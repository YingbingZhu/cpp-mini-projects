//
// Created by yingbingzhu on 2025/4/29.
//

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mutex>
#include <thread>
#include <vector>
#include <openssl/ssl.h>
#include <openssl/err.h>

std::vector<SSL*> clients;
std::mutex clients_mutex;
SSL_CTX *ssl_ctx; // manage certificates and algorithm

void handle_client(SSL* ssl, int client_socket) {
  char buffer[1024];

  while (true) {
    memset(buffer, 0, sizeof(buffer));
    ssize_t bytes_read = SSL_read(ssl, buffer, sizeof(buffer));
    if (bytes_read <= 0) {
      std::cerr << "Client disconnected or error\n";
      break;
    }

    std::cout << "Received " << bytes_read << " bytes\n";
    // broadcasr the messgae to all clients
    clients_mutex.lock();
    for (SSL* other_ssl : clients) {
      if (other_ssl != ssl) {
        SSL_write(other_ssl, buffer, bytes_read);
      }
    }
    clients_mutex.unlock();
  }

  // cleanup
  clients_mutex.lock();
  clients.erase(
      std::remove(clients.begin(), clients.end(), ssl),
      clients.end()
  );
  clients_mutex.unlock();
  SSL_shutdown(ssl);
  SSL_free(ssl);
}

void print_current_dir() {
  char buff[PATH_MAX];
  if (getcwd(buff, sizeof(buff)) != NULL) {
    std::cout << "Current working directory: " << buff << std::endl;
  } else {
    std::cerr << "Failed to get current working directory!" << std::endl;
  }
}

int main() {
  print_current_dir();
  // Initialize OpenSSL
  SSL_library_init();
  SSL_load_error_strings();
  OpenSSL_add_all_algorithms();

  // Create SSL context
  ssl_ctx = SSL_CTX_new(TLS_server_method());
  if (!ssl_ctx) {
    ERR_print_errors_fp(stderr);
    return 1;
  }

  // Load certificate and private key
  if (SSL_CTX_use_certificate_file(ssl_ctx, "../../../cert.pem", SSL_FILETYPE_PEM) <= 0 ||
    SSL_CTX_use_PrivateKey_file(ssl_ctx, "../../../key.pem", SSL_FILETYPE_PEM) <= 0) {
    ERR_print_errors_fp(stderr);
    return 1;
    }


  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    std::cerr << "Failed to create socket\n";
    return 1;
  }

  // bind to port
  sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8888);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(sock, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    std::cerr << "Failed to bind socket\n";
    return 1;
  }

  // start listening
  if (listen(sock, 5) == -1) {
    std::cerr << "Failed to listen on socket\n";
    return 1;
  }
  std::cout << "Server listening on port 8888\n";

  while (true) {
    sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    int conn = accept(sock, (sockaddr*)&client_addr, &len);
    SSL* ssl = SSL_new(ssl_ctx);
    SSL_set_fd(ssl, conn);
    if (SSL_accept(ssl) <= 0) {
      std::cerr << "Failed to accept connection\n";
      continue;
    }
    std::cout << "New connection from " << inet_ntoa(client_addr.sin_addr) << "\n";
    // add to client list
    clients_mutex.lock();
    clients.push_back(ssl);
    clients_mutex.unlock();

    // create a thread for this client
    std::thread(handle_client, ssl, conn).detach();
  }

  SSL_CTX_free(ssl_ctx);
  EVP_cleanup();

  return 0;
}


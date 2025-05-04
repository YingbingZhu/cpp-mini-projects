//
// Created by yingbingzhu on 2025/4/29.
//

#include <iostream>
#include <string>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

void receive_messages(SSL* ssl) {
  char buffer[1024];
  while (true) {
    memset(buffer, 0, sizeof(buffer));
    int bytes_received = SSL_read(ssl, buffer, sizeof(buffer));
    if (bytes_received <= 0) {
      std::cerr << "Server disconnected or error\n";
      break;
    }
    std::cout << std::string(buffer, bytes_received) << std::endl;
  }
}

int main() {
  // Initialize OpenSSL
  SSL_library_init();
  SSL_load_error_strings();
  OpenSSL_add_all_algorithms();

  // Create SSL context
  SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
  if (!ctx) {
    ERR_print_errors_fp(stderr);
    return 1;
  }

  // input username
  std::string username;
  std::cout << "Enter your username: ";
  std::getline(std::cin, username);

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    std::cerr << "Failed to create socket\n";
    return 1;
  }

  sockaddr_in server_addr{};
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8888);
  if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
    std::cerr << "Invalid address\n";
    return 1;
  }

  // connect to server
  if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    std::cerr << "Failed to connect to server\n";
    return 1;
  }
  SSL* ssl = SSL_new(ctx);
  SSL_set_fd(ssl, sock);

  if (SSL_connect(ssl) <= 0) {
    std::cerr << "TLS handshake failed\n";
    ERR_print_errors_fp(stderr);
    return 1;
  }

  std::cout << "Connected to server!\n";

  // start thread to receive messages
  std::thread receiver_thread(receive_messages, ssl);
  receiver_thread.detach();

  // main thread to send messages
  std::string message;
  while (true) {
    std::getline(std::cin, message);
    if (message == "exit") break;
    if (message.empty()) continue;
    std::string full_message = username + ": " + message;
    SSL_write(ssl, full_message.c_str(), full_message.size());
  }

  // clean up
  SSL_shutdown(ssl);
  SSL_free(ssl);
  close(sock);
  SSL_CTX_free(ctx);
  EVP_cleanup();
  return 0;
}
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

std::vector<int> clients;
std::mutex clients_mutex;

void handle_client(int client_socket) {
  char buffer[1024];

  while (true) {
    memset(buffer, 0, sizeof(buffer));
    ssize_t bytes_read = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_read <= 0) {
      std::cerr << "Client disconnected or error\n";
      break;
    }

    std::cout << "Received " << bytes_read << " bytes\n";
    // broadcasr the messgae to all clients
    clients_mutex.lock();
    for (int client: clients) {
      if (client != client_socket) {
        send(client, buffer, bytes_read, 0);
      }
    }
    clients_mutex.unlock();
  }

  // cleanup
  clients_mutex.lock();
  clients.erase(
      std::remove(clients.begin(), clients.end(), client_socket),// shift elements that not match to front
      clients.end()
  );
  clients_mutex.unlock();
  close(client_socket);
}

int main() {
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
    if (conn == -1) {
      std::cerr << "Failed to accept connection\n";
      continue;
    }
    std::cout << "New connection from " << inet_ntoa(client_addr.sin_addr) << "\n";
    // add to client list
    clients_mutex.lock();
    clients.push_back(conn);
    clients_mutex.unlock();

    // create a thread for this client
    std::thread(handle_client, conn).detach();
  }

  return 0;
}


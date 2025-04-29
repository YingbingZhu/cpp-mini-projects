//
// Created by yingbingzhu on 2025/4/29.
//

#include <iostream>
#include <string>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void receive_messages(int sock) {
  char buffer[1024];
  while (true) {
    memset(buffer, 0, sizeof(buffer));
    ssize_t bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received <= 0) {
      std::cerr << "Server disconnected or error\n";
      break;
    }
    std::cout << std::string(buffer, bytes_received) << std::endl;
  }
}

int main() {
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

  std::cout << "Connected to server!\n";

  // start thread to receive messages
  std::thread receiver(receive_messages, sock);

  // main thread to send messages
  std::string message;
  while (true) {
    std::getline(std::cin, message);
    if (message == "exit") {
      break;
    }
    std::string full_message = username + ": " + message;
    send(sock, full_message.c_str(), full_message.size(), 0);
  }

  // clean up
  close(sock);
  receiver.detach();
  return 0;
}
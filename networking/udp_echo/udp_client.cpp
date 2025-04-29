//
// Created by yingbingzhu on 2025/4/28.
//


#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main() {
  // create socket
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock == -1) {
    perror("socket creation failed");
    return 1;
  }
  // server information
  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_port = htons(8888);
  // Convert IPv4 and IPv6 addresses from text to binary form
  if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) <= 0) {
    std::cerr << "Invalid address / Address not supported" << std::endl;
    return 1;
  }
  // message to send
  const char* message = "Hello world!";
  ssize_t sent_bytes = sendto(sock, message, strlen(message), 0, (sockaddr*)&server, sizeof(server));
  if (sent_bytes == -1) {
    perror("sendto failed");
    return 1;
  }

  std::cout << "Message sent to server." << std::endl;

  // receive response
  char buffer[1024];
  socklen_t server_len = sizeof(server);
  ssize_t recv_bytes = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&server, &server_len);

  if (recv_bytes >= 0) {
    buffer[recv_bytes] = '\0'; // Null-terminate
    std::cout << "Server reply: " << buffer << std::endl;
  } else {
    perror("recvfrom failed");
  }

  close(sock);
  return 0;



}
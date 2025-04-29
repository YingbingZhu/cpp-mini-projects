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
  // Create a UDP socket
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock == -1) {
    std::cerr << "Failed to create socket\n";
    return 1;
  }

  //  Bind it to a port
  sockaddr_in serverAddr{};
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(8888);
  serverAddr.sin_addr.s_addr = INADDR_ANY; // receive messages send to any interface
  if (bind(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
    std::cerr << "Bind failed\n";
    close(sock);
    return 1;
  }

  //  Wait for messages (recvfrom)
  char buffer[1024];
  sockaddr_in clientAddr{};
  socklen_t clientAddrLen = sizeof(clientAddr);

  std::cout << "UDP Echo Server is running on port 8888...\n";
  while (true) {
    memset(buffer, 0, sizeof(buffer)); // clear buffer
    // (leave 1 byte space for safety / null terminator)
    int bytes = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&clientAddr, &clientAddrLen);
    if (bytes == -1) {
      std::cerr << "Failed to receive data\n";
      continue;
    }

    std::cout << "Received: " << buffer << "\n";
    //  Echo the message back to the sender (sendto)
    sendto(sock, buffer, bytes, 0, (sockaddr*)&clientAddr, clientAddrLen);
  }

  close(sock);
  return 0;
}
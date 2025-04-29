//
// Created by yingbingzhu on 2025/4/28.
//
#include <sys/socket.h>  // socket(), connect()
#include <netinet/in.h>  // sockaddr_in
#include <arpa/inet.h>   // inet_pton()
#include <unistd.h>      // close()
#include <cstring>       // memset()
#include <iostream>

int main() {
  // create socket, Address Family = IPv4, TCP
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  // prepare address and port number
  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  for (int i = 20 ; i <= 100; i++) {
    addr.sin_port = htons(i);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr); // Convert string IP to binary
    // connect
    int result = connect(sock, (sockaddr*)&addr, sizeof(addr));
    if (result == 0) {
      std::cout << "[+] Port " << i << " is OPEN!\n";
    }
    close(sock);
  }
  return 0;
}
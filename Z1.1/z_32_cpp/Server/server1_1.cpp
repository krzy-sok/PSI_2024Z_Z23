// Server side implementation of UDP client-server model
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <chrono>

#define PORT 8080
#define MAXLINE 66000

// Driver code
int main() {
  //
  int sockfd;
  char buffer[MAXLINE];
  const char *hello = "Confirmation sent";
  struct sockaddr_in servaddr, cliaddr;

  // Creating socket file descriptor
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  memset(&cliaddr, 0, sizeof(cliaddr));

  // Filling server information
  servaddr.sin_family = AF_INET; // IPv4
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(PORT);

  // Bind the socket with the server address
  if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  socklen_t len;
  int n;

  len = sizeof(cliaddr); // len is value/result

  std::chrono::time_point start = std::chrono::steady_clock::now();
  while (std::chrono::steady_clock::now() - start < std::chrono::seconds(10)) {
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_DONTWAIT,
                 (struct sockaddr *)&cliaddr, &len);
    if (n != -1) {
      buffer[n] = '\0';
      printf("Received  %d bytes\n", n);
      printf("Sender: %c%c%c \n", buffer[0], buffer[1], buffer[2]);

      sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM,
             (const struct sockaddr *)&cliaddr, len);
      std::cout << hello << std::endl;
    }
  }
  return 0;
}

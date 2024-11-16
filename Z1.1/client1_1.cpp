// Client side implementation of UDP client-server model
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define MAXLINE 66000

char *msg_generator(int lenght) {
  char *message = new char[66000];
  char sender[] = "z32";
  strncpy(message, sender, sizeof(sender));
  for (int i = 3; i < lenght; i++) {
    message[i] = char(i % 26 + 65);
  }
  message[lenght] = '\0';
  return message;
}

// Driver code
int main() {
  int sockfd;
  char buffer[MAXLINE];
  // const char *hello = "Hello from client";
  struct sockaddr_in servaddr;

  // Creating socket file descriptor
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));

  // Filling server information
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = INADDR_ANY;

  int n;
  socklen_t len;
  int length = 1;

  while (1) {
    char *msg = msg_generator(length);

    sendto(sockfd, msg, strlen(msg), MSG_CONFIRM,
           (const struct sockaddr *)&servaddr, sizeof(servaddr));
    std::cout << "Message sent with length: " << length << std::endl;

    length += 100;
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL,
                 (struct sockaddr *)&servaddr, &len);
    buffer[n] = '\0';
    std::cout << "Server received message:" << buffer << std::endl;
  }

  close(sockfd);
  return 0;
}

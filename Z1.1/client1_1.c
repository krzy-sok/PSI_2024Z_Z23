//docker run -it --network-alias z32_client --ip '172.21.32.3' --network z32_network --name z32_client z32_client
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define PORT 8080
#define MAXLINE 66000
#define NETWORK_IP "172.21.32.2"

char *msg_generator(int lenght) {
  char *message = (char *)malloc(66000 * sizeof(char));
  char sender[] = "z32";
  strncpy(message, sender, sizeof(sender));
  for (int i = 3; i < lenght; i++) {
    message[i] = (char)(i % 26 + 65);
  }
  message[lenght] = '\0';
  return message;
}

int main() {
  int sockfd;
  char buffer[MAXLINE];
  struct sockaddr_in servaddr;

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = inet_addr(NETWORK_IP);

  int n;
  socklen_t len;
  int length = 1;

  clock_t start = clock();
  while ((double)(clock() - start) / CLOCKS_PER_SEC < 10.0) {
    char *msg = msg_generator(length);

    sendto(sockfd, msg, strlen(msg), MSG_CONFIRM,
           (const struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Message sent with length: %d\n", length);

    length += 100;

    while ((double)(clock() - start) / CLOCKS_PER_SEC < 10.0) {
      n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_DONTWAIT,
                   (struct sockaddr *)&servaddr, &len);
      if (n != -1) {
        buffer[n] = '\0';
        printf("Server received message: %s\n", buffer);
        break;
      }
    }
  }

  close(sockfd);
  return 0;
}

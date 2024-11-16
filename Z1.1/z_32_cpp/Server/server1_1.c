//docker run -it --rm --network-alias z32_server --ip '172.21.32.2' --network z32_network --name z32_server z32_server
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define PORT 8080
#define MAXLINE 66000

int main() {
  int sockfd;
  char buffer[MAXLINE];
  const char *hello = "Confirmation sent";
  struct sockaddr_in servaddr, cliaddr;

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  memset(&cliaddr, 0, sizeof(cliaddr));

  servaddr.sin_family = AF_INET; 
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(PORT);

  if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  socklen_t len;
  int n;

  len = sizeof(cliaddr); 

  clock_t start = clock();
  while ((double)(clock() - start) / CLOCKS_PER_SEC < 10.0) {
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_DONTWAIT,
                 (struct sockaddr *)&cliaddr, &len);
    if (n != -1) {
      buffer[n] = '\0';
      printf("Received  %d bytes\n", n);
      printf("Sender: %c%c%c \n", buffer[0], buffer[1], buffer[2]);

      sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM,
             (const struct sockaddr *)&cliaddr, len);
      printf("%s\n", hello);
    }
  }
  return 0;
}

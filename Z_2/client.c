#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <buffer_size>\n", argv[0]);
        return -1;
    }

    int buffer_size = atoi(argv[1]);
    if (buffer_size <= 0) {
        return -1;
    }

    int sock = 0;
    struct sockaddr_in serv_addr;
    char *buffer = malloc(buffer_size);
    memset(buffer, 'A', buffer_size); 

    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == 0) {
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

 
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        return -1;
    }

   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        return -1;
    }

    printf("Połączono z serwerem.\n");
    clock_t t;
   
    for (int i = 0; i < 20; i++) {
        t = clock();
        if (send(sock, buffer, buffer_size, 0) == -1) {
            printf("Bład wysłania danych");
            break;
        }
        t = clock() - t; 
        double time_taken = ((double)t)/CLOCKS_PER_SEC; 
        printf("Wysłano dane w %f\n", time_taken);
    }

    free(buffer);
    close(sock);
    return 0;
}

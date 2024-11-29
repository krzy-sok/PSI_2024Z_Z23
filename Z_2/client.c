#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080

void log_time_diff(struct timespec start, struct timespec end) {
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Czas wysyłania pakietu: %.6f sekund\n", elapsed);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <buffer_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int buffer_size = atoi(argv[1]);
    if (buffer_size <= 0) {
        printf("Error: buffer size must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    int sock = 0;
    struct sockaddr_in serv_addr;
    char *buffer = malloc(buffer_size);
    memset(buffer, 'A', buffer_size); 

    // Tworzenie gniazda
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

 
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return -1;
    }

    // Połączenie z serwerem
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    printf("Połączono z serwerem.\n");

    // Wysyłanie danych w pętli
    for (int i = 0; i < 20; i++) {
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

        if (send(sock, buffer, buffer_size, 0) == -1) {
            perror("Send error");
            break;
        }

        clock_gettime(CLOCK_MONOTONIC, &end);
        log_time_diff(start, end);
    }

    free(buffer);
    close(sock);
    return 0;
}

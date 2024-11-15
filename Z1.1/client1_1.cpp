// Client side implementation of UDP client-server model 
#include <bits/stdc++.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <time.h>

#define PORT	 8080 
#define MAXLINE 2000

char * msg_generator(int lenght) {
    std::string message = "z32";
for (int i = 0; i< lenght -2; i++){
    message += char(i % 26 + 65);


}
char* msg = message.data();
return msg;
}


// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	// const char *hello = "Hello from client"; 
	struct sockaddr_in	 servaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
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
	
        while(1){
        char * msg = msg_generator(length);
     
        sendto(sockfd, msg, strlen(msg), 
		MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
			sizeof(servaddr)); 
	std::cout<<"Message sent with length: " << length <<std::endl; 
    
    length += 200;
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
				MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len); 
	buffer[n] = '\0'; 
	std::cout<<"Server received message:"<<buffer <<std::endl; 
    sleep(0.5);
        }
		
	

	close(sockfd); 
	return 0; 
}

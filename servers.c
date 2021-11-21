#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8888

int main(int argc, char const *argv[])
{
    int server_fd, new_socket; long c;
    struct sockaddr_in server;
    int addrlen = sizeof(server);
    
    // HTTP protocol implement
     char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 45\n\n Hai, saya Nazim. Boleh saya tahu awak siapa?";
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    
	//Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( PORT );
    
    memset(server.sin_zero, '\0', sizeof server.sin_zero);
    
    //Bind
    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
	
	//Listen
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
	
	//Accepting connection
    while(1)
    {
        printf("\n----------------- Waiting for new connection --------------------\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&server, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        
        char buffer[30000] = {0};
        c = read( new_socket , buffer, 30000);
        printf("%s\n",buffer );
        write(new_socket , hello , strlen(hello));
        printf("------------------ Message has been sent -------------------");
        close(new_socket);
    }
    return 0;
}

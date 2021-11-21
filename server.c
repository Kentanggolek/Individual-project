#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<string.h>

int main(int argc , char *argv[])
{
	int socket_desc , new_socket , c;
	struct sockaddr_in server , client;
	int addrlen = sizeof(server);
	
	char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 37\n\n Hai, testing 1,2,3 !";
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY use to bind all ip in server
	server.sin_port = htons( 80 );
	
	memset(server.sin_zero, '\0', sizeof server.sin_zero);
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("bind failed");
	}
	puts("bind done");
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	if (new_socket<0)
	{
		perror("accept failed");
	}
	
	puts("Connection accepted");

	return 0;
}

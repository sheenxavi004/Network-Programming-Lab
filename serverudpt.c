// Name   : serverudpt.c
// Desc   : Server side concurrent time server application using UDP
// Input  : None
// Output : Acknowledgement from the client.
// Author : Sheen Xavier A
// Date   : 23/06/2021

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 4444

int main()
{
	// Variables for socket creation
	int sockfd;
    time_t t;
	struct sockaddr_in server_addr, server_trans;
	char buffer[1024];
	socklen_t addr_size;

	// Creating the socket for establishing connection between the server and the client
	sockfd = socket(AF_INET, SOCK_DGRAM, 0); //SOCK_DGRAM represents UDP
	if(sockfd == -1)
	{
		printf("Socket Creation Failed!\n");
		exit(0);
	}
	else
		printf("Socket Creation Successful!\n");

	memset(&server_addr, '\0', sizeof(server_addr)); // Setting the server_addr to NULL

	// Setting the connection family, port and IP
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr_size = sizeof(server_trans);

	// Binding the socket to given the specifications given
	if(bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)))
	{
		printf("Socket Binding Failed!\n");
		exit(0);
	}
	else
		printf("Socket Binding Successful!\n");

	// Receiving the message transmitted by the client
	recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&server_trans, &addr_size);
	printf("Client : %s\n", buffer);
	
	// Sending the time to the client
    time(&t); // time converts realtime into seconds and ctime provides the string form.
	sendto(sockfd, ctime(&t), 1024, 0, (struct sockaddr*)&server_trans, addr_size); 
    printf("Server : The current date and time has been transmitted to the client!\n");

	printf("Transmission is over!\n");
	return 0;
}
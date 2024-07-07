// Name   : clientudp.c
// Desc   : Program to demonstrate client side communication using UDP
// Input  : None
// Output : Data transmitted to the server and the reply from the server
// Author : Sheen Xavier A
// Date   : 04/06/2021

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444

int main()
{
	// Varibles for Socket Creation
	int sockfd;
	struct sockaddr_in server_addr;
	char data[1024];
	socklen_t addr_size;

	// Creating client socket for establishing connection with the server
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
	addr_size = sizeof(server_addr);

	// Transmitting the query to the server via the established socket
	printf("Query : ");
	scanf(" %[^\n]", data);
	sendto(sockfd, data, 1024, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

	// Receiving the reply from the server in response to the query
	recvfrom(sockfd, data, 1024, 0, (struct sockaddr*)&server_addr, &addr_size);
	printf("Server : %s\n", data);

	printf("Transmission is over!\n"); 

	return 0;
}
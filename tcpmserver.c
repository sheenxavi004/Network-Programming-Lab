// Name   : tcpmserver.c
// Desc   : Program to demonstrate server side of multi user chat server using TCP
// Input  : Message to be transmitted to various clients
// Output : Responses to be transmitted to the clients and the processing involved
// Author : Sheen Xavier A
// Date   : 11/06/2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444

int main()
{
	// Variables for socket creation
	int sockfd, connSocket;
	struct sockaddr_in serverAddr, connAddr;
	socklen_t addr_size;
	char buffer[1024];
	pid_t childpid; // Variable for the multiple clients

	// Creating the socket for establishing connection between client and server
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		printf("Socket Creation Failed!\n");
		exit(0);
	}
	else
		printf("Socket Creation Successful!\n");
	memset(&serverAddr, '\0', sizeof(serverAddr)); // Setting the serverAddr to NULL

	// Setting the connection family, port and IP
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Binding the socket to given the specifications given
	if((bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr))) != 0)
	{
		printf("Socket Binding Failed!\n");
		exit(0);
	}
	else
		printf("Socket Binding Successful!\n");


	// Trying to listen
	if(listen(sockfd, 5) != 0)
	{
		printf("Listening Failed!\n");
		exit(0);
	}
	else
		printf("Server is Listening!\n");
	addr_size = sizeof(connAddr);

	// Server runs until program is terminated
	while(1)
	{
		// Accepting the connection request from the client and proceeding
		connSocket = accept(sockfd, (struct sockaddr*)&connAddr, &addr_size);
		if(connSocket < 0)
			exit(0);
		printf("Connection accepted from %s:%d\n", inet_ntoa(connAddr.sin_addr), ntohs(connAddr.sin_port));
		
		if((childpid = fork()) == 0) // Creating child processes for handling mutliple clients
		{
			close(sockfd);
			while(1)
			{
				// Recieving message from the client
				memset(buffer, 0, sizeof(buffer));
				recv(connSocket, buffer, 1024, 0);

				// Closing connection if client exits
				if(strcmp(buffer, "exit") == 0)
				{
					printf("Disconnected from %s:%d\n", inet_ntoa(connAddr.sin_addr), ntohs(connAddr.sin_port));
					break;
				}

				// Message recieved from the client
				printf("Client@%s:%d : %s\n", inet_ntoa(connAddr.sin_addr), ntohs(connAddr.sin_port), buffer);
				printf("Reply : ");
				// Sending the message via the new socket
				scanf(" %[^\n]", buffer);
				send(connSocket, buffer, strlen(buffer), 0);
				bzero(buffer, sizeof(buffer));
			}
		}
	}
	// Closing the sockets
	close(connSocket);
	close(sockfd);

	printf("Connection Closed!\n");

	return 0;
}
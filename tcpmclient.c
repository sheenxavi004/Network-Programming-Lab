// Name   : tcpmclient.c
// Desc   : Program to demonstrate client side of multi-user chat server using TCP
// Input  : Messages to be transmitted to the server
// Output : Responses from the Server and the processing involved
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
	// Varibles for Socket Creation
	int clientSocket;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	// Creating client socket for establishing connection with the server
	clientSocket = socket(AF_INET, SOCK_STREAM, 0); // SOCK_STREAM implies TCP
	if(clientSocket == -1)
	{
		printf("Socket Creation Failed!\n");
		exit(0);
	}
	printf("Socket Creation Successful!\n");
	memset(&serverAddr, '\0', sizeof(serverAddr)); // Setting the serverAddr to NULL

	// Setting the connection family, port and IP
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Connecting the client to server
	if(connect(clientSocket, (struct  sockaddr*)&serverAddr, sizeof(serverAddr)) != 0)
	{
		printf("Connection with Server Failed!\n");
		exit(0);
	}
	else
		printf("Connection with Server Successful!\n");

	while(1)
	{
		printf("Message : ");
		scanf(" %[^\n]", buffer);
		// Transmitting data to the server side
		send(clientSocket, buffer, strlen(buffer), 0);

		// For closing the communication on server side
		if(!strcmp(buffer, "exit"))
			break;
		// Recieving the data transmitted by the server
		bzero(buffer, sizeof(buffer));
		recv(clientSocket, buffer, 1024, 0);
		printf("Server : %s\n", buffer);
	}
	// Closing the socket
	close(clientSocket);
	printf("Connection Closed!\n");

	return 0;
}
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

	// Recieving the data transmitted by the server
	recv(connSocket, buffer, 1024, 0);
	printf("Data Recieved : %s\n", buffer);

	// Accepting the connection request from the client and proceeding
	connSocket = accept(sockfd, (struct sockaddr*)&connAddr, &addr_size);
	strcpy(buffer, "TCP is a Connection Oriented Protocol!");
	// Sending the message via the new socket
	send(connSocket, buffer, strlen(buffer), 0);
	printf("Data Transmission Complete!\n");

	// Closing the sockets
	close(connSocket);
	close(sockfd);

	printf("Connection Closed!\n");

	return 0;
}
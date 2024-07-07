#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 4444

int main()
{
	// Varibles for Socket Creation
	int clientSocket;
	struct sockaddr_in serverAddr;
	char buffer[1024], fname[1000];

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


	// Reading the name of the file to be requested
	printf("Filename : ");
	scanf(" %[^\n]", fname);

	// Sending the message via the new socket
	send(clientSocket, fname, strlen(fname), 0);
	// Recieving the data transmitted by the server
	recv(clientSocket, buffer, 1024, 0);
	printf("Data Recieved : %s\n", buffer);

	// Closing the socket
	close(clientSocket);
	printf("Connection Closed!\n");

	return 0;
}
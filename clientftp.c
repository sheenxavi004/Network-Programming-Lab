// Name   : clientfcp.c
// Desc   : Program to demonstrate client side communication using TCP
// Input  : Name of the file required
// Output : Contents of the requested file and the process ID of the server
//          and the processing involved
// Author : Sheen Xavier A
// Date   : 08/07/2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	printf("Name of File : ");
	scanf(" %[^\n]", fname);

	// Sending the message via the new socket
	send(clientSocket, fname, strlen(fname), 0);
    printf("Requesting the file named %s from the server...\n", fname);


	// Receiving the file content transmitted by the server
	recv(clientSocket, buffer, 1024, 0);
	if(strcmp(buffer, "NO"))
    {
        printf("The contents of the file %s are : ", fname);
        printf("\n---------------------------------\n%s",buffer);
        printf("\n---------------------------------\n");
    }
    else
        printf("Server : The file doesn't exist!\n");

    // Requesting the process id of the server
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, "Request for Process ID of the Server.");
    send(clientSocket, buffer, 1024, 0);
    printf("Requesting the Process ID of the Server...\n");

    // Receiving the process id of the server
    recv(clientSocket, buffer, 1024, 0);
    printf("Server : %s\n", buffer);
    printf("Transmission Complete!\n");
    

	// Closing the socket
	close(clientSocket);
	printf("Connection Closed!\n");

	return 0;
}
// Name   : serverftp.c
// Desc   : Program to demonstrate server side of concurrent file server using TCP
// Input  : None
// Output : File transmission and the processing involved
// Author : Sheen Xavier A
// Date   : 08/07/2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/sendfile.h>
#include <fcntl.h>

#define PORT 4444

int main()
{
	// Variables for socket creation
	int sockfd, connSocket, filefd;
	struct sockaddr_in serverAddr, connAddr;
	socklen_t addr_size;
	char buffer[1024], fname[1000];

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

	// Accepting the connection request from the client and proceeding
	connSocket = accept(sockfd, (struct sockaddr*)&connAddr, &addr_size);

	// Recieving the name of the file transmitted by the client
    memset(fname, 0, sizeof(fname));
	recv(connSocket, fname, 1000, 0);
    printf("Client : Requesting file named %s\n", fname);

    // Checking if the file exists and can be read
    if(access(fname, F_OK) == -1)
    {
	    strcpy(buffer, "NO");
        send(connSocket, buffer, sizeof(buffer), 0);
        printf("File doesn't exist!\n");
    }
    else
    {
        printf("File found. Processing Transmission...\n");
        // Sending the file to be transmitted
        filefd = open(fname, O_RDONLY);
        sendfile(connSocket, filefd, 0, 1024);
        printf("File Transmission Complete!\n");
        close(filefd);
    }

    // Recieving request of process ID from the client
    memset(buffer, 0, sizeof(buffer));
    recv(connSocket, buffer, 1024, 0);
    printf("Client : %s\n", buffer);

    // Sending the Process ID of the server
    memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, "The Process ID of the Server is %d.", getpid());
    send(connSocket, buffer, 1024, 0);
	printf("Transmission Complete!\n");

	// Closing the sockets
	close(connSocket);
	close(sockfd);

	printf("Connection Closed!\n");

	return 0;
}
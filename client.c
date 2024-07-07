#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 4444

int main()
{
	// Varibles for Socket Creation
	int clientSocket, continueLoop = 1;
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


	// Reading the stream of numbers
	printf("Enter the string : ");
	scanf(" %[^\n]", fname);
	// Sending the numerical string to the server
	send(clientSocket, fname, strlen(fname), 0);

	// Recieving the sum or message transmitted by the server
    while(continueLoop)
    {
        memset(buffer, 0, sizeof(buffer));
	    recv(clientSocket, buffer, 1024, 0);

        // Continue to recieve data unless the data recieved is
        // an error message or a single digit
        if((!isdigit(buffer[0])) || (strlen(buffer) == 1))
            continueLoop = 0;
	    printf("From Server : %s\n", buffer);
    }

	// Closing the socket
	close(clientSocket);
	printf("Connection Closed!\n");

	return 0;
}
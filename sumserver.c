// Name   : sumserver.c
// Desc   : Program to demonstrate server side of sum computing server using TCP
// Input  : Numerical string from client
// Output : Sum of the numbers in the string is transmitted to client until the
//          sum is a single digit
// Author : Sheen Xavier A
// Date   : 18/09/2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/sendfile.h>

#define PORT 4444

int main()
{
	// Variables for socket creation
	int sockfd, connSocket, sum, tempSum, i;
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

    // The server will run forever
    while(1)
    {

        // Accepting the connection request from the client and proceeding
        connSocket = accept(sockfd, (struct sockaddr*)&connAddr, &addr_size);

        printf("Found Client!\n");
        // Recieving request of sum from the client
        memset(buffer, 0, sizeof(buffer));
        recv(connSocket, buffer, 1024, 0);
        printf("Client Sum Request : %s\n", buffer);

        // Checking whether the numeric string is valid
        /*
        i = 0;
        checkNumericString = 1;
        while(buffer[i] != '\0')
        {
            if(!isdigit(buffer[i]))
            {
                checkNumericString = 0;
                break;
            }
            i++;
        }

        */

        if(isdigit[buffer[0]])
        {
            i = 0;
            sum = 0;
            while(buffer[i] != '\0')
            {
                sum += buffer[i] - 48;
                i++;
            }

            while(sum > 9) // Continues transmitting until sum is a single digit
            {
                printf("To Client : %d\n", sum);
                sprintf(buffer, "%d", sum);
                send(connSocket, buffer, 1024, 0);
                tempSum = 0;
                while(sum > 0)
                {
                    tempSum += sum % 10;
                    sum /= 10;
                }
                sum = tempSum;
            }
            printf("To Client : %d\n", sum);
            sprintf(buffer, "%d", sum);
            send(connSocket, buffer, 1024, 0);
        }
        else // If the string recieved from the client is not numerical
        {
            memset(buffer, 0, sizeof(buffer));
            strcpy(buffer, "Sorry, cannot compute!");
            printf("To Client : %s\n", buffer);
            send(connSocket, buffer, 1024, 0);   
        }

        printf("Waiting for Connection....\n");
    }

	// Closing the sockets
	close(connSocket);
	close(sockfd);

	printf("Connection Closed!\n");

	return 0;
}
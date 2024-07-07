// Name   : cpcomm.c
// Desc   : Program which simulates the communication between
//          parent and child process via ordinary pipes
// Input  : Data to be transmitted
// Output : Communication between the parent and child process
// Author : Sheen Xavier A
// Date   : 22/04/2021

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int dp[2], id;
	char msgcp[30];
	char *data = "Successor sends his regards!\n";
	// Creating the pipe
	if(pipe(dp) == -1)
	{
		// Exiting incase of failure in creating pipe
		printf("Pipe creation failure!\n");
		exit(0);
	}

	id = fork(); // Creating the child process

	if(id == 0) // If we're currently in the child process
	{
		// Child Process Handling Section
		sleep(1); 
		printf("Child writing the data to be sent to parent...\n");
		write(dp[1], data, 30); // Child process writes data into the pipe
	}
	else
	{
		// Parent Process Handling Section
		sleep(1);
		read(dp[0], msgcp, 30); // Parent process reades data from the pipe
		printf("Parent reading data from the child...\n");
		printf("Message from Child to Parent : %s\n", msgcp); 
	}

	return 0;
}
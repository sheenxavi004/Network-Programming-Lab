#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int flow[2];
	char buff[18];

	// Creating the pipe for flow of data
	if(pipe(flow) == -1)
	{
		printf("Error in piping!\n");
		exit(0);
	}

	// Data to be inserted into the pipe
	char *data = "Wings of Freedom\n";

	// Inserting data into the pipe at write end 
	printf("Inserting data into pipe at one end...\n");
	write(flow[1], data, 18);
	printf("Finished inserting data!\n");

	// Fetching data previously inserted into the pipe from read end
	printf("Fetching data from the pipe at the other end...\n");
	read(flow[0], buff, 18);
	printf("Finished fetching data!\n");

	// Aquired data
	printf("Data from the pipe: %s\n", buff);
	
	return 0;
}
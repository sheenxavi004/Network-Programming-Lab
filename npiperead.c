// Name   : npiperead.c
// Desc   : Program to demonstrate IPC using named pipes
//          This program reads first and then writes
// Input  : Data to be transmitted
// Output : Communication between two process
// Author : Sheen Xavier A
// Date   : 22/04/2021

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
	int fd;

	// FIFO File Path
	char * spfifo = "/tmp/ipc";
	char rdata[100], wdata[100];
	// Creating the FIFO file for IPC using mkfifo()
	// Setting permission for the FIFO File as read-write
	mkfifo(spfifo, 0666);

	printf("HAL-9000 Terminal\n");
	while(1)
	{
		// Opening the FIFO for read only
		fd = open(spfifo, O_RDONLY);

		read(fd, rdata, 100); // Reading content from FIFO
		printf("Dave says : %s\n", rdata); // Displaying the message from other process

		// Opening the FIFO for write only
		fd = open(spfifo, O_WRONLY);
		
		printf("Type Message : ");
		scanf(" %[^\n]", wdata); // Reading input from the user
		write(fd, wdata, strlen(wdata) + 1); //Writing the input onto FIFO

		close(fd); //Closing the FIFO
	}
	return 0;
}
#include <stdio.h>
#include <fcntl.h>

int main()
{
	// This mode creates the file if it doesn't exist
	int ftry = open("file.c", O_RDONLY | O_CREAT);
	int closeres = -1;

	if(ftry == -1)
		printf("Error in opening or creating the file \n"); // Success
	else
		printf("File opened with descriptor : %d\n", ftry); // Returns file descriptor used
	
	// Closing the file with descriptor 'ftry'

	closeres = close(ftry);
	if(closeres == 0)
		printf("File has been successfully closed!\n");
	else
		printf("Error in closing file!\n");
	return 0;
}
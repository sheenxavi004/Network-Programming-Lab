#include <stdio.h>
#include <fcntl.h>

int main()
{
	// This mode creates the file if it doesn't exist
	int ftry = open("file.c", O_RDONLY | O_CREAT);

	if(ftry == -1)
		printf("Error in opening or creating the file \n"); // Success
	else
		printf("File Descriptor Used : %d\n", ftry); // Returns file descriptor used
	return 0;
}
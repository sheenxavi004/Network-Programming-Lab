#include <stdio.h>
#include <fcntl.h>

int main()
{
	// This mode creates the file if it doesn't exist
	int ftry = open("file.txt", O_RDONLY | O_CREAT);
	int readb = 0;
	char *content = (char *)calloc(1000, sizeof(char));

	if(ftry == -1)
		printf("Error in opening or creating the file \n"); // Success
	else
		printf("File opened with descriptor : %d\n", ftry); // Returns file descriptor used
	
	// Reading and printing contents
	
	readb = read(ftry, content, 20);
	content[readb] = '\0';

	printf("Read %d bytes. The contents are : \n%s\n",readb, content);
	
	// Closing the file with descriptor 'ftry'
	close(ftry);
	printf("File closed!\n");
	return 0;
}
#include <stdio.h>
#include <fcntl.h>

int main()
{
	// This mode creates the file if it doesn't exist
	int ftry = open("filer.txt", O_RDWR | O_CREAT);
	int writeb = 0;

	if(ftry == -1)
		printf("Error in opening or creating the file \n"); // Success
	else
		printf("File opened with descriptor : %d\n", ftry); // Returns file descriptor used
	
	// Writing content
	
	writeb = write(ftry, "Good Day!\n", 10);
	if(writeb > -1)
		printf("Content written successfully!\n");

	// Closing the file with descriptor 'ftry'
	close(ftry);
	printf("File closed!\n");
	return 0;
}
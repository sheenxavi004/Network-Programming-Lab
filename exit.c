#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Starting the program !\n");
	printf("Exiting the program !\n");

	// When we execute this step the thread is terminated 
	exit(0);

	// Won't be run
	printf("Content not meant to be printed!\n");
	return 0;
}
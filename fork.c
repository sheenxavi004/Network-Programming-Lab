#include <stdio.h>
#include <unistd.h>

int main()
{
	int pid = 0;
	pid = fork();

	// Parent process
	if(pid > 0)
		printf("The Parent process has ID %d\n", getpid());

	// Child process
	if(pid == 0)
		printf("The Child process has ID %d\nThe Parent process has ID %d\n", getpid(), getppid());

	// Process creation error
	if(pid < 0)
		printf("Error in creating child process!\n");
	
	return 0;
}
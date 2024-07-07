#include <stdio.h>
#include <unistd.h>

int main()
{
	int pid = getpid(); // Returns the pid of the process
	printf("The Process ID is %d\n", pid);
	return 0;
}
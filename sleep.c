#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("Sleep for 2 seconds!\n");
	sleep(2); // sleep for 2 seconds

	printf("Waking Up and snoozing for another 2 seconds!\n");
	sleep(2); // sleep for 2 seconds

	printf("Finally, Woke Up!\n");
	return 0;
}
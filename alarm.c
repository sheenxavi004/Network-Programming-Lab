#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void alarm_handler(int signm)
{
	printf("Beeping....!\n");
}

int main()
{
	int i;
	signal(SIGALRM, alarm_handler); // Registering signal handler

	alarm(4); // Scheduled alarm after 3 seconds

	for(i = 0 ; i < 8 ; i++)
	{
		printf("Processing...!\n");
		sleep(1); // Sleep is executed to delay so that the alarm is executed
	}
	return 0;

}
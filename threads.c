#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *threadContent(void *v)
{
	// The executing thread body
	int *threadId = (int *)v;
	sleep(1);
	printf("Now running Thread No : %d ...\n", *threadId);
	return NULL; 
}

int main() 
{

	int i, n;
	pthread_t threadId; // Stores the thread ID

	// Reading the input n for creating n threads
	printf("Number of Threads : ");
	scanf("%d", &n);

	printf("Creating Threads...\n");
	for(i = 1 ; i <= n ; i++)
	{
		printf("-----------------------------\n");
		printf("Creating Thread No : %d\n", i);
		// Creating the thread
		pthread_create(&threadId, NULL, threadContent, (void *)&i);
		// Join is used to ensure that the threads wait for 
		// the currently executing threads to terminate
		pthread_join(threadId, NULL);
		printf("Escaping Thread No : %d\n", i);
		printf("-----------------------------\n");
	}
	   
	printf("Finished running the threads!\n");
	return 0;
}
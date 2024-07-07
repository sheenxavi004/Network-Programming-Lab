// Name   : readerwriter2.c
// Desc   : Program to demonstrate second readers-writers problem(writer's preference)
// Input  : None
// Output : Interaction of readers and writers with the shared resource
// Author : Sheen Xavier A
// Date   : 12/05/2021

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Semamphores for reader and writer processes
sem_t writer_reader;
pthread_mutex_t mutex; // Mutex lock
int data = 4; // Shared data
int writer_cnt = 0; // Keeps track of the count of readers

// Handles the operation of reader process
void *reader(void *rcno)
{
	sem_wait(&writer_reader); // Change to read mode
	// Read content
	printf("Reader ID : %d reads data from the shared resource as %d\n", *((int *)rcno), data);
	sem_post(&writer_reader); // Change to writer mode
}

void *writer(void *wcno)
{
	int prev_data = data;

	pthread_mutex_lock(&mutex); // Aquiring the mutex lock
	writer_cnt++; 	// Increment the number of writers currently writing

	if(writer_cnt == 1) // If we're the first writer block the reader
		sem_wait(&writer_reader); // Change the mode to writer mode

	pthread_mutex_unlock(&mutex); // Relinquish the mutex lock
	
	data = data * 4; // Perform modification to data
	printf("Writer ID : %d modified shared data from %d to %d\n", *((int *) wcno), prev_data, data);

	pthread_mutex_lock(&mutex);	// Aquire the mutex lock
	writer_cnt--; 	// Decrement the number of readers while exiting

	if(writer_cnt == 0) // If we're at the last writer relinquish control
		sem_post(&writer_reader); // Change mode back to reader

	pthread_mutex_unlock(&mutex); // Relinquish the mutex lock
}

int main()
{
	int i;
	pthread_t readers[5], writers[5]; // Reader and Writer process
	pthread_mutex_init(&mutex, NULL); // Initialize the mutex lock
	sem_init(&writer_reader, 0, 1);  // Initialize the semaphore associated with reader and writer

	int numbarray[5] = {1, 2, 3, 4, 5}; // For IDs of reader and writer

	for(i = 0 ; i < 5 ; i++) // Create Writer and Reader Processes
	{
		pthread_create(&writers[i], NULL, (void *)writer, (void *)&numbarray[i]);
		pthread_create(&readers[i], NULL, (void *)reader, (void *)&numbarray[i]);
	}
	sleep(1); // Bringing a delay
	pthread_mutex_destroy(&mutex); // Removing the semaphore and mutex lock 
	sem_destroy(&writer_reader);

	return 0;

}
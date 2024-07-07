// Name   : readerwriter.c
// Desc   : Program to demonstrate first readers-writers problem
// Input  : None
// Output : Interaction of readers and writers with the shared resource
// Author : Sheen Xavier A
// Date   : 04/05/2021

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Semamphores for reader and writer processes
sem_t writer_reader;
pthread_mutex_t mutex; // Mutex lock
int data = 4; // Shared data
int reader_cnt = 0; // Keeps track of the count of readers

// Handles the operation of reader process
void *reader(void *rcno)
{
	pthread_mutex_lock(&mutex); // Aquiring the mutex lock
	reader_cnt++; 	// Increment the number of readers currently reading

	if(reader_cnt == 1)
		sem_wait(&writer_reader); // If we're the first reader, block the reader

	pthread_mutex_unlock(&mutex); // Relinquish the mutex lock
	// Read content
	printf("Reader ID : %d reads data from the shared resource as %d\n", *((int *)rcno), data);

	pthread_mutex_lock(&mutex);	// Aquire the mutex lock
	reader_cnt--; 	// Decrement the number of readers while exiting

	// If we're the last reader executing, wake up the writer
	if(reader_cnt == 0)
		sem_post(&writer_reader);

	pthread_mutex_unlock(&mutex); // Relinquish the mutex lock
}

void *writer(void *wcno)
{
	int prev_data = data;
	sem_wait(&writer_reader); // Change the mode to writer mode
	data = data * 4; // Perform modification to data
	printf("Writer ID : %d modified shared data from %d to %d\n", *((int *) wcno), prev_data, data);
	sem_post(&writer_reader); // Change mode back to reader
}

int main()
{
	int i;
	pthread_t readers[5], writers[5]; // Reader and Writer process
	pthread_mutex_init(&mutex, NULL); // Initialize the mutex lock
	sem_init(&writer_reader, 0, 1);  // Initialize the semaphore associated with reader and writer

	int numbarray[5] = {1, 2, 3, 4, 5}; // For IDs of reader and writer

	for(i = 0 ; i < 5 ; i++) // Create Reader Processes
		pthread_create(&readers[i], NULL, (void *)reader, (void *)&numbarray[i]);

	for(i = 0 ; i < 5 ; i++) // Create Writer Processes
		pthread_create(&writers[i], NULL, (void *)writer, (void *)&numbarray[i]);

	for(i = 0 ; i < 5 ; i++) // Allowing multiple readers
		pthread_join(readers[i], NULL);

	for(i = 0 ; i < 5 ; i++) // Allowing multiple writers
		pthread_join(writers[i], NULL);

	sleep(1); // Bringing a delay
	pthread_mutex_destroy(&mutex); // Removing the semaphore and mutex lock 
	sem_destroy(&writer_reader);

	return 0;
}
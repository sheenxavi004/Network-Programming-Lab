// Name   : shread.c
// Desc   : Program to demonstrate IPC using Shared Memory
//          This program is used to read data from the Shared Memory
// Input  : None
// Output : Data that was transmitted
// Author : Sheen Xavier A
// Date   : 22/04/2021

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
	// Generates the unique which is stored into key
	key_t key = ftok("shared", 65);

	// Creates a shared memory and stores the generated
	// id in memid
	int memid = shmget(key, 1024, 0666 | IPC_CREAT);

	// Attaching string data to the shared memory segment
	char *data = (char *)shmat(memid, (void*)0, 0);

	printf("Data Recieved : %s\n", data); // Reading transmitted data

	// After reading, we detach data from shared memory
	shmdt(data); 

	// Destroying the shared memory
	shmctl(memid, IPC_RMID, NULL);

	return 0;
}
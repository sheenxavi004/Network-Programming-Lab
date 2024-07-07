// Name   : shwrite.c
// Desc   : Program to demonstrate IPC using Shared Memory
//          This program is used to write data into the Shared Memory
// Input  : Data to be transmitted
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

	printf("Data to be transmitted : ");
	scanf(" %[^\n]", data); // Writing data to be transmitted

	// Transmitted message
	printf("Successfully relayed the message : %s\n", data);

	// After writing, we detach data from shared memory
	shmdt(data);

	return 0;
}
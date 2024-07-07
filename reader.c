#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
 	// ftok to generate unique key
	int key = ftok("shmfile", 65);

	// shmegt returns an ID which is sid 
	int sid = shmget(key, 1024, 0666 | IPC_CREAT);

	// shmat to attach to shared memory
	char *str = (char*) shmat(sid, (void*)0, 0);

	// Data retrieved
	printf("Data read from memory : %s\n", str);

	// shmdt to detach from shared memory
	shmdt(str);

	//destroy the shared memory
	shmctl(sid, IPC_RMID, NULL);

	return 0;
}
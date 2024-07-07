// Name   : msgread.c
// Desc   : Program to demonstrate IPC using Message Queue
//          This program is used to read data from the Message Queue
// Input  : None
// Output : Data that was transmitted
// Author : Sheen Xavier A
// Date   : 22/04/2021

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Data structure for message queue
struct msg_buff {
	long msg_type;
	char msg_data[100];
}msg;

int main()
{
	key_t key; // Varible for storing unique key
	int msgid;

	// Generating the unique key
	key = ftok("msfile", 65);
	
	// Creates a message queue and stores
	// the generated id in msgid
	msgid = msgget(key, 0666 | IPC_CREAT);
	msg.msg_type = 1; // Setting message type as 1

	msgrcv(msgid, &msg, sizeof(msg), 1, 0); // Recieving the transmitted message

	printf("Data Recieved : %s\n", msg.msg_data);

	//Destroying the message queue
	msgctl(msgid, IPC_RMID, NULL);

	return 0;
}
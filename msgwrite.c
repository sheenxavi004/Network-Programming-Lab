// Name   : msgwrite.c
// Desc   : Program to demonstrate IPC using Message Queue
//          This program is used to write data into the Message Queue
// Input  : Data to be transmitted
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
	key = ftok("msgfile", 65);
	
	// Creates a message queue and stores
	// the generated id in msgid
	msgid = msgget(key, 0666 | IPC_CREAT);
	msg.msg_type = 1; // Setting message type as 1

	printf("Message to be transmitted : ");
	scanf(" %[^\n]", msg.msg_data); // Reading the message to be send

	// Transmitted message
	printf("Successfully relayed the message : %s\n", msg.msg_data);

	msgsnd(msgid, &msg, sizeof(msg), 0); // Sending the message contents

	return 0;
}
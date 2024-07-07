#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
 
int main()
{
    if (fork()== 0)
        printf("Now we're in the child process!\n");
    else
    {
        printf("Now we're in the parent process!\n");

        wait(NULL); // Freezing the parent and moving to child process

        printf("Exiting the child process!\n");
    }
 
    printf("End of Process!\n");
    return 0;
}
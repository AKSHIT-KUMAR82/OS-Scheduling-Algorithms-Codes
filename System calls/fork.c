/*
fork() System call creates a dublicate child copy of the calling process 
it return 3 values :
-ve (In case it failed to allocate resources to the process )
0 (In case child process is created and running)
+ve (Child process created and it's pid gets return to the parent process)


Orphan process : When parent exits after it's execution and child process is still running wihtout it's parent
Zombie Process : When child leaves after it's execution and parent is still running
*/

#include<stdio.h>
#include<unistd.h>

int main() {
    // Create a new process using fork
    pid_t pid = fork();
    if(pid==0){
        printf("Child process created....\n");
        printf("Child id : %d\n",getpid());
        printf("Parent id : %d\n",getppid());
    }
    else if(pid>0){
        printf("Parent process created....\n");
        printf("Child id : %d\n",pid);
        printf("Parent id : %d\n",getpid());
    }
    else{
        printf("System failed to allocate resources....\n");
    }
    return 0;
}

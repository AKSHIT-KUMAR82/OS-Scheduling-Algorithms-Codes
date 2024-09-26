/* Here we are doing program 3 from file*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){

    //Zombie Process...
    pid_t pid1=fork();
    if(pid1<0){
        printf("Child process not created...\n");
        return -1;
    }
    else if(pid1==0){
        printf("Child process created...\n");
        //Now our task is to list all the files the system...
        execlp("ls","ls","-l",(char *)NULL);
        exit(0);
    }
    else{
        printf("Parent process created...\n");
        wait(NULL);
        printf("Parent process id : ",getpid());
    }


    //Orphan Process...
    pid_t pid2=fork();
    if(pid2<0){
        printf("Child process2 not created...\n");
        return -1;
    }
    else if(pid2==0){
        printf("Child process2 created...\n");
        //Now our task is to list all the files the system...
        sleep(5);
        printf("Child process2 work done...\n");
        exit(0);
    }
    else{
        printf("Parent process created...\n");
        exit(0);
    }

}
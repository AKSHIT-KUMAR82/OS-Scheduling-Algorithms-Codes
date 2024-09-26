/*
This Algorithm is used to check whether our system is in safe state or not. In other way we can say our system is deadlock free or not.
Safe State : If we get any single safe sequence then we can say that our system is in safe state else unsafe state(DeadLock)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Process Structure which holds data about their Maximum requirement, Allocated and Need for each type of resource available in our system...
typedef struct process_struct
{
    int Max[100];
    int Allocated[100];
    int Need[100];
} processes_struct;

//Input function.....
void Input(int No_Processes, processes_struct Process[], int available[], int No_Resources)
{
    for (int i = 0; i < No_Processes; i++)
    {
        printf("****Enter Max-Requirement and Allocated Resources for %d process****\n",i+1);
        for (int j = 0; j < No_Resources; j++)
        {
            scanf("%d%d", &Process[i].Max[j], &Process[i].Allocated[j]);
            Process[i].Need[j] = Process[i].Max[j] - Process[i].Allocated[j];
        }
    }

    // Now, Lets take input for available units remaining after allocation of resources to each process...Instead of this we can calculate it manually as well, Just a little bit change in code is required.
    //***** What change in code ***** ??
    /* We can take input total units of each resource available in our system and at the time we are taking input for allocated resources for each process, 
    We can subtract it from total available resources and therefore we can calculate available resources in our system for each type of resource after their allocation*/

    printf("Enter Available Units for each process : \n");
    for (int i = 0; i < No_Resources; i++)
    {
        scanf("%d", &available[i]);
    }
}

//Fuction to check is we are getting some safe sequence or not, Which ensures that our system is in safe state or not (i.e Deadlock or not)....
int Is_System_Safe(int No_Processes, int No_Resources, int SafeSequence[], processes_struct Process[], int available[])
{
    bool Is_Completed[No_Processes];
    int completed=0;
    bool proceed = true,flag;
    for (int i = 0; i < No_Processes; i++)
        Is_Completed[i] = false;

    int k = 0;

    while (proceed)
    {
        proceed = false;
        for (int i = 0; i < No_Processes; i++)
        {
            flag=true;
            if (Is_Completed[i] == false)
            {
                for(int j=0;j<No_Resources;j++){
                    if(Process[i].Need[j]>available[j]){
                        flag=false;
                        break;
                    }
                }
                if(flag){
                    completed++;
                    SafeSequence[k++]=i+1;
                    for(int j=0;j<No_Resources;j++)
                          available[j]+=Process[i].Allocated[j];
                    Is_Completed[i]=true;
                    proceed=true;
                }
            }
        }
    }
    if(completed==No_Processes)
       return 1;
    
    return 0;
       
}

int main()
{
    int No_Processes, No_Resources;
    printf("Enter the no. of Processes : ");
    scanf("%d", &No_Processes);
    printf("Enter the no. of resources available in our system : ");
    scanf("%d", &No_Resources);
    processes_struct Process[No_Processes];
    int available[No_Resources];

    // Let's Take Input....
    Input(No_Processes, Process, available, No_Resources);
    int SafeSequence[No_Processes];
    if (Is_System_Safe(No_Processes, No_Resources, SafeSequence, Process, available))
    {
        printf("System is in safe state...\n");
        printf("******SAFE SEQUENCE******\n");
        for(int i=0;i<No_Processes;i++){
            printf("%d ",SafeSequence[i]);
        }
    }
    else
    {
        printf("System is not in safe state, Hence Deadlock....\n");
    }

    return 0;
}
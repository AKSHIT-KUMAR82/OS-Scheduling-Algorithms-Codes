//Basic Libraries...
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//To find max of 2 numbers...
#define max(a,b) a>=b?a:b

//Process Structure...
struct process_struct{
    int pid;
    int at,bt;
    int st,ct;
    int rt,tat,wt;
}pro[100];

//To sort values based on arrival time in ascending order...
int ComparatorAT(const void *a,const void *b){
    int at1=((struct process_struct *)a)->at;
    int at2=((struct process_struct *)b)->at;
    if(at1<at2)
       return -1;
    if(at1>=at2)
       return 1; //In this case we have to sort...
}

int main(){
    int n;
    int remaining_bt[100]; //Premptive Algorithm that's why to keep track of remmaining burst time...
    printf("Enter the no. of processes : ");
    scanf("%d",&n);
    printf("Enter the arrival and burst time of the processes : \n");
    for(int i=0;i<n;i++){
        scanf("%d%d",&pro[i].at,&pro[i].bt);
        pro[i].pid=i+1;
        remaining_bt[i]=pro[i].bt; //Intializes it at first for every process...
    }

    int quantum;
    printf("Enter the quantum time : ");
    scanf("%d",&quantum);

    //Function to sort based on the condition inside comparator...
    qsort((void *)pro,n,sizeof(struct process_struct),ComparatorAT);

    bool visited[100]={false},first_process=true,is_completed[100]={false};
    int queue[100],front=-1,rear=-1; //Ready queue to keep track which process is next execution...
    int sum_rt=0,sum_tat=0,sum_wt=0,start_time,life_cycle,current=0,idle_time=0,completed=0;

    //Intializes it for the very first process...
    queue[++rear]=0;
    visited[0]=true;
    int index;

    while(completed!=n){
        index=queue[++front]; //Takes out the process index for execution...

        //It will run exactly n times at the starting of each process...
        if(remaining_bt[index]==pro[index].bt){

            //This tells us exact start time, As it might be possible that there is some gap exists between arrival time and end time of previous process....
            pro[index].st=max(pro[index].at,current);

            //To add up the exact gap for finding out the idle time of cpu...
            idle_time+=first_process?0:(pro[index].st-current);
            current=pro[index].st;

            //It helps us to find out the life cycle of whole scheduling of processes...
            if(first_process){
                start_time=pro[index].st;
                first_process=false;
            }
        }

        //Now, Two cases based on the remmaining burst time of the processes...
        if(remaining_bt[index]>quantum){
            current+=quantum; 
            remaining_bt[index]-=quantum; 
        }
        else{
            //Process Ends here as remmaining time is less than quantum time....
            current+=remaining_bt[index];
            remaining_bt[index]=0;
            is_completed[index]=true;
            pro[index].ct=current;
            pro[index].rt=pro[index].st-pro[index].at;
            pro[index].tat=pro[index].ct-pro[index].at;
            pro[index].wt=pro[index].tat-pro[index].bt;

            sum_rt+=pro[index].rt;
            sum_tat+=pro[index].tat;
            sum_wt+=pro[index].wt;
            completed++;
        }

        //Now, Queuing the processes arrived in between the current process execution for quantum time...
        for(int i=1;i<n;i++){
            if(pro[i].at<=current&&visited[i]==false){
                queue[++rear]=i;
                //Mark them visited as they came into the ready queue...
                visited[i]=true;
            }
        }

        //Now, Once current process gets executed then queued it at end if it's not fully executed...
        if(is_completed[index]==false){
            queue[++rear]=index;
        }
    }

    printf("Processes\tAt\tBt\tSt\tCt\tRt\tTat\tWt\n");
    life_cycle=current-start_time;
    float CPU_efficiency=((life_cycle-idle_time)/life_cycle)*100;
    for(int i=0;i<n;i++){
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i+1,pro[i].at,pro[i].bt,pro[i].st,pro[i].ct,pro[i].rt,pro[i].tat,pro[i].wt);
    }
    printf("Average Turn Around Time : %f\n",(float)sum_tat/n);
    printf("Average Response Time : %f\n",(float)sum_rt/n);
    printf("Average Waiting Time : %f\n",(float)sum_wt/n);
    printf("CPU Efficiency : %f",CPU_efficiency);
    return 0;

}
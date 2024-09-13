//All basic libraries....
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

//Process Structure....
struct process_struct{
    int pid;
    int at,bt;
    int st,ct;
    int rt,tat,wt;
    int priority; //For getting priority for each process....
}pro[100];

int main(){
    int n;
    //Taking input for the processes...
    printf("Enter the no. of processes in the system : ");
    scanf("%d",&n);
    
    printf("Enter the arrival,burst time and priority of the processes respectively : \n");
    for(int i=0;i<n;i++){
        scanf("%d%d%d",&pro[i].at,&pro[i].bt,&pro[i].priority);
        pro[i].pid=i+1;
    }
    
    int completed=0,current=0,sum_rt=0,sum_tat=0,sum_wt=0,index=-1,Min_priority=INT_MAX,idle_time=0,length_cycle,start_time;
    bool is_completed[100]={false},first_process=true;
    
    //Here we are assuming that smaller number has greater priority....
    while(completed!=n){
        index=-1;
        Min_priority=INT_MAX;
        for(int i=0;i<n;i++){
            if(pro[i].at<=current&&is_completed[i]==false){
                if(pro[i].priority<Min_priority){
                    Min_priority=pro[i].priority;
                    index=i;
                }
                else if(pro[i].priority==Min_priority&&pro[i].at<pro[index].at){
                    index=i;
                }
            }
        }
        
        if(index==-1){ //It means that No process is available in the ready queue for the current time...
            current++;
            idle_time++;
        }
        else{
            if(first_process){
                start_time=current;
                first_process=false;
            }
            pro[index].st=current;
            pro[index].ct=current+pro[index].bt;
            pro[index].rt=pro[index].st-pro[index].at;
            pro[index].tat=pro[index].ct-pro[index].at;
            pro[index].wt=pro[index].tat-pro[index].bt;
            
            sum_wt+=pro[index].wt;
            sum_tat+=pro[index].tat;
            sum_rt+=pro[index].rt;
            completed++;
            is_completed[index]=true;
            current=pro[index].ct;
        }
    }

    printf("Processes\tAt\tBt\tSt\tCt\tRt\tTat\tWt\n");
    length_cycle=current-start_time;
    float CPU_efficiency=((length_cycle-idle_time)/length_cycle)*100;
    for(int i=0;i<n;i++){
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i+1,pro[i].at,pro[i].bt,pro[i].st,pro[i].ct,pro[i].rt,pro[i].tat,pro[i].wt);
    }
    printf("Average Turn Around Time : %f\n",(float)sum_tat/n);
    printf("Average Response Time : %f\n",(float)sum_rt/n);
    printf("Average Waiting Time : %f\n",(float)sum_wt/n);
    printf("CPU Efficiency : %f",CPU_efficiency);
    
}
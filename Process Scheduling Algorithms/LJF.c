//Here we are going to write a C program for the Longest job first scheduling algorithm in Non-premptive mode.....

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

struct program_struc{ //Process structure...
    int pid;
    int at,bt;
    int st,ct;
    int rt,tat,wt;
}pro[100];

int main(){
    int n;
    printf("Enter the no. of processes : ");
    scanf("%d",&n);
    printf("Enter the arrival and burst time of the processes : \n");
    for(int i=0;i<n;i++){
        scanf("%d%d",&pro[i].at,&pro[i].bt);
        pro[i].pid=i+1;
    }
    bool is_remaining[100]={false},first_process=true;
    int completed=0,sum_rt=0,sum_tat=0,sum_wt=0,life_cycle,idle_time=0,current=0;
    int index=-1,Largest_bt=INT_MIN,Start_time=0;
    while(completed!=n){
        index=-1;
        Largest_bt=INT_MIN;
        for(int i=0;i<n;i++){
            if(pro[i].at<=current&&is_remaining[i]!=true){
                if(pro[i].bt>Largest_bt){
                    index=i;
                    Largest_bt=pro[i].bt;
                }
                else if(pro[i].bt==Largest_bt&&pro[i].at<pro[index].at){
                    index=i;
                }
                
            }
        }
        if(index==-1){
            //We have no process available for the current time...
            idle_time++;
            current++;
        }
        else{
            if(first_process){
                Start_time=current;
                first_process=false;
            }
            pro[index].st=current;
            pro[index].ct=current+pro[index].bt; //As processes are non-premptive....
            pro[index].rt=pro[index].st-pro[index].at;
            pro[index].tat=pro[index].ct-pro[index].at;
            pro[index].wt=pro[index].tat-pro[index].bt;
            
            sum_rt+=pro[index].rt;
            sum_wt+=pro[index].wt;
            sum_tat+=pro[index].tat;
            completed++;
            current=pro[index].ct;
            is_remaining[index]=true;
        }
    }
    
    printf("Processes\tAt\tBt\tSt\tCt\tRt\tTat\tWt\n");
    life_cycle=current-Start_time;
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
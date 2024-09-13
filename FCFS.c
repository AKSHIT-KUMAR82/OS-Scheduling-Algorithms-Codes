#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#define max(a,b) a>=b?a:b


struct process_struct{
    int pid;
    int at,bt;
    int st,ct;
    int rt,tat,wt;
}pro[100];

int ComparatorAt(const void *a,const void *b){
    int at1=((struct process_struct*)a)->at;
    int at2=((struct process_struct*)b)->at;
    if(at1<at2){
        return -1; //No sorting required...
    }
    else{
        return 1; //Sorting required...
    }
}


int main(){
    int n;
    printf("Enter the no. of processes available in the system : ");
    scanf("%d",&n);
    printf("Enter arrival and burst time of processes : \n");
    for(int i=0;i<n;i++){
        scanf("%d%d",&pro[i].at,&pro[i].bt);
        pro[i].pid=i+1;
    }
    //Now, Lets sort processes based on arrival time in increasing order....
    qsort((void *)pro,n,sizeof(struct process_struct),ComparatorAt);
    bool first_process=true;
    int sum_rt=0,sum_tat=0,sum_wt=0,idle_time=0,start_time,life_cycle;
    for(int i=0;i<n;i++){
        pro[i].st=first_process?pro[i].at:max(pro[i].at,pro[i-1].ct);
        pro[i].ct=pro[i].st+pro[i].bt;
        pro[i].rt=pro[i].st-pro[i].at;
        pro[i].tat=pro[i].ct-pro[i].at;
        pro[i].wt=pro[i].tat-pro[i].bt;

        sum_rt+=pro[i].rt;
        sum_tat+=pro[i].tat;
        sum_wt+=pro[i].wt;
        idle_time+=pro[i].st-pro[i-1].ct;
        if(first_process){
            start_time=pro[i].at;
            first_process=false;
        }
    }

    printf("Processes\tAt\tBt\tSt\tCt\tRt\tTat\tWt\n");
    life_cycle=pro[n-1].ct-start_time;
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
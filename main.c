#include <stdio.h>

#define SIZE 100

void calWaitingTime(int waitingTime[], int num, int time){
    for (int x=0; x<num; x++){
       waitingTime[x]=x*time;
    }
}

void calTurnaroundTime(int burstTime[],int turnaroundTime[], int num, int time){
  int done=0;
   while(done!=num){
      done=0;
      for (int x=0; x<num; x++){
         if (burstTime[x]==0){
            done+=1;
         }
         else if (burstTime[x]<time){
            turnaroundTime[x]+=burstTime[x];
            for (int y=0; y<num; y++){
              if (burstTime[y]!=0 && y!=x){
                turnaroundTime[y]+=burstTime[x];
              }
            }
            burstTime[x]=0;
         }
         else{
            turnaroundTime[x]+=time;
            burstTime[x]-=time;
            for (int y=0; y<num; y++){
              if(burstTime[y]!=0 && y!=x){
                turnaroundTime[y]+=time;
              }
            }
         }
      }
   }
}

int main(void){
    int processID[SIZE]={0};
    int burstTime[SIZE]={0};
    int copyBurst[SIZE]={0};
    int waitingTime[SIZE]={0};
    int turnaroundTime[SIZE]={0};
    int totalWaiting=0;
    int totalTurnaround=0;
    int num=0;
    int time=0;

    printf("Number of Processes: ");
    scanf("%d", &num);
    while(num>SIZE){
       printf("The number of processes inputted exceed the program's capacity\n");
       printf("Number of Processes: ");
       scanf("%d", &num);
    }
    printf("Time Quantum: ");
    scanf("%d", &time);
    printf("----------------------------------------------------\n");

    for (int x=0; x<num; x++){
       printf("Process ID:");
       scanf("%d", &processID[x]);
       printf("Burst Time:");
       scanf("%d", &burstTime[x]);
       copyBurst[x]=burstTime[x];
       printf("----------------------------------------------------\n");
    }

    calWaitingTime(waitingTime, num, time);
    calTurnaroundTime(copyBurst, turnaroundTime, num, time);

    //printf("Process ID          Burst Time         Waiting Time       Turnaround Time");

    printf("+=================+============================+=================+=====================+\n");
    printf("|   Process ID             Burst Time              Waiting Time      Turnaround Time   |\n");
    printf("+=================+============================+=================+=====================+\n");

    for(int x=0; x<num; x++){
      printf("%11d %20d %20d %20d\n", processID[x], burstTime[x], waitingTime[x], turnaroundTime[x]);
    }

    printf("+=================+============================+=================+=====================+\n");

    for (int x=0; x<num; x++){
       totalWaiting += waitingTime[x];
       totalTurnaround += turnaroundTime[x];
    }

    float avgWaiting=totalWaiting/num;
    float avgTurnaround=totalTurnaround/num;
    printf("Average Waiting Time: %.2f\n", avgWaiting);
    printf("Average Turnaround Time: %.2f\n", avgTurnaround);
}






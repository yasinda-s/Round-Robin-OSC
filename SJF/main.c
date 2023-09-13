#include <stdio.h>

#define SIZE 100

void calWaitingTime(int waitingTime[], int num, int time, int overhead){
    for (int x=0; x<num; x++){
       waitingTime[x]=x*(time+overhead);
    }
}

void calTurnaroundTime(int burstTime[],int turnaroundTime[], int num, int time, int overhead){
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
                turnaroundTime[y]+=overhead;
              }
            }
            burstTime[x]=0;
         }
         else{
            burstTime[x]-=time;
            for (int y=0; y<num; y++){
              if(burstTime[y]!=0){
                turnaroundTime[y]+=time;
                turnaroundTime[y]+=overhead;
              }
              else if(y==x){
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
    int overhead=0;

    printf("Round Robin with Overhead\n");
    printf("Number of Processes: ");
    scanf("%d", &num);
    while(num>SIZE){
       printf("The number of processes inputted exceed the program's capacity\n");
       printf("Number of Processes: ");
       scanf("%d", &num);
    }
    printf("Time Quantum: ");
    scanf("%d", &time);
    printf("Overhead: ");
    scanf("%d", &overhead);
    while(overhead>=time){
       printf("Overhead duration cannot exceed the time quantum\n");
       printf("Overhead: ");
       scanf("%d", &overhead);
    }
    printf("----------------------------------------------------\n");

    for (int x=0; x<num; x++){
       printf("Process ID:");
       scanf("%d", &processID[x]);
       printf("Burst Time:");
       scanf("%d", &burstTime[x]);
       copyBurst[x]=burstTime[x];
       printf("----------------------------------------------------\n");
    }

    calWaitingTime(waitingTime, num, time, overhead);
    calTurnaroundTime(copyBurst, turnaroundTime, num, time, overhead);

    printf("+=================+============================+=================+=====================+\n");
    printf("|   Process ID             Burst Time              Waiting Time       Turnaround Time  |\n");
    printf("+=================+============================+=================+=====================+\n");

    for(int x=0; x<num; x++){
      printf("%10d %23d %23d %20d\n", processID[x], burstTime[x], waitingTime[x], turnaroundTime[x]);
    }

    printf("+=================+============================+=================+=====================+\n");

    for (int x=0; x<num; x++){
       totalWaiting += waitingTime[x];
       totalTurnaround += turnaroundTime[x];
    }

    float avgWaiting=totalWaiting/num;
    float avgTurnaround=totalTurnaround/num;

    printf("\n");
    printf("Average Waiting Time: %.2f\n", avgWaiting);
    printf("Average Turnaround Time: %.2f", avgTurnaround);
}

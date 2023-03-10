#include "../header/v4zha.h"
#include <stdio.h>

void FCFS(int n, Vec);

int main() {
  int n;
  printf("Enter the number of processes\n");
  scanf("%d", &n);
  printf("Enter burst time of each process\n");
  Vec btime = new_vec(n);
  FCFS(n, btime);
  freeVec(btime);
}

void FCFS(int n, Vec b_time) {
  Vec w_time = Vector(n);
  Vec ta_time = Vector(n);
  v_val(w_time, 0) = 0;
  v_val(ta_time, 0) = v_val(b_time, 0);
  int *w_data = w_time->data;
  int *b_data = b_time->data;
  //
  // Assign waiting time
  // let Arrival time of all process = 0 ;
  // In FCFS , first proc waiting time =0
  // adutha proc_waiting time=waiting time of prev process + burst time of prev
  // process
  //
  //         p1         p2             p3
  //  0[---------]3[------------]10[---------]
  //
  //   So waiting time of p2 = w_time of p1 (0) + Burst time  of p1 (3)=3
  // last process vere continue this : )
  //
  for (int i = 1; i < n; i++) {
    //
    // use v_val(w_time,i) as alternative : )
    //  then why use array operator and w_data ? , veruthe , alternative method
    //  : )
    //
    w_data[i] = w_data[i - 1] + b_data[i - 1];
  }
  // Calculate TurnAround time
  //
  //          p1         p2             p3
  //   0[---------]3[------------]10[-------------]
  //    ^                         |              ^
  //    |{      wtime[i]         }|{ b_time[i]  }|
  //    |                         |              |
  //    |{ wtime[i-1]+btime[i-1] }|              |
  //    |                         |              |
  //    -----------------------------------------
  //   TurnAround time of p3 =wtime[i]+btime[i]
  //
  for (int i = 0; i < n; i++)
    v_val(ta_time, i) = v_val(w_time, i) + v_val(b_time, i);
  printf("Proc.No\t\tBurstTime\tWaitingTime\tTurnAroundTime\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t\t%d\t\t%d\t\t%d\n", i, v_val(b_time, i), v_val(w_time, i),
           v_val(ta_time, i));
  }
  float avg_wt = (float)vecSum(w_time) / n;
  float avg_tat = (float)vecSum(ta_time) / n;
  printf("Average Waiting time : %f\n", avg_wt);
  printf("Average TurnAround time : %f\n", avg_tat);

  freeVec(w_time);
  freeVec(ta_time);
}

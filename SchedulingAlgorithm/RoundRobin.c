//Round Robin Schduling
#include <stdio.h>

int main() {
    int i, nop, ct = 0, time_quantum, counter;
    int total_wait_time = 0, total_turnaround_time = 0;
    int arrival_time[10], burst_time[10], rt[10], completed[10] = {0};
    float average_waiting_time, average_turnaround_time;

    printf("Enter total number of processes: ");
    scanf("%d", &nop);
    counter = nop;

    for (i = 0; i < nop; i++) {
        printf("Enter Details of process[%d]\n", i + 1);
        printf("Enter arrival time: ");
        scanf("%d", &arrival_time[i]);
        printf("Burst Time: ");
        scanf("%d", &burst_time[i]);
        rt[i] = burst_time[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    printf("\nProcess ID\tBurst Time\tTurnaround Time\tWaiting Time\n");

    int all_done = 0, executed;
    while (all_done != nop) {
        executed = 0;
        for (i = 0; i < nop; i++) {
            if (arrival_time[i] <= ct && rt[i] > 0) {
                executed = 1;
                if (rt[i] <= time_quantum) {
                    ct += rt[i];
                    rt[i] = 0;
                    completed[i] = 1;
                    all_done++;

                    int turnaround_time = ct - arrival_time[i];
                    int waiting_time = turnaround_time - burst_time[i];

                    printf("Process[%d]\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], turnaround_time, waiting_time);

                    total_wait_time += waiting_time;
                    total_turnaround_time += turnaround_time;
                } else {
                    rt[i] -= time_quantum;
                    ct += time_quantum;
                }
            }
        }
        if (executed == 0) {
            ct++;
        }
    }

    average_waiting_time = (float)total_wait_time / nop;
    average_turnaround_time = (float)total_turnaround_time / nop;

    printf("\nAvg Waiting time: %.2f", average_waiting_time);
    printf("\nAvg Turnaround time: %.2f\n", average_turnaround_time);

    return 0;
}

#include <stdio.h>

int main() {
    int bt[10], priority[10], rt[10], completiontime, i, highest_priority;
    int remain = 0, n, time = 0, sum_wait = 0, sum_turnaround = 0;

    printf("Enter number of processes: \n");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter Details of process[%d]\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority: ");
        scanf("%d", &priority[i]);
        rt[i] = bt[i];
    }

    printf("\nProcess ID\tTurnaround Time\t\tWaiting Time\n");

    while (remain != n) {
        highest_priority = -1;

        for (i = 0; i < n; i++) {
            if (rt[i] > 0) {
                if (highest_priority == -1 || priority[i] < priority[highest_priority]) {
                    highest_priority = i;
                }
            }
        }

        if (highest_priority == -1) continue;

        time += bt[highest_priority];
        completiontime = time;
        int turnaround_time = completiontime;
        int waiting_time = turnaround_time - bt[highest_priority];

        printf("\nP[%d]\t\t%d\t\t%d", highest_priority + 1, turnaround_time, waiting_time);

        sum_wait += waiting_time;
        sum_turnaround += turnaround_time;
        rt[highest_priority] = 0;
        remain++;
    }

    printf("\nAvg Waiting time: %.2f", sum_wait * 1.0 / n);
    printf("\nAvg Turnaround time: %.2f\n", sum_turnaround * 1.0 / n);

    return 0;
}

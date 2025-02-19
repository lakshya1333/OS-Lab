#include <stdio.h>

int main() {
    int at[10], bt[10], rt[10], completiontime, i, smallest;
    int remain = 0, n, time, sum_wait = 0, sum_turnaround = 0;

    printf("Enter number of processes: \n");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter Details of process[%d]\n", i + 1);
        printf("Enter arrival time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    printf("\nProcess ID\tBurst Time\tTurnaround Time\tWaiting Time\n");

    for (time = 0; remain != n; time++) {
        smallest = -1;

        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                if (smallest == -1 || rt[i] < rt[smallest]) {
                    smallest = i;
                }
            }
        }

        if (smallest == -1) continue;

        rt[smallest]--;

        if (rt[smallest] == 0) {
            remain++;
            completiontime = time + 1;
            int turnaround_time = completiontime - at[smallest];
            int waiting_time = turnaround_time - bt[smallest];

            printf("\nP[%d]\t|\t%d\t|\t%d", smallest + 1, turnaround_time, waiting_time);

            sum_wait += waiting_time;
            sum_turnaround += turnaround_time;
        }
    }

    printf("\nAvg Waiting time: %.2f", sum_wait * 1.0 / n);
    printf("\nAvg Turnaround time: %.2f\n", sum_turnaround * 1.0 / n);

    return 0;
}

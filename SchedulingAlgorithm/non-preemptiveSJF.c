#include <stdio.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int waiting;
    int turnaround;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];


    for (int i = 0; i < n; i++) {
        printf("Enter arrival and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].pid = i + 1;
    }


    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].arrival) {
            currentTime = p[i].arrival;
        }


        int shortest = i;
        for (int j = i + 1; j < n; j++) {
            if (p[j].arrival <= currentTime && p[j].burst < p[shortest].burst) {
                shortest = j;
            }
        }


        struct Process temp = p[i];
        p[i] = p[shortest];
        p[shortest] = temp;


        p[i].waiting = currentTime - p[i].arrival;
        p[i].turnaround = p[i].waiting + p[i].burst;
        currentTime += p[i].burst;
    }

    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    float totalWaiting = 0, totalTurnaround = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
        totalWaiting += p[i].waiting;
        totalTurnaround += p[i].turnaround;
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaiting / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaround / n);

    return 0;
}


#include <stdio.h>

struct Process {
    int id;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};

void findWaitingTime(struct Process processes[], int n) {
    processes[0].waitingTime = 0; 
    for (int i = 1; i < n; i++) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }
}

void findTurnaroundTime(struct Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

void calculateFCFS(struct Process processes[], int n) {
    findWaitingTime(processes, n);
    findTurnaroundTime(processes, n);

    printf("\nProcess	Burst Time	Waiting Time	Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }
    printf("\nAverage Waiting Time: %.2f", totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("P%d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
    }

    calculateFCFS(processes, n);
    return 0;
}

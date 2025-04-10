#include <stdio.h>
#include <stdlib.h>

#define MAX 10

struct Task {
    int id;
    int period;
    int burst;
    int deadline;
    int remaining;
    int next_arrival;
};


int compareRMS(const void *a, const void *b) {
    return ((struct Task *)a)->period - ((struct Task *)b)->period;
}

int compareEDF(const void *a, const void *b) {
    return ((struct Task *)a)->deadline - ((struct Task *)b)->deadline;
}

void simulateRMS(struct Task tasks[], int n, int simTime) {
    printf("\n---- Rate Monotonic Scheduling ----\n");

    struct Task taskList[MAX];
    for (int i = 0; i < n; i++) taskList[i] = tasks[i];
    qsort(taskList, n, sizeof(struct Task), compareRMS);

    for (int time = 0; time < simTime; time++) {
        for (int i = 0; i < n; i++) {
            if (time == taskList[i].next_arrival) {
                taskList[i].remaining = taskList[i].burst;
                taskList[i].next_arrival += taskList[i].period;
            }
        }

        int scheduled = -1;
        for (int i = 0; i < n; i++) {
            if (taskList[i].remaining > 0) {
                scheduled = i;
                break;
            }
        }

        if (scheduled != -1) {
            printf("Time %2d: Running P%d\n", time, taskList[scheduled].id);
            taskList[scheduled].remaining--;
        } else {
            printf("Time %2d: CPU is IDLE\n", time);
        }
    }
}

void simulateEDF(struct Task tasks[], int n, int simTime) {
    printf("\n---- Earliest Deadline First Scheduling ----\n");

    struct Task taskList[MAX];
    for (int i = 0; i < n; i++) taskList[i] = tasks[i];

    for (int time = 0; time < simTime; time++) {
        for (int i = 0; i < n; i++) {
            if (time == taskList[i].next_arrival) {
                taskList[i].remaining = taskList[i].burst;
                taskList[i].deadline = time + taskList[i].period;
                taskList[i].next_arrival += taskList[i].period;
            }
        }

        qsort(taskList, n, sizeof(struct Task), compareEDF);

        int scheduled = -1;
        for (int i = 0; i < n; i++) {
            if (taskList[i].remaining > 0) {
                scheduled = i;
                break;
            }
        }

        if (scheduled != -1) {
            printf("Time %2d: Running P%d (Deadline: %d)\n", time, taskList[scheduled].id, taskList[scheduled].deadline);
            taskList[scheduled].remaining--;
        } else {
            printf("Time %2d: CPU is IDLE\n", time);
        }
    }
}

int main() {
    int n;
    int simTime;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    struct Task tasks[MAX];

    for (int i = 0; i < n; i++) {
        printf("Enter period and burst time for Task P%d: ", i + 1);
        scanf("%d%d", &tasks[i].period, &tasks[i].burst);
        tasks[i].id = i + 1;
        tasks[i].remaining = 0;
        tasks[i].next_arrival = 0;
        tasks[i].deadline = tasks[i].period;
    }

    printf("Enter simulation time: ");
    scanf("%d", &simTime);

    simulateRMS(tasks, n, simTime);
    simulateEDF(tasks, n, simTime);

    return 0;
}

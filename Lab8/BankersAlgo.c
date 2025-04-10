#include <stdio.h>
#include <stdbool.h>

#define P 5
#define R 3

int available[R];
int max[P][R];
int allocation[P][R];
int need[P][R];

bool isSafe() {
    int work[R];
    bool finish[P] = {false};
    int safeSequence[P];

    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < R; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    safeSequence[count++] = i;
                    found = true;
                }
            }
        }
        if (!found) {
            return false;
        }
    }

    printf("The system is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++) {
        printf("P%d", safeSequence[i]);
        if (i != P - 1) printf(" -> ");
    }
    printf("\n");
    return true;
}


bool requestResources(int process, int request[R]) {
    for (int i = 0; i < R; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Process exceeded its maximum claim.\n");
            return false;
        }
        if (request[i] > available[i]) {
            printf("Resources not available, process must wait.\n");
            return false;
        }
    }

    for (int i = 0; i < R; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    if (!isSafe()) {
        for (int i = 0; i < R; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        printf("Request denied to maintain a safe state.\n");
        return false;
    }
    printf("Request granted.\n");
    return true;
}

int main() {
    printf("Enter the available resources: \n");
    for (int i = 0; i < R; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum demand for each process: \n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocated resources for each process: \n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    if (isSafe()) {
        printf("The system is in a safe state.\n");
    } else {
        printf("The system is NOT in a safe state.\n");
    }

    int process, request[R];
    printf("Enter the process number making a request: ");
    scanf("%d", &process);

    printf("Enter the resource request for process %d: ", process);
    for (int i = 0; i < R; i++) {
        scanf("%d", &request[i]);
    }

    requestResources(process, request);
    return 0;
}



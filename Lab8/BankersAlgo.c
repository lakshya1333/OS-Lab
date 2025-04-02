#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];


bool isSafe(int processes[], int n, int m) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }
    
    int safeSequence[MAX_PROCESSES];
    int count = 0;
    
    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                bool canAllocate = true;
                for (int r = 0; r < m; r++) {
                    if (need[p][r] > work[r]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int r = 0; r < m; r++) {
                        work[r] += allocation[p][r];
                    }
                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            return false;
        }
    }
    
    printf("System is in a safe state. Safe sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}


bool requestResources(int processID, int request[]) {
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > need[processID][i] || request[i] > available[i]) {
            printf("Request cannot be granted immediately.\n");
            return false;
        }
    }
    
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[processID][i] += request[i];
        need[processID][i] -= request[i];
    }
    
    if (!isSafe((int[]){0, 1, 2, 3, 4}, MAX_PROCESSES, MAX_RESOURCES)) {
        for (int i = 0; i < MAX_RESOURCES; i++) {
            available[i] += request[i];
            allocation[processID][i] -= request[i];
            need[processID][i] += request[i];
        }
        printf("Request leads to unsafe state, rolling back.\n");
        return false;
    }
    
    printf("Request granted.\n");
    return true;
}

int main() {
    int processes[MAX_PROCESSES] = {0, 1, 2, 3, 4};
    int n = MAX_PROCESSES, m = MAX_RESOURCES;
    
    printf("Enter available resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }
    
    printf("Enter maximum resource allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }
    
    printf("Enter allocated resource matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
    
    if (!isSafe(processes, n, m)) {
        printf("System is in an unsafe state!\n");
        return 1;
    }
    
    int processID, request[MAX_RESOURCES];
    printf("Enter process ID making a request: ");
    scanf("%d", &processID);
    printf("Enter resource request: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &request[i]);
    }
    
    requestResources(processID, request);
    
    return 0;
}

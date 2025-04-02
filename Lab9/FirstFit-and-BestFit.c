 #include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int allocated;
} Hole;


typedef struct {
    int size;
    int allocated_to;
} Process;


void firstFit(Hole *holes, int nh, Process *processes, int np) {
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nh; j++) {
            if (holes[j].size >= processes[i].size && holes[j].allocated == 0) {
                processes[i].allocated_to = j;
                holes[j].size -= processes[i].size;
                break;
            }
        }
    }
}


void bestFit(Hole *holes, int nh, Process *processes, int np) {
    for (int i = 0; i < np; i++) {
        int bestIdx = -1;
        for (int j = 0; j < nh; j++) {
            if (holes[j].size >= processes[i].size && holes[j].allocated == 0) {
                if (bestIdx == -1 || holes[j].size < holes[bestIdx].size) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            processes[i].allocated_to = bestIdx;
            holes[bestIdx].size -= processes[i].size;
        }
    }
}


void displayResults(Process *processes, int np, Hole *holes, int nh) {
    printf("\nProcess Allocation:\n");
    for (int i = 0; i < np; i++) {
        if (processes[i].allocated_to != -1)
            printf("Process %d -> Hole %d\n", i, processes[i].allocated_to);
        else
            printf("Process %d -> Not Allocated\n", i);
    }
    printf("\nHole Availability:\n");
    for (int i = 0; i < nh; i++) {
        printf("Hole %d -> Remaining Size: %d\n", i, holes[i].size);
    }
}

int main() {
    int nh, np;
    

    printf("Enter number of holes: ");
    scanf("%d", &nh);
    Hole *holes = (Hole *)malloc(nh * sizeof(Hole));
    
    printf("Enter sizes of holes: ");
    for (int i = 0; i < nh; i++) {
        scanf("%d", &holes[i].size);
        holes[i].allocated = 0;
    }
    

    printf("Enter number of processes: ");
    scanf("%d", &np);
    Process *processes = (Process *)malloc(np * sizeof(Process));
    
    printf("Enter sizes of processes: ");
    for (int i = 0; i < np; i++) {
        scanf("%d", &processes[i].size);
        processes[i].allocated_to = -1;
    }
    
    printf("\nFirst Fit Allocation\n");
    firstFit(holes, nh, processes, np);
    displayResults(processes, np, holes, nh);
    

    for (int i = 0; i < nh; i++) {
        holes[i].allocated = 0;
    }
    for (int i = 0; i < np; i++) {
        processes[i].allocated_to = -1;
    }
    

    printf("\nBest Fit Allocation\n");
    bestFit(holes, nh, processes, np);
    displayResults(processes, np, holes, nh);
    

    free(holes);
    free(processes);
    
    return 0;
}

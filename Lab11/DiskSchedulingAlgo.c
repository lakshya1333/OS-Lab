#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int abs_diff(int a, int b) {
    return a > b ? a - b : b - a;
}

void sort(int arr[], int n) {
    for(int i=0; i<n-1; i++)
        for(int j=0; j<n-i-1; j++)
            if(arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
}

void SSTF(int rq[], int n, int head) {
    int done[MAX] = {0}, total = 0, count = 0, pos = head;
    printf("\nSSTF Order: ");
    while(count < n) {
        int min = 1e9, index = -1;
        for(int i=0; i<n; i++) {
            if(!done[i] && abs_diff(pos, rq[i]) < min) {
                min = abs_diff(pos, rq[i]);
                index = i;
            }
        }
        total += abs_diff(pos, rq[index]);
        printf("%d ", rq[index]);
        pos = rq[index];
        done[index] = 1;
        count++;
    }
    printf("\nTotal head movement = %d\n", total);
}

void SCAN(int rq[], int n, int head, int size) {
    int total = 0, pos = head;
    int arr[MAX], m = 0;

    for(int i=0; i<n; i++) arr[m++] = rq[i];
    arr[m++] = 0;  // end of disk
    arr[m++] = head;
    sort(arr, m);

    int i;
    for(i=0; i<m; i++) {
        if(arr[i] == head) break;
    }

    printf("\nSCAN Order: ");
    for(int j=i; j>=0; j--) {
        printf("%d ", arr[j]);
        if(j > 0) total += abs_diff(arr[j], arr[j-1]);
    }
    for(int j=i+1; j<m; j++) {
        total += abs_diff(arr[j], arr[j-1]);
        printf("%d ", arr[j]);
    }

    printf("\nTotal head movement = %d\n", total);
}

void CSCAN(int rq[], int n, int head, int size) {
    int total = 0, pos = head;
    int arr[MAX], m = 0;

    for(int i=0; i<n; i++) arr[m++] = rq[i];
    arr[m++] = 0;      // start
    arr[m++] = size;   // end
    arr[m++] = head;
    sort(arr, m);

    int i;
    for(i=0; i<m; i++) {
        if(arr[i] == head) break;
    }

    printf("\nC-SCAN Order: ");
    for(int j=i; j<m-1; j++) {
        printf("%d ", arr[j]);
        total += abs_diff(arr[j], arr[j+1]);
    }

    // jump to beginning (not counted)
    printf("%d ", arr[0]);
    for(int j=0; j<i-1; j++) {
        total += abs_diff(arr[j], arr[j+1]);
        printf("%d ", arr[j+1]);
    }

    printf("\nTotal head movement = %d\n", total);
}

void CLOOK(int rq[], int n, int head) {
    int total = 0, pos = head;
    int arr[MAX], m = 0;

    for(int i=0; i<n; i++) arr[m++] = rq[i];
    arr[m++] = head;
    sort(arr, m);

    int i;
    for(i=0; i<m; i++) {
        if(arr[i] == head) break;
    }

    printf("\nC-LOOK Order: ");
    for(int j=i; j<m-1; j++) {
        printf("%d ", arr[j+1]);
        total += abs_diff(arr[j], arr[j+1]);
    }

    // jump to start (not counted)
    for(int j=0; j<i-1; j++) {
        printf("%d ", arr[j]);
        total += abs_diff(arr[j], arr[j+1]);
    }

    printf("\nTotal head movement = %d\n", total);
}

int main() {
    int rq[MAX], n, head, choice, size;

    int sample[] = {82, 170, 43, 140, 24, 16, 190};
    n = sizeof(sample)/sizeof(sample[0]);
    for(int i=0; i<n; i++) rq[i] = sample[i];
    head = 50;
    size = 199;

    while(1) {
        printf("\n\n*** Disk Scheduling Menu ***\n");
        printf("1. SSTF\n2. SCAN\n3. C-SCAN\n4. C-LOOK\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: SSTF(rq, n, head); break;
            case 2: SCAN(rq, n, head, size); break;
            case 3: CSCAN(rq, n, head, size); break;
            case 4: CLOOK(rq, n, head); break;
            case 5: exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

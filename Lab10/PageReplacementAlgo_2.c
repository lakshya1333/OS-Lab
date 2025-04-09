// LRU

#include <stdio.h>
#include <stdlib.h>

int findLRU(int* time, int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void lru(int* pages, int totalPages, int frameCount) {
    int* frames = (int*)malloc(frameCount * sizeof(int));
    int* time = (int*)malloc(frameCount * sizeof(int));
    int count = 0, pageFaults = 0;

    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < totalPages; i++) {
        int flag = 0;
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == pages[i]) {
                count++;
                time[j] = count;
                flag = 1;
                break;
            }
        }

        if (!flag) {
            int pos = -1;
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1) pos = findLRU(time, frameCount);

            frames[pos] = pages[i];
            count++;
            time[pos] = count;
            pageFaults++;
        }
    }

    printf("LRU Page Faults: %d\n", pageFaults);
    free(frames);
    free(time);
}

int main() {
    int frameCount, totalPages;
    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    printf("Enter number of pages: ");
    scanf("%d", &totalPages);

    int* pages = (int*)malloc(totalPages * sizeof(int));
    printf("Enter page reference string:\n");
    for (int i = 0; i < totalPages; i++) {
        scanf("%d", &pages[i]);
    }

    lru(pages, totalPages, frameCount);

    free(pages);
    return 0;
}



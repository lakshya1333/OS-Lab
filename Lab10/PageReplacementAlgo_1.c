// FIFO and Optimal

#include <stdio.h>
#include <stdlib.h>

int isPageInFrame(int* frames, int frameCount, int page) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == page) return 1;
    }
    return 0;
}

int predict(int* pages, int* frames, int frameCount, int index, int totalPages) {
    int res = -1, farthest = index;
    for (int i = 0; i < frameCount; i++) {
        int j;
        for (j = index; j < totalPages; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == totalPages) return i;
    }
    return (res == -1) ? 0 : res;
}

void fifo(int* pages, int totalPages, int frameCount) {
    int* frames = (int*)malloc(frameCount * sizeof(int));
    int pageFaults = 0, index = 0;

    for (int i = 0; i < frameCount; i++) frames[i] = -1;

    for (int i = 0; i < totalPages; i++) {
        if (!isPageInFrame(frames, frameCount, pages[i])) {
            frames[index] = pages[i];
            index = (index + 1) % frameCount;
            pageFaults++;
        }
    }

    printf("\nFIFO Page Faults: %d\n", pageFaults);
    free(frames);
}

void optimal(int* pages, int totalPages, int frameCount) {
    int* frames = (int*)malloc(frameCount * sizeof(int));
    int pageFaults = 0;

    for (int i = 0; i < frameCount; i++) frames[i] = -1;

    for (int i = 0; i < totalPages; i++) {
        if (!isPageInFrame(frames, frameCount, pages[i])) {
            int j;
            for (j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    frames[j] = pages[i];
                    break;
                }
            }
            if (j == frameCount) {
                int pos = predict(pages, frames, frameCount, i + 1, totalPages);
                frames[pos] = pages[i];
            }
            pageFaults++;
        }
    }

    printf("Optimal Page Faults: %d\n", pageFaults);
    free(frames);
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

    fifo(pages, totalPages, frameCount);
    optimal(pages, totalPages, frameCount);

    free(pages);
    return 0;
}


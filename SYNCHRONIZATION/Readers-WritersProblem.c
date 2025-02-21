#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, write_sem;
int readercount = 0;

void* reader(void* arg) {
    int id = *(int*)arg;

    while (1) {
        sem_wait(&mutex); // Lock access to readercount
        readercount++; // Increment reader count
        if (readercount == 1) {
            sem_wait(&write_sem); // First reader blocks writers
        }
        sem_post(&mutex); // Unlock readercount

        // Reading section
        printf("Reader %d is reading...\n", id);
        sleep(1); // Simulate reading time

        sem_wait(&mutex); // Lock access to readercount
        readercount--; // Decrement reader count
        if (readercount == 0) {
            sem_post(&write_sem); // Last reader allows writers
        }
        sem_post(&mutex); // Unlock readercount

        sleep(1); // Simulate time before reading again
    }
}

void* writer(void* arg) {
    int id = *(int*)arg; // Writer ID

    while (1) {
        sem_wait(&write_sem); // Ensure exclusive access to resource

        // Writing section
        printf("Writer %d is writing...\n", id);
        sleep(2); // Simulate writing time

        sem_post(&write_sem); // Allow other readers/writers

        sleep(2); // Simulate time before writing again
    }
}

int main() {
    pthread_t readers[3], writers[2]; 
    int r_ids[3] = {1, 2, 3}, w_ids[2] = {1, 2};

    
    sem_init(&mutex, 0, 1); 
    sem_init(&write_sem, 0, 1);

    
    for (int i = 0; i < 3; i++) {
        pthread_create(&readers[i], NULL, reader, &r_ids[i]);
    }

  
    for (int i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, &w_ids[i]);
    }

    
    for (int i = 0; i < 3; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&write_sem);

    return 0;
}

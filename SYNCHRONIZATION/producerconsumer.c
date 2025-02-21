#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CAPACITY 5  // Buffer size

int buffer[CAPACITY]; 
int in = 0, out = 0; 

sem_t empty, full; 
pthread_mutex_t mutex; 

// Producer function
void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100; 
        sem_wait(&empty);     // Wait if buffer is full
        pthread_mutex_lock(&mutex); // Lock critical section

        buffer[in] = item; 
        printf("Producer produced: %d\n", item);
        in = (in + 1) % CAPACITY;

        pthread_mutex_unlock(&mutex); // Unlock critical section
        sem_post(&full); // Signal that buffer has a new item

        sleep(1);
    }
}

// Consumer function
void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full);  // Wait if buffer is empty
        pthread_mutex_lock(&mutex); // Lock critical section

        item = buffer[out]; 
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % CAPACITY;

        pthread_mutex_unlock(&mutex); // Unlock critical section
        sem_post(&empty); // Signal that buffer has a free space

        sleep(2); 
    }
}

int main() {
    pthread_t prodThread, consThread;

    sem_init(&empty, 0, CAPACITY);  
    sem_init(&full, 0, 0);         
    pthread_mutex_init(&mutex, NULL);

   
    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);

 
    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);

    
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Buffer capacity
#define MAX_ITEMS 10   // Number of items to produce/consume

int buffer[BUFFER_SIZE]; 
int in = 0, out = 0; 


sem_t empty; 
sem_t full; 
pthread_mutex_t mutex; 

// Producer function
void* producer(void* arg) {
    for (int i = 0; i < MAX_ITEMS; i++) {
        int item = rand() % 100;  

        sem_wait(&empty);  
        pthread_mutex_lock(&mutex); 

        
        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;  

        pthread_mutex_unlock(&mutex);  
        sem_post(&full); 

        sleep(1);
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    for (int i = 0; i < MAX_ITEMS; i++) {
        sem_wait(&full);  
        pthread_mutex_lock(&mutex); 

      
        int item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;  

        pthread_mutex_unlock(&mutex);   
        sem_post(&empty);  

        sleep(1); 
    }
    return NULL;
}

int main() {
    pthread_t prodThread, consThread
  
    sem_init(&empty, 0, BUFFER_SIZE);
    pthread_mutex_init(&mutex, NULL);  
    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);

    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);

    // Destroy semaphores and mut
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

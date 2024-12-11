#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 1 

int buffer = 0;  
sem_t empty, full;  
pthread_mutex_t mutex;

void* producer(void* arg) {
    int item = 1;
    sem_wait(&empty);  
    pthread_mutex_lock(&mutex); 

    buffer = item; 
    printf("Produced: %d\n", item);

    pthread_mutex_unlock(&mutex);  
    sem_post(&full); 
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    int item;
    sem_wait(&full);  // Wait for full slot
    pthread_mutex_lock(&mutex);  // Lock the buffer

    item = buffer;  // Consume item
    printf("Consumed: %d\n", item);

    pthread_mutex_unlock(&mutex);  
    sem_post(&empty);  // Signal empty slot
    return NULL;
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, BUFFER_SIZE);  
    sem_init(&full, 0, 0); 
    pthread_mutex_init(&mutex, NULL); 

   
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}


/*
INPUT and OUTPUT:

pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ ./lab7_Q4_producerconsumer
Produced: 1
Consumed: 1

*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Shared resource
int shared_memory = 0;

// Semaphores
sem_t rw_mutex;  // Binary semaphore for shared memory access

// Writer function
void* writer(void* arg) {
    int writer_id = *((int*)arg);

    while (1) {
        sleep(rand() % 3 + 1); // Simulate some delay
        printf("Writer %d is trying to write...\n", writer_id);

        sem_wait(&rw_mutex);  // Lock the shared resource
        shared_memory++;
        printf("Writer %d wrote value: %d\n", writer_id, shared_memory);
        sem_post(&rw_mutex);  // Unlock the shared resource

        sleep(rand() % 3 + 1); // Simulate delay after writing
    }

    return NULL;
}

// Reader function
void* reader(void* arg) {
    int reader_id = *((int*)arg);

    while (1) {
        sleep(rand() % 3 + 1); // Simulate some delay
        printf("Reader %d is trying to read...\n", reader_id);

        sem_wait(&rw_mutex);  // Lock the shared resource
        printf("Reader %d read value: %d\n", reader_id, shared_memory);
        sem_post(&rw_mutex);  // Unlock the shared resource

        sleep(rand() % 3 + 1); // Simulate delay after reading
    }

    return NULL;
}

int main() {
    pthread_t readers[3], writers[2]; // Threads for readers and writers
    int reader_ids[3] = {1, 2, 3};
    int writer_ids[2] = {1, 2};

    // Initialize semaphore
    sem_init(&rw_mutex, 0, 1);  // Binary semaphore for shared resource

    // Create reader threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Let threads run for some time
    sleep(20);

    // Cancel all threads and clean up
    for (int i = 0; i < 3; i++) {
        pthread_cancel(readers[i]);
    }
    for (int i = 0; i < 2; i++) {
        pthread_cancel(writers[i]);
    }

    // Destroy semaphore
    sem_destroy(&rw_mutex);

    printf("Simplified Reader-Writer simulation ended.\n");

    return 0;
}



/*
OUTPUT:

pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ ./lab7_Q5_readerwriter
Reader 3 is trying to read...
Reader 3 read value: 0
Reader 2 is trying to read...
Reader 2 read value: 0
Writer 1 is trying to write...
Writer 1 wrote value: 1
Reader 1 is trying to read...
Reader 1 read value: 1
Writer 2 is trying to write...
Writer 2 wrote value: 2
Reader 1 is trying to read...
Reader 1 read value: 2
Reader 3 is trying to read...
Reader 3 read value: 2
Reader 2 is trying to read...
Reader 2 read value: 2
Writer 1 is trying to write...
Writer 1 wrote value: 3
Writer 2 is trying to write...
Writer 2 wrote value: 4
Reader 2 is trying to read...
Reader 2 read value: 4
Reader 1 is trying to read...
Reader 1 read value: 4
Writer 1 is trying to write...
Writer 1 wrote value: 5
Reader 3 is trying to read...
Reader 3 read value: 5
Writer 2 is trying to write...
Writer 2 wrote value: 6
Reader 3 is trying to read...
Reader 3 read value: 6
Writer 1 is trying to write...
Writer 1 wrote value: 7
Reader 2 is trying to read...
Reader 2 read value: 7
Reader 1 is trying to read...
Reader 1 read value: 7
Writer 2 is trying to write...
Writer 2 wrote value: 8
Reader 3 is trying to read...
Reader 3 read value: 8
Writer 1 is trying to write...
Writer 1 wrote value: 9
Reader 2 is trying to read...
Reader 2 read value: 9
Simplified Reader-Writer simulation ended.
*/
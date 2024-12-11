#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX 10000

int cnt = 0; // Global shared variable

void *Incr(void *p) {
    int temp, i;
    // Each thread increments cnt MAX times
    for (i = 0; i < MAX; i++) {
        temp = cnt;  // Read cnt
        temp = temp + 1;  // Increment temp
        cnt = temp;  // Write back to cnt
    }
    return NULL;
}

int main() {
    pthread_t th1, th2;

    // Create two threads that run the Incr function
    pthread_create(&th1, NULL, Incr, NULL);
    pthread_create(&th2, NULL, Incr, NULL);

    // Wait for both threads to finish
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    // Check if the final value of cnt is what we expect
    if (cnt < 2 * MAX) {
        printf("Count is %d but it should have been %d\n", cnt, 2 * MAX);
    } else {
        printf("Count is %d\n", cnt);
    }
    return 0;
}

/*
O/P Predicted:
pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ ./lab5_Q4_oppredict
Count is 13501 but it should have been 20000

Reason: The value of cnt is often less than 20000 when the program runs. 
This happens due to race conditions during concurrent execution of the 
threads due to Lack of Synchronization.
*/
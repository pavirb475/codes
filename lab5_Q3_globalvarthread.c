#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int gdata = 100; // Global variable

void *tfun(void *arg) { // Function executed by each thread
    int ldata = 10; // Local variable

    // Print thread ID
    printf("Hello. I am the child thread with ID: %lu\n", pthread_self());

    printf("First gdata value %d\n", gdata);
    gdata += 5;
    printf("gdata after modification = %d\n", gdata);

    // Access and modify local variable
    printf("ldata before modification = %d\n", ldata);
    ldata += 5;
    printf("ldata after modification = %d\n", ldata);

    return NULL;
}
int main() { // Main thread
    pthread_t tid1, tid2;

    // Create first child thread
    pthread_create(&tid1, NULL, tfun, NULL);
    
    // Create second child thread
    pthread_create(&tid2, NULL, tfun, NULL);

    fprintf(stdout, "Main thread continues...\n");
    // Wait for both threads to finish
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Print final value of global variable in main thread
    printf("Final value of gdata in main thread = %d\n", gdata);
    printf("Main thread joins the child threads\n");

    return 0;
}

/*
INPUT and OUTPUT:

pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ ./lab5_Q3_globalvarthread
Hello. I am the child thread with ID: 140052588893888
First gdata value 100
gdata after modification = 105
ldata before modification = 10
ldata after modification = 15
Hello. I am the child thread with ID: 140052580501184
First gdata value 105
gdata after modification = 110
ldata before modification = 10
ldata after modification = 15
Main thread continues...
Final value of gdata in main thread = 110
Main thread joins the child threads
*/
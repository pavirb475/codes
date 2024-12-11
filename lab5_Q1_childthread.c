#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *tfun(void *arg) {   //child thread
    printf("Hello from  thread!\n");
    return NULL;
}

int main() {  //main thread  //every proces has a main process
    pthread_t tid; 

    int newt = pthread_create(&tid, NULL, tfun, NULL);   //thread id has threads identification
    if (newt != 0) { 
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    fprintf(stdout, "Main thread continues...\n");

    pthread_join(tid, NULL);  //here main thread waits until child thread executes
                              //it waits until child finishes tfunc
    printf("Main thread joins the child thread\n");
    return 0;
}

/*
INPUT and OUTPUT:

pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ ./lab5_Q1_childthread
Main thread continues...
Hello from  thread!
Main thread joins the child thread
*/
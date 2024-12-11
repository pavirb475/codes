#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int gvar=200;


void *tfun(void *arg) {   
    printf("Hello. I am the child thread!\n");
    printf("Thread id= %lu\n",pthread_self());
    printf("gvar=%d\n",gvar);
    gvar=20;
    return NULL;
}

int main() {  //main thread  
    pthread_t tid, tid2; 

    int newt = pthread_create(&tid, NULL, tfun, NULL);   //thread id has threads identification

    int newt2 = pthread_create(&tid2, NULL, tfun, NULL);   

    fprintf(stdout, "Main thread continues...\n");

    pthread_join(tid, NULL);  //here main thread waits until child thread executes

    pthread_join(tid2, NULL);                          
    printf("Main thread joins the child thread\n");
    return 0;
}

/*
INPUT and OUTPUT:

pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ ./lab5_Q2_multiplethreads
Main thread continues...
Hello. I am the child thread!
Thread id= 140424788571840
gvar=200
Hello. I am the child thread!
Thread id= 140424796964544
gvar=20
Main thread joins the child thread
*/
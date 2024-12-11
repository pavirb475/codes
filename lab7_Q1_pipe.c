#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int status, status2, pipefds1[2], pipefds2[2];
    pid_t pid;
    char writebuf[20], readbuf[20];

    // Create the pipes
    status = pipe(pipefds1);
    status2 = pipe(pipefds2);
    if (status == -1 || status2 == -1) {
        perror("Error in creating pipes");
        exit(1); // Exit with error
    }

    // Create child process
    pid = fork();
    if (pid == -1) {
        perror("Cannot create child process");
        exit(2);

    } else if (pid == 0) { 
        // P1 >> Child process
        close(pipefds1[0]); 
        close(pipefds2[1]); 

        // P1 Sending "Name" to P2
        printf("P1: SENDING NAME\n");
        write(pipefds1[1], "Name", 5);

        // Reading reply of P2 and printing
        read(pipefds2[0], readbuf, 8); 
        readbuf[8] = '\0';           
        printf("P1: REPLY READ AND PRINTED: %s\n", readbuf);

        close(pipefds1[1]); 
        close(pipefds2[0]); 
        exit(0);

    } else { 
        // P2 >> Parent process
        close(pipefds1[1]); 
        close(pipefds2[0]); 

        // Reading message from P1
        read(pipefds1[0], readbuf, 5); 
        readbuf[5] = '\0';            
        printf("P2: READ AND REPLIED\n");

        // Replying to P1
        write(pipefds2[1], "Pavithra", 8); 
        close(pipefds1[0]); 
        close(pipefds2[1]); 
        exit(0);
    }
}

/*
INPUT and OUTPUT:

pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ ./lab7_Q1_pipe
P1: SENDING NAME
P2: READ AND REPLIED
P1: REPLY READ AND PRINTED: Pavithra
*/
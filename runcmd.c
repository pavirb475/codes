#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {  // Check if the number of arguments is correct
        printf("Incorrect number of arguments\n");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {  
        perror("Fork failed");
        exit(1);
    }
    if (pid == 0) {  
        execlp(argv[1], argv[1], argv[2],NULL);
        perror("Exec failed");
        exit(1);
        
    } 
    else {  
        int status;
        wait(&status); 
        if (WIFEXITED(status)) {
            printf("Command successfully completed\n");
        } else {
            printf("Command failed\n");
        }
    }
    return 0;
}

/* 
INPUT and OUTPUT:

pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ gcc runcmd.c -o runcmd
pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ ./runcmd echo Hello
Hello
Command successfully completed
pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ ./runcmd ls -l
total 648

*/
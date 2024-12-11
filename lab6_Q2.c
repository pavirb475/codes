#include <signal.h> 
#include <stdio.h>  
#include <stdlib.h> 
#include <sys/types.h>
#include <unistd.h>
void termination_handler(const int signal){
    switch (signal){
    case SIGINT:
        printf("\nSIGINT (%i) (Ctrl + C) signal caught.\n", signal);
        break;
    case SIGTERM:
        printf("\nSIGTERM (%i) (default `kill` or `killall`) signal caught.\n", 
            signal);
        break;
    default:
        printf("\nUnk signal (%i) caught.\n", signal);
        break;
    }
    exit(signal);
}
int main(int argc, char *argv[])
{
    struct sigaction new_action;
    new_action.sa_handler = termination_handler; 
    sigemptyset(&new_action.sa_mask); 
    new_action.sa_flags = 0;  


    sigaction(SIGINT, &new_action,NULL);
    sigaction(SIGTERM, &new_action,NULL);
    printf("%d\n",getpid());
    while(1){
    }
}

/*
INPUT and OUTPUT:

pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ ./lab6_Q2
1879
^C
SIGINT (2) (Ctrl + C) signal caught.
*/
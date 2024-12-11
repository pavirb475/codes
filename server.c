#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>//
#include <stdlib.h> //atoi,exit,EXIT_FAILURE
int main(int argc, char *argv[])
{
    char op;
    int n1,n2,res;
    if(argc!=4){
        printf("error, provide args +/- num1 num 2\n");
        return EXIT_FAILURE;
    }
    else{
        op=argv[1][0]; //since argv[1] is a string tha contains operator, argv[1][0] is first char
        n1=atoi(argv[2]);
        n2=atoi(argv[3]);
        
        switch(op){
        case  '+': res=n1+n2;break;
        case  '-':res=n1-n2;break;
            default:
                printf("error in operand\n");
                return EXIT_FAILURE;
        }
        exit(res);

    }
}

/*
INPUT and OUTPUT:

pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ gcc client.c -o client
pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ gcc server.c -o server
pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ ./client
Enter an operator and two operands+
2
5
child 1369 exited normally
7
*/
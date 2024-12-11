#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> //WIFEXITED defined here
int main()
{
pid_t pid; //pid_t is a signed integer
int status;
int n1,n2;
char c;
printf("Enter an operator and two operands");
scanf(" %c%d%d",&c,&n1,&n2);
pid = fork();
if (pid < 0) { /* error occurred */
fprintf(stderr, "Fork Failed");
return 1;
}
if(pid==0){
    char oper[2]={0};
    char op1[3]={0};
    char op2[3]={0};

    sprintf(oper,"%c",c);
    sprintf(op1,"%d",n1);
    sprintf(op2,"%d",n2);
    execl("./pserver", "pserver", oper, op1, op2, NULL);
   //printf("child pid=%d\n",getpid());
   //execl("./serv.o","serv.o",oper,op1,NULL);
}
else{
    int w=wait(&status);
  
    if(WIFEXITED(status)){ 
             
        printf("child %d exited normally\n",w);

        int res=WEXITSTATUS(status);
        printf("%d\n",res);
    }

}

return 0;
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
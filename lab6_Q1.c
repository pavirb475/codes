#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    int *a,*b,shmid,status;
    int i;
    shmid = shmget(IPC_PRIVATE,2*sizeof(int),0777|IPC_CREAT);
    if(fork()==0){
        printf("in child pid=%d\n",getpid());
        b=(int*)shmat(shmid,0,0);
        for(i=0;i<5;i++){
            sleep(2);printf("child reads %d %d\n",b[0],b[1]);
        }
        shmdt(b);  
    }
    else{
        printf("parent pid=%d\n",getpid());
        a=(int*)shmat(shmid,0,0);
        a[0]=0;
        a[1]=1;
        for(i=0;i<5;i++){
            sleep(1);
            a[0]=a[0]+a[1];
            a[1]=a[0]+a[1];
            printf("parent writes %d %d\n",a[0],a[1]);
        }
        wait(&status);
         shmdt(a);
    }
   shmctl(shmid,IPC_RMID,0);  //IPC_RMID: Removes the shared memory segment, effectively marking it for deletion.
    return 0;
}

/*
INPUT and OUTPUT:

pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ ./lab6_Q1
parent pid=1867
in child pid=1868
parent writes 1 2
parent writes 3 5
child reads 3 5
parent writes 8 13
parent writes 21 34
child reads 21 34
parent writes 55 89
child reads 55 89
child reads 55 89
child reads 55 89

*/
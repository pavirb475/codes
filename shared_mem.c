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
    //returns  the identifier of the System V shared memory segment associated with the key(first arg).
    //here key=IPC_PRIVATE - new shared memory segment is created
    shmid = shmget(IPC_PRIVATE,2*sizeof(int),0777|IPC_CREAT);
    if(fork()==0){
        printf("in child pid=%d\n",getpid());
        //shmat()  attaches  the  System V shared memory segment identified by shmid to the address space of the calling process.
        //2nd arg is 0, the segment is attached to the first available address as selected by the system
        //shmat() returns the address of the attached shared memory segment
        b=(int*)shmat(shmid,0,0);
        for(i=0;i<5;i++){
            sleep(2);printf("child reads %d %d\n",b[0],b[1]);
        }
        shmdt(b);  // detaches the shared memory segment 
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
    // remove shared memory
   shmctl(shmid,IPC_RMID,0);
    return 0;
}
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
 int main(int argc, char *argv[]){
 char buf[20];
 if(argc!=2){
 write(1,"error\n",6);
 exit(0);
 }
 int fd=open(argv[1],O_CREAT|O_RDWR);
 read(0,buf,20);
 write(fd,buf,strlen(buf));
 close(fd);
 return 0;
 } 

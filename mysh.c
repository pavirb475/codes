#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main() {
    char buf[256];  
    pid_t pid;                

    while (1) {
        printf(">>> ");
        fflush(stdout);  

        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            printf("\nExiting shell.\n");
            break;  // Exit on EOF (Ctrl+D)
        }

        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        }

        if (strlen(buf) == 0) {
            continue;
        }

        pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        }

        if (pid == 0) {
            execlp(buf, buf, NULL);  
            perror("Exec failed");  
            exit(1);
        } else {
            waitpid(pid, NULL, 0);
        }
    }

    return 0;
}

/*
pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ gcc mysh.c -o mysh
pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ ./mysh
>>> ./helloworld
Hello, World!
>>> ./byeworld
Goodbye, World!
>>>*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipefd[2]; // File descriptors for the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { 
        // Child process: Executes `ls`
        close(pipefd[0]);              // Close unused read end of the pipe
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the pipe's write end
        close(pipefd[1]);              // Close the original write end

        execlp("ls", "ls", NULL);       // Execute `ls`
        perror("execlp");               // If execlp fails
        exit(EXIT_FAILURE);
    } else { 
        // Parent process: Executes `wc -l`
        close(pipefd[1]);              // Close unused write end of the pipe
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to the pipe's read end
        close(pipefd[0]);              // Close the original read end

        execlp("wc", "wc", "-l", NULL); // Execute `wc -l`
        perror("execlp");               // If execlp fails
        exit(EXIT_FAILURE);
    }

    return 0;
}
/*
INPUT and OUTPUT:

pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ ./lab7_Q2
92
pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ ls | wc -l
92

*/
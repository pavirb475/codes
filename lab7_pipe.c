#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int status, pid, pipefds[2];
    char buf[20];

    // Create the pipe
    status = pipe(pipefds);
    if (status == -1) {
        perror("Error in creating pipe");
        exit(1); //exit with error
    }

    // Create child process
    pid = fork();
    if (pid == -1) {
        perror("Cannot create child process");
        exit(2);
    } else if (pid == 0) { 
        // Child process: sends message to parent
        close(pipefds[0]); // Close unused read end
        printf("Sending message by %d, pipefds=%d\n", getpid(), pipefds[1]);//getpid() returns the Process ID (PID) of the current process. //pipefds[1] represents an integer value that the operating system assigns to identify this specific pipe's write endpoint.
        write(pipefds[1], "Hello", 5); // Write message to pipe  //5 specifies the number of bytes to write from the string into the pipe.
        close(pipefds[1]); // Close write end
        exit(0);
    } else { 
        // Parent process: receives message from child
        close(pipefds[1]); // Close unused write end
        read(pipefds[0], buf, 5); // Read message from pipe //read raw data (bytes) from a file descriptor into a buffer
        buf[5] = '\0'; // Null-terminate the string
        printf("%d read message: %s\n", getpid(), buf);
        close(pipefds[0]); // Close read end
        exit(0);
    }
}
//After the call, buf contains: buf = {'H', 'e', 'l', 'l', 'o'}
//Adding buf[5] = '\0'; makes it: buf = "Hello" // A null-terminated string
//the string in buf is not nulcd l-terminated, since pipes only transfer raw bytes, not C-style strings
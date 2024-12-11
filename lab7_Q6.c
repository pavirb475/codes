#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

int found_index = -1;

void signal_handler(int signo) {
   
}

void search(int *array, int size, int num, int offset) {
    for (int i = 0; i < size; i++) {
        if (array[i] == num) {
            kill(getppid(), SIGUSR1);
            exit(offset + i);
        }
    }
    exit(-1);
}

int main(int argc, char *argv[]) {
    if (argc != 3) return 1;

    int array[100], n = 0, num = atoi(argv[2]);
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) return 1;

    while (read(fd, &array[n], sizeof(int)) > 0) n++;
    close(fd);

    if (n < 5) {
        for (int i = 0; i < n; i++) {
            if (array[i] == num) {
                printf("Found at index %d\n", i);
                return 0;
            }
        }
        printf("Not found\n");
        return 0;
    }

    signal(SIGUSR1, signal_handler);

    int mid = n / 2;
    pid_t pid1 = fork();
    if (pid1 == 0) search(array, mid, num, 0);

    pid_t pid2 = fork();
    if (pid2 == 0) search(array + mid, n - mid, num, mid);

    int status;
    while (wait(&status) > 0) {
        if (WIFEXITED(status) && WEXITSTATUS(status) >= 0) {
            found_index = WEXITSTATUS(status);
            kill(pid1, SIGKILL);
            kill(pid2, SIGKILL);
            break;
        }
    }

    if (found_index != -1) printf("Found at index %d\n", found_index);
    else printf("Not found\n");

    return 0;
}

/*
INPUT and OUTPUT:

pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ ./lab7_Q6 numbers.bin 3
Found at index 2
*/
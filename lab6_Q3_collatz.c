#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define SHARED_MEMORY_SIZE 4096
int string_to_int(const char *str) {
    int result = 0;
    while (*str) {
        if (!isdigit(*str)) {
            fprintf(stderr, "Error: Input must be a positive integer.\n");
            exit(EXIT_FAILURE);
        }
        result = result * 10 + (*str - '0');
        str++;
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive-integer>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = string_to_int(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "Error: Please provide a positive integer.\n");
        exit(EXIT_FAILURE);
    }

    void *shared_memory = mmap(NULL, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE,
                               MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_memory == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { 
        char buffer[SHARED_MEMORY_SIZE] = {0};
        char temp[32];

        while (n != 1) {
            sprintf(temp, "%d, ", n);
            strcat(buffer, temp);
            n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        }
        sprintf(temp, "1");
        strcat(buffer, temp);

        strcpy((char *)shared_memory, buffer);

        exit(EXIT_SUCCESS);

    } else { 
        wait(NULL);

        printf("Collatz sequence: %s\n", (char *)shared_memory);

        if (munmap(shared_memory, SHARED_MEMORY_SIZE) == -1) {
            perror("munmap");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

/*
INPUT and OUTPUT:

pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ ./lab6_Q3_collatz 8
Collatz sequence: 8, 4, 2, 1
*/

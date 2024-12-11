
#include <stdio.h>

int main() {
    FILE *file = fopen("numbers.bin", "wb"); // Open file in binary write mode
    if (file == NULL) {
        perror("Error creating file");
        return 1;
    }

    int numbers[] = {1, 2, 3, 4, 5, 6}; // Array of integers to write
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    fwrite(numbers, sizeof(int), count, file); // Write integers to the file
    fclose(file);

    printf("numbers.bin created successfully!\n");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Global arrays and size
#define SIZE 10
int unsorted_array[SIZE] = {4,9,8,1,5,6,7,3,2,0};
int sorted_array[SIZE]; // Array to store the final sorted result

// Function to perform bubble sort
void bubble_sort(int arr[], int start, int end) {
    for (int i = start; i < end - 1; i++) {
        for (int j = start; j < end - (i - start) - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Thread function for sorting
void *sorting_thread(void *arg) {
    int *indexes = (int *)arg;
    int start = indexes[0];
    int end = indexes[1];
    bubble_sort(unsorted_array, start, end);
    pthread_exit(0);
}

// Function to merge two sorted sublists
void merge(int arr1[], int start1, int end1, int arr2[], int start2, int end2, int result[]) {
    int i = start1, j = start2, k = 0;

    // Merge the two lists
    while (i < end1 && j < end2) {
        if (arr1[i] < arr2[j]) {
            result[k++] = arr1[i++];
        } else {
            result[k++] = arr2[j++];
        }
    }

    // Copy remaining elements of the first sublist
    while (i < end1) {
        result[k++] = arr1[i++];
    }

    // Copy remaining elements of the second sublist
    while (j < end2) {
        result[k++] = arr2[j++];
    }
}

// Thread function for merging
void *merging_thread(void *arg) {
    merge(unsorted_array, 0, SIZE / 2, unsorted_array, SIZE / 2, SIZE, sorted_array);
    pthread_exit(0);
}

// Main function
int main() {
    pthread_t sort_tid1, sort_tid2, merge_tid;

    // Define the start and end indices for sorting threads
    int indexes1[] = {0, SIZE / 2};
    int indexes2[] = {SIZE / 2, SIZE};

    printf("Unsorted Array: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", unsorted_array[i]);
    }
    printf("\n");

    // Create two sorting threads
    pthread_create(&sort_tid1, NULL, sorting_thread, (void *)indexes1);
    pthread_create(&sort_tid2, NULL, sorting_thread, (void *)indexes2);

    // Wait for the sorting threads to finish
    pthread_join(sort_tid1, NULL);
    pthread_join(sort_tid2, NULL);

    printf("Partially Sorted Array: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", unsorted_array[i]);
    }
    printf("\n");

    // Create merging thread
    pthread_create(&merge_tid, NULL, merging_thread, NULL);

    // Wait for the merging thread to finish
    pthread_join(merge_tid, NULL);

    // Output the final sorted array
    printf("Sorted Array: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", sorted_array[i]);
    }
    printf("\n");

    return 0;
}

/*
INPUT and OUTPUT:

pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ ./lab5_Q5_sortingthreads
Unsorted Array: 4 9 8 1 5 6 7 3 2 0
Partially Sorted Array: 1 4 5 8 9 0 2 3 6 7
Sorted Array: 0 1 2 3 4 5 6 7 8 9
*/
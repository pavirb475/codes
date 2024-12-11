#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Shared variables
int account_balance = 1000;
int flag[2] = {0, 0}; // Flags for Peterson's solution
int turn = 0;

// Deposit function
void* deposit(void* arg) {
    for (int i = 0; i < 5; i++) {
        // Enter critical section (Peterson's solution)
        flag[0] = 1;
        turn = 1;
        while (flag[1] && turn == 1);

        // Critical section: deposit
        int temp = account_balance;
        printf("Depositing 500...\n");
        temp += 500;
        usleep(100000); // Simulate processing time
        account_balance = temp;
        printf("New balance after deposit: %d\n", account_balance);

        // Exit critical section
        flag[0] = 0;

        usleep(50000); // Simulate delay
    }
    return NULL;
}

// Withdraw function
void* withdraw(void* arg) {
    for (int i = 0; i < 5; i++) {
        // Enter critical section (Peterson's solution)
        flag[1] = 1;
        turn = 0;
        while (flag[0] && turn == 0);

        // Critical section: withdraw
        if (account_balance >= 300) {
            int temp = account_balance;
            printf("Withdrawing 300...\n");
            temp -= 300;
            usleep(100000); // Simulate processing time
            account_balance = temp;
            printf("New balance after withdrawal: %d\n", account_balance);
        } else {
            printf("Insufficient funds for withdrawal.\n");
        }

        // Exit critical section
        flag[1] = 0;

        usleep(50000); 
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Create threads for deposit and withdraw
    pthread_create(&t1, NULL, deposit, NULL);
    pthread_create(&t2, NULL, withdraw, NULL);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Final account balance
    printf("Final account balance: %d\n", account_balance);
    return 0;
}


/*
INPUT and OUTPUT:

pavithrarb@DESKTOP-PAVSS:~/OSCPRGMS$ ./lab7_Q3
Depositing 500...
New balance after deposit: 1500
Withdrawing 300...
New balance after withdrawal: 1200
Depositing 500...
New balance after deposit: 1700
Withdrawing 300...
New balance after withdrawal: 1400
Depositing 500...
New balance after deposit: 1900
Withdrawing 300...
New balance after withdrawal: 1600
Depositing 500...
New balance after deposit: 2100
Withdrawing 300...
New balance after withdrawal: 1800
Depositing 500...
New balance after deposit: 2300
Withdrawing 300...
New balance after withdrawal: 2000
Final account balance: 2000
*/
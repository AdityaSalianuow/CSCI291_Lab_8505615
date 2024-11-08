#include <stdio.h>

#define INITIAL_BALANCE 1000
#define MAX_TRANSACTIONS 10

int main()
{
    int balance = INITIAL_BALANCE;
    int transactions[MAX_TRANSACTIONS] = {200, -150, -500, -400, -50, -200, 300};
    int tobeprocessed[MAX_TRANSACTIONS];
    int tobeprocessed_count = 0;

    printf("Starting balance: %d AED\n", balance);

    for (int i = 0; i < MAX_TRANSACTIONS; i++) {
        if (transactions[i] == 0) break;

        int transaction = transactions[i];

        if (transaction < 0 && balance + transaction < 0) {
            printf("Skipped withdrawal of %d AED: Insufficient funds.\n", -transaction);
            tobeprocessed[tobeprocessed_count++] = transaction;
        } else {
            balance += transaction;
            printf("Processed transaction: %d AED, New balance: %d AED\n", transaction, balance);

            if (balance == 0) {
                printf("Balance reached zero. Stopping further transactions.\n");
                for (int j = i + 1; j < MAX_TRANSACTIONS; j++) {
                    if (transactions[j] == 0) break;
                    tobeprocessed[tobeprocessed_count++] = transactions[j];
                }
                break;
            }
        }
    }

    printf("\nFinal balance: %d AED\n", balance);
    printf("Transactions to be processed later:\n");
    for (int i = 0; i < tobeprocessed_count; i++) {
        printf("%d ", tobeprocessed[i]);
    }
    printf("\n");

    return 0;
}

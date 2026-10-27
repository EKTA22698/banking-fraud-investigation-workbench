#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "dataset.h"
#include "transaction.h"
#include "fraud.h"

int main(void)
{
    Transaction *transactions = malloc(
        MAX_TRANSACTIONS * sizeof(Transaction)
    );

    if (transactions == NULL)
    {
        printf("ERROR: Unable to allocate memory for transactions.\n");
        return 1;
    }

    int transaction_count = 0;
    int choice;

    do
    {
        display_main_menu();

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input. Please enter a number.\n");

            while (getchar() != '\n')
            {
                /* Clear invalid input */
            }

            continue;
        }

        printf("\n");

        switch (choice)
        {
            case 1:
                transaction_count = load_transactions_csv(
                    "data/small/transactions_small.csv",
                    transactions,
                    MAX_TRANSACTIONS
                );

                if (transaction_count >= 0)
                {
                    printf("\nDataset loaded successfully.\n");

                    print_dataset_summary(
                        transactions,
                        transaction_count
                    );
                }

                break;

            case 2:
                print_all_transactions(
                    transactions,
                    transaction_count
                );
                break;

            case 3:
    analyze_fraud(
        transactions,
        transaction_count
    );
    break;
            case 4:
                printf("Transaction Search and Sort - Coming Soon\n");
                break;

            case 5:
                printf("Pattern Search - Coming Soon\n");
                break;

            case 6:
                printf("Fraud Network Analysis - Coming Soon\n");
                break;

            case 7:
                printf("Investigation Planning - Coming Soon\n");
                break;

            case 8:
                printf("Algorithm Laboratory - Coming Soon\n");
                break;

            case 9:
                printf("Benchmark Runner - Coming Soon\n");
                break;

            case 10:
                printf("Test Suite - Coming Soon\n");
                break;

            case 11:
                printf("Export Results - Coming Soon\n");
                break;

            case 0:
                printf("Exiting Fraud Investigation Workbench...\n");
                break;

            default:
                printf("Invalid choice. Please select 0 to 11.\n");
        }

    } while (choice != 0);

    free(transactions);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "dataset.h"
#include "transaction.h"
#include "fraud.h"
#include "sorting.h"
#include "searching.h"
#include "divide_conquer.h"

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
{
    int operation_choice;

    if (transaction_count <= 0)
    {
        printf("No dataset is currently loaded.\n");
        printf("Please load a dataset first.\n");
        break;
    }

    printf("\n============================================\n");
    printf("       TRANSACTION SEARCH AND SORT\n");
    printf("============================================\n");
    printf("1. Merge Sort by Amount\n");
    printf("2. Quick Sort by Amount\n");
    printf("3. Iterative Binary Search by Transaction ID\n");
    printf("4. Recursive Binary Search by Transaction ID\n");
    printf("0. Back\n");
    printf("============================================\n");
    printf("Select operation: ");

    if (scanf("%d", &operation_choice) != 1)
    {
        printf("Invalid input.\n");

        while (getchar() != '\n')
        {
        }

        break;
    }

    if (operation_choice == 1)
    {
        merge_sort_transactions(
            transactions,
            transaction_count
        );

        printf("\nTransactions sorted using Merge Sort.\n");

        print_all_transactions(
            transactions,
            transaction_count
        );
    }
    else if (operation_choice == 2)
    {
        quick_sort_transactions(
            transactions,
            transaction_count
        );

        printf("\nTransactions sorted using Quick Sort.\n");

        print_all_transactions(
            transactions,
            transaction_count
        );
    }
    else if (
        operation_choice == 3 ||
        operation_choice == 4
    )
    {
        char search_id[ID_LENGTH];
        int result;

        printf("Enter Transaction ID: ");
        scanf("%19s", search_id);

        /*
         * Binary search requires sorted input.
         */
        sort_transactions_by_id(
            transactions,
            transaction_count
        );

        if (operation_choice == 3)
        {
            result = binary_search_iterative(
                transactions,
                transaction_count,
                search_id
            );

            printf("\nAlgorithm: Iterative Binary Search\n");
        }
        else
        {
            result = binary_search_recursive(
                transactions,
                transaction_count,
                search_id
            );

            printf("\nAlgorithm: Recursive Binary Search\n");
        }

        if (result >= 0)
        {
            printf("Transaction found at index %d.\n", result);

            print_transaction(
                &transactions[result]
            );
        }
        else
        {
            printf("Transaction '%s' was not found.\n", search_id);
        }
    }
    else if (operation_choice != 0)
    {
        printf("Invalid operation.\n");
    }

    break;
}     
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
{
    int algorithm_choice;

    printf("\n============================================\n");
    printf("          DAA ALGORITHM LABORATORY\n");
    printf("============================================\n");
    printf("1. Maximum Subarray\n");
    printf("2. Fast Power\n");
    printf("3. Celebrity Problem\n");
    printf("0. Back\n");
    printf("============================================\n");
    printf("Select algorithm: ");

    if (scanf("%d", &algorithm_choice) != 1)
    {
        printf("Invalid input.\n");

        while (getchar() != '\n')
        {
        }

        break;
    }

    if (algorithm_choice == 1)
    {
        double values[] = {
            -2.0, 5.0, -1.0, 8.0,
            12.0, -3.0, 4.0
        };

        int count =
            sizeof(values) / sizeof(values[0]);

        MaxSubarrayResult result =
            maximum_subarray(values, count);

        printf("\nMaximum Subarray Result\n");
        printf("Start index : %d\n", result.left);
        printf("End index   : %d\n", result.right);
        printf("Maximum sum : %.2f\n", result.sum);
    }
    else if (algorithm_choice == 2)
    {
        long long base;
        unsigned int exponent;

        printf("Enter base: ");
        scanf("%lld", &base);

        printf("Enter exponent: ");
        scanf("%u", &exponent);

        printf(
            "\nResult: %lld\n",
            fast_power(base, exponent)
        );
    }
    else if (algorithm_choice == 3)
    {
        int relationships[10][10] = {0};

        int people = 4;

        /*
         * Person 2 is the celebrity.
         */

        relationships[0][2] = 1;
        relationships[1][2] = 1;
        relationships[3][2] = 1;

        relationships[0][1] = 1;
        relationships[1][3] = 1;

        int celebrity =
            find_celebrity(relationships, people);

        if (celebrity >= 0)
        {
            printf(
                "\nCelebrity found: Person %d\n",
                celebrity
            );
        }
        else
        {
            printf("\nNo celebrity found.\n");
        }
    }
    else if (algorithm_choice != 0)
    {
        printf("Invalid algorithm choice.\n");
    }

    break;
}

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
#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "dataset.h"
#include "transaction.h"
#include "fraud.h"
#include "sorting.h"
#include "searching.h"
#include "divide_conquer.h"
#include "matrix_algorithms.h"

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
            /*
             * OPTION 1
             * Load banking transaction dataset
             */
            case 1:
            {
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
            }

            /*
             * OPTION 2
             * View loaded transactions
             */
            case 2:
            {
                print_all_transactions(
                    transactions,
                    transaction_count
                );

                break;
            }

            /*
             * OPTION 3
             * Fraud investigation
             */
            case 3:
            {
                analyze_fraud(
                    transactions,
                    transaction_count
                );

                break;
            }

            /*
             * OPTION 4
             * Sorting and searching
             */
            case 4:
            {
                int operation_choice;

                if (transaction_count <= 0)
                {
                    printf("No dataset is currently loaded.\n");
                    printf("Please load a dataset first.\n");
                    break;
                }

                printf("\n");
                printf("============================================================\n");
                printf("              TRANSACTION SEARCH AND SORT\n");
                printf("============================================================\n");
                printf("1. Merge Sort by Amount\n");
                printf("2. Quick Sort by Amount\n");
                printf("3. Iterative Binary Search by Transaction ID\n");
                printf("4. Recursive Binary Search by Transaction ID\n");
                printf("0. Back\n");
                printf("============================================================\n");
                printf("Select operation: ");

                if (scanf("%d", &operation_choice) != 1)
                {
                    printf("Invalid input.\n");

                    while (getchar() != '\n')
                    {
                        /* Clear invalid input */
                    }

                    break;
                }

                /*
                 * Merge Sort
                 */
                if (operation_choice == 1)
                {
                    merge_sort_transactions(
                        transactions,
                        transaction_count
                    );

                    printf(
                        "\nTransactions sorted using Merge Sort.\n"
                    );

                    print_all_transactions(
                        transactions,
                        transaction_count
                    );
                }

                /*
                 * Quick Sort
                 */
                else if (operation_choice == 2)
                {
                    quick_sort_transactions(
                        transactions,
                        transaction_count
                    );

                    printf(
                        "\nTransactions sorted using Quick Sort.\n"
                    );

                    print_all_transactions(
                        transactions,
                        transaction_count
                    );
                }

                /*
                 * Binary Search
                 */
                else if (
                    operation_choice == 3 ||
                    operation_choice == 4
                )
                {
                    char search_id[ID_LENGTH];
                    int result;

                    printf("Enter Transaction ID: ");

                    if (scanf("%19s", search_id) != 1)
                    {
                        printf("Invalid Transaction ID.\n");
                        break;
                    }

                    /*
                     * Binary search requires sorted data.
                     */
                    sort_transactions_by_id(
                        transactions,
                        transaction_count
                    );

                    /*
                     * Iterative Binary Search
                     */
                    if (operation_choice == 3)
                    {
                        result = binary_search_iterative(
                            transactions,
                            transaction_count,
                            search_id
                        );

                        printf(
                            "\nAlgorithm: "
                            "Iterative Binary Search\n"
                        );
                    }

                    /*
                     * Recursive Binary Search
                     */
                    else
                    {
                        result = binary_search_recursive(
                            transactions,
                            transaction_count,
                            search_id
                        );

                        printf(
                            "\nAlgorithm: "
                            "Recursive Binary Search\n"
                        );
                    }

                    if (result >= 0)
                    {
                        printf(
                            "Transaction found at index %d.\n",
                            result
                        );

                        print_transaction(
                            &transactions[result]
                        );
                    }
                    else
                    {
                        printf(
                            "Transaction '%s' was not found.\n",
                            search_id
                        );
                    }
                }

                else if (operation_choice != 0)
                {
                    printf("Invalid operation.\n");
                }

                break;
            }

            /*
             * OPTION 5
             * Pattern matching module
             */
            case 5:
            {
                printf("Pattern Search - Coming Soon\n");
                break;
            }

            /*
             * OPTION 6
             * Graph algorithms
             */
            case 6:
            {
                printf(
                    "Fraud Network Analysis - Coming Soon\n"
                );

                break;
            }

            /*
             * OPTION 7
             * Optimization and investigation planning
             */
            case 7:
            {
                printf(
                    "Investigation Planning - Coming Soon\n"
                );

                break;
            }

            /*
             * OPTION 8
             * DAA Algorithm Laboratory
             */
            case 8:
            {
                int algorithm_choice;

                printf("\n");
                printf("============================================================\n");
                printf("                DAA ALGORITHM LABORATORY\n");
                printf("============================================================\n");
                printf("1. Maximum Subarray\n");
                printf("2. Fast Power\n");
                printf("3. Celebrity Problem\n");
                printf(
                    "4. Classical vs Strassen "
                    "Matrix Multiplication\n"
                );
                printf("0. Back\n");
                printf("============================================================\n");
                printf("Select algorithm: ");

                if (scanf("%d", &algorithm_choice) != 1)
                {
                    printf("Invalid input.\n");

                    while (getchar() != '\n')
                    {
                        /* Clear invalid input */
                    }

                    break;
                }

                /*
                 * Maximum Subarray
                 */
                if (algorithm_choice == 1)
                {
                    double values[] = {
                        -2.0,
                        5.0,
                        -1.0,
                        8.0,
                        12.0,
                        -3.0,
                        4.0
                    };

                    int count =
                        sizeof(values) /
                        sizeof(values[0]);

                    MaxSubarrayResult result =
                        maximum_subarray(
                            values,
                            count
                        );

                    printf("\nMaximum Subarray Result\n");
                    printf(
                        "Start index : %d\n",
                        result.left
                    );
                    printf(
                        "End index   : %d\n",
                        result.right
                    );
                    printf(
                        "Maximum sum : %.2f\n",
                        result.sum
                    );
                }

                /*
                 * Fast Power
                 */
                else if (algorithm_choice == 2)
                {
                    long long base;
                    unsigned int exponent;

                    printf("Enter base: ");

                    if (scanf("%lld", &base) != 1)
                    {
                        printf("Invalid base.\n");
                        break;
                    }

                    printf("Enter exponent: ");

                    if (scanf("%u", &exponent) != 1)
                    {
                        printf("Invalid exponent.\n");
                        break;
                    }

                    printf(
                        "\nResult: %lld\n",
                        fast_power(
                            base,
                            exponent
                        )
                    );
                }

                /*
                 * Celebrity Problem
                 */
                else if (algorithm_choice == 3)
                {
                    int relationships[10][10] = {0};
                    int people = 4;

                    /*
                     * Person 2 is deliberately
                     * configured as the celebrity.
                     */
                    relationships[0][2] = 1;
                    relationships[1][2] = 1;
                    relationships[3][2] = 1;

                    relationships[0][1] = 1;
                    relationships[1][3] = 1;

                    int celebrity =
                        find_celebrity(
                            relationships,
                            people
                        );

                    if (celebrity >= 0)
                    {
                        printf(
                            "\nCelebrity found: "
                            "Person %d\n",
                            celebrity
                        );
                    }
                    else
                    {
                        printf(
                            "\nNo celebrity found.\n"
                        );
                    }
                }

                /*
                 * Classical vs Strassen
                 * Matrix Multiplication
                 */
                else if (algorithm_choice == 4)
{
    int A[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};
    int B[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};

    int classical_result
        [MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};

    int strassen_result
        [MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};

    int size = 2;
    int i;
    int j;

    printf("\n============================================\n");
    printf("       MATRIX MULTIPLICATION COMPARISON\n");
    printf("============================================\n");

    printf("\nEnter values for Matrix A (2 x 2):\n");

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            printf("A[%d][%d] = ", i, j);

            if (scanf("%d", &A[i][j]) != 1)
            {
                printf("Invalid matrix value.\n");

                while (getchar() != '\n')
                {
                    /* Clear invalid input */
                }

                break;
            }
        }
    }

    printf("\nEnter values for Matrix B (2 x 2):\n");

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            printf("B[%d][%d] = ", i, j);

            if (scanf("%d", &B[i][j]) != 1)
            {
                printf("Invalid matrix value.\n");

                while (getchar() != '\n')
                {
                    /* Clear invalid input */
                }

                break;
            }
        }
    }

    classical_matrix_multiply(
        size,
        A,
        B,
        classical_result
    );

    strassen_matrix_multiply(
        size,
        A,
        B,
        strassen_result
    );

    printf("\nMatrix A:\n");
    print_matrix(size, A);

    printf("\nMatrix B:\n");
    print_matrix(size, B);

    printf("\nClassical Multiplication Result:\n");
    print_matrix(
        size,
        classical_result
    );

    printf("\nStrassen Multiplication Result:\n");
    print_matrix(
        size,
        strassen_result
    );

    /*
     * Verify that both algorithms produced
     * exactly the same matrix.
     */
    int results_match = 1;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (classical_result[i][j] !=
                strassen_result[i][j])
            {
                results_match = 0;
            }
        }
    }

    printf("\nCorrectness Check: ");

    if (results_match)
    {
        printf("PASS\n");
        printf(
            "Both algorithms produced "
            "the same result.\n"
        );
    }
    else
    {
        printf("FAIL\n");
        printf(
            "The algorithms produced "
            "different results.\n"
        );
    }
} 

                /*
                 * 0 simply returns to main menu.
                 */
                else if (algorithm_choice != 0)
                {
                    printf(
                        "Invalid algorithm choice.\n"
                    );
                }

                break;
            }

            /*
             * OPTION 9
             * Benchmark runner
             */
            case 9:
            {
                printf(
                    "Benchmark Runner - Coming Soon\n"
                );

                break;
            }

            /*
             * OPTION 10
             * Test suite
             */
            case 10:
            {
                printf("Test Suite - Coming Soon\n");
                break;
            }

            /*
             * OPTION 11
             * Export results
             */
            case 11:
            {
                printf(
                    "Export Results - Coming Soon\n"
                );

                break;
            }

            /*
             * EXIT
             */
            case 0:
            {
                printf(
                    "Exiting Fraud Investigation "
                    "Workbench...\n"
                );

                break;
            }

            default:
            {
                printf(
                    "Invalid choice. "
                    "Please select 0 to 11.\n"
                );

                break;
            }
        }

    } while (choice != 0);

    /*
     * Release dynamically allocated
     * transaction memory.
     */
    free(transactions);

    return 0;
}
#include <stdio.h>

#include "search_sort_menu.h"
#include "sorting.h"
#include "searching.h"


void run_search_sort_menu(
    Transaction transactions[],
    size_t transaction_count
)
{
    if (
        transactions == NULL ||
        transaction_count == 0
    )
    {
        printf(
            "No dataset is currently loaded.\n"
        );

        printf(
            "Please load a dataset first.\n"
        );

        return;
    }


    int operation_choice;


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


    if (
        scanf(
            "%d",
            &operation_choice
        ) != 1
    )
    {
        printf(
            "Invalid input.\n"
        );

        while (getchar() != '\n')
        {
        }

        return;
    }


    /*
     * MERGE SORT
     */
    if (operation_choice == 1)
    {
        merge_sort_transactions(
            transactions,
            (int)transaction_count
        );

        printf(
            "\nMerge Sort completed successfully.\n"
        );

        printf(
            "Transactions sorted: %zu\n",
            transaction_count
        );

        printf(
            "Sort key           : Amount (ascending)\n"
        );
    }


    /*
     * QUICK SORT
     */
    else if (operation_choice == 2)
    {
        quick_sort_transactions(
            transactions,
            (int)transaction_count
        );

        printf(
            "\nQuick Sort completed successfully.\n"
        );

        printf(
            "Transactions sorted: %zu\n",
            transaction_count
        );

        printf(
            "Sort key           : Amount (ascending)\n"
        );
    }


    /*
     * BINARY SEARCH
     */
    else if (
        operation_choice == 3 ||
        operation_choice == 4
    )
    {
        char search_id[
            ID_LENGTH
        ];

        int result;


        printf(
            "Enter Transaction ID: "
        );


        if (
            scanf(
                "%31s",
                search_id
            ) != 1
        )
        {
            printf(
                "Invalid Transaction ID.\n"
            );

            while (getchar() != '\n')
            {
            }

            return;
        }


        /*
         * Binary Search requires records
         * sorted by Transaction ID.
         */
        sort_transactions_by_id(
            transactions,
            (int)transaction_count
        );


        if (operation_choice == 3)
        {
            result =
                binary_search_iterative(
                    transactions,
                    (int)transaction_count,
                    search_id
                );

            printf(
                "\nAlgorithm: "
                "Iterative Binary Search\n"
            );
        }

        else
        {
            result =
                binary_search_recursive(
                    transactions,
                    (int)transaction_count,
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
                "Transaction found at "
                "index %d.\n\n",
                result
            );

            print_transaction(
                &transactions[result]
            );
        }

        else
        {
            printf(
                "Transaction '%s' "
                "was not found.\n",
                search_id
            );
        }
    }


    /*
     * BACK
     */
    else if (operation_choice == 0)
    {
        return;
    }


    else
    {
        printf(
            "Invalid operation.\n"
        );
    }
}
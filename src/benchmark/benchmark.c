#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "benchmark.h"
#include "sorting.h"
#include "transaction.h"


static void generate_transactions(
    Transaction transactions[],
    int count
)
{
    int i;

    for (i = 0; i < count; i++)
    {
        snprintf(
            transactions[i].transaction_id,
            ID_LENGTH,
            "B%06d",
            i
        );

        /*
         * Deterministic pseudo-random-looking
         * transaction amount.
         *
         * No rand() is used so repeated
         * benchmark runs receive identical data.
         */
        transactions[i].amount =
            (double)(
                ((i * 7919) + 104729)
                % 100000
            ) + 1.0;

        transactions[i].risk_score = 0;
    }
}


static int is_sorted(
    const Transaction transactions[],
    int count
)
{
    for (int i = 1; i < count; i++)
    {
        if (
            transactions[i - 1].amount >
            transactions[i].amount
        )
        {
            return 0;
        }
    }

    return 1;
}


static int same_sorted_result(
    const Transaction first[],
    const Transaction second[],
    int count
)
{
    for (int i = 0; i < count; i++)
    {
        if (
            first[i].amount !=
            second[i].amount
        )
        {
            return 0;
        }
    }

    return 1;
}


void run_sorting_benchmark(void)
{
    int dataset_choice;
    int count;

    printf("\n");
    printf("============================================================\n");
    printf("                    BENCHMARK RUNNER\n");
    printf("============================================================\n");
    printf("1. Small Dataset       (100 transactions)\n");
    printf("2. Medium Dataset      (1,000 transactions)\n");
    printf("3. Large Dataset       (10,000 transactions)\n");
    printf("4. Adversarial Dataset (10,000 sorted transactions)\n");
    printf("0. Back\n");
    printf("============================================================\n");
    printf("Select dataset: ");

    if (scanf("%d", &dataset_choice) != 1)
    {
        printf("Invalid input.\n");

        while (getchar() != '\n')
        {
        }

        return;
    }

    if (dataset_choice == 0)
    {
        return;
    }

    if (dataset_choice == 1)
    {
        count = 100;
    }
    else if (dataset_choice == 2)
    {
        count = 1000;
    }
    else if (
        dataset_choice == 3 ||
        dataset_choice == 4
    )
    {
        count = 10000;
    }
    else
    {
        printf("Invalid dataset selection.\n");
        return;
    }


    Transaction *original =
        malloc(
            count *
            sizeof(Transaction)
        );

    Transaction *merge_data =
        malloc(
            count *
            sizeof(Transaction)
        );

    Transaction *quick_data =
        malloc(
            count *
            sizeof(Transaction)
        );


    if (
        original == NULL ||
        merge_data == NULL ||
        quick_data == NULL
    )
    {
        printf(
            "ERROR: Benchmark memory allocation failed.\n"
        );

        free(original);
        free(merge_data);
        free(quick_data);

        return;
    }


    generate_transactions(
        original,
        count
    );


    /*
     * Adversarial case for our Quick Sort:
     *
     * Our implementation chooses the last
     * element as pivot. Already-sorted data
     * can therefore produce highly unbalanced
     * partitions.
     */
    if (dataset_choice == 4)
    {
        merge_sort_transactions(
            original,
            count
        );
    }


    /*
     * Both algorithms MUST receive
     * exactly the same input.
     */
    memcpy(
        merge_data,
        original,
        count * sizeof(Transaction)
    );

    memcpy(
        quick_data,
        original,
        count * sizeof(Transaction)
    );


    printf("\nRunning benchmark...\n");

    printf(
        "Transactions: %d\n",
        count
    );


    /*
     * MERGE SORT
     */
    clock_t merge_start =
        clock();

    merge_sort_transactions(
        merge_data,
        count
    );

    clock_t merge_end =
        clock();


    /*
     * QUICK SORT
     */
    clock_t quick_start =
        clock();

    quick_sort_transactions(
        quick_data,
        count
    );

    clock_t quick_end =
        clock();


    double merge_ms =
        (
            (double)(
                merge_end -
                merge_start
            ) /
            CLOCKS_PER_SEC
        ) * 1000.0;


    double quick_ms =
        (
            (double)(
                quick_end -
                quick_start
            ) /
            CLOCKS_PER_SEC
        ) * 1000.0;


    int merge_correct =
        is_sorted(
            merge_data,
            count
        );

    int quick_correct =
        is_sorted(
            quick_data,
            count
        );

    int same_result =
        same_sorted_result(
            merge_data,
            quick_data,
            count
        );


    /*
     * Approximate transaction-array
     * storage used by the benchmark copy.
     *
     * Later memory benchmarking will
     * distinguish algorithmic auxiliary
     * memory from dataset storage.
     */
    double dataset_memory_kb =
        (
            (double)(
                count *
                sizeof(Transaction)
            )
        ) / 1024.0;


    printf("\n");
    printf("====================================================================\n");
    printf("                       SORTING BENCHMARK\n");
    printf("====================================================================\n");

    printf(
        "%-15s %-15s %-15s %-12s\n",
        "ALGORITHM",
        "TIME (ms)",
        "DATA (KB)",
        "CORRECT"
    );

    printf(
        "--------------------------------------------------------------------\n"
    );

    printf(
        "%-15s %-15.3f %-15.2f %-12s\n",
        "Merge Sort",
        merge_ms,
        dataset_memory_kb,
        merge_correct ? "PASS" : "FAIL"
    );

    printf(
        "%-15s %-15.3f %-15.2f %-12s\n",
        "Quick Sort",
        quick_ms,
        dataset_memory_kb,
        quick_correct ? "PASS" : "FAIL"
    );

    printf(
        "--------------------------------------------------------------------\n"
    );


    printf(
        "Identical sorted result: %s\n",
        same_result ? "PASS" : "FAIL"
    );


    if (dataset_choice == 4)
    {
        printf(
            "\nAdversarial condition:\n"
        );

        printf(
            "Input was already sorted before "
            "Quick Sort execution.\n"
        );

        printf(
            "Last-element pivot selection may "
            "cause O(n^2) behavior.\n"
        );
    }


    printf("\nTheoretical Complexity\n");
    printf("----------------------------------------\n");
    printf(
        "Merge Sort : O(n log n) "
        "best/average/worst\n"
    );

    printf(
        "Quick Sort : O(n log n) average, "
        "O(n^2) worst\n"
    );


    free(original);
    free(merge_data);
    free(quick_data);
}
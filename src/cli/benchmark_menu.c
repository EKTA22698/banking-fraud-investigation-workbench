#include <stdio.h>

#include "benchmark_menu.h"
#include "benchmark.h"


void run_benchmark_menu(
    Transaction transactions[],
    size_t transaction_count,
    int is_paysim
)
{
    int benchmark_choice;

    printf("\n");
    printf("============================================================\n");
    printf("                    BENCHMARK RUNNER\n");
    printf("============================================================\n");

    printf("1. Sorting Algorithms\n");
    printf("2. String Matching Algorithms\n");
    printf("3. Matrix Multiplication\n");
    printf("4. Graph Algorithms\n");
    printf("5. Run Complete Benchmark Suite\n");
    printf("6. PaySim Scalability and Fraud Quality\n");
    printf("0. Back\n");

    printf("============================================================\n");
    printf("Select benchmark: ");


    if (
        scanf(
            "%d",
            &benchmark_choice
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
     * SORTING
     */
    if (benchmark_choice == 1)
    {
        run_sorting_benchmark();
    }


    /*
     * STRING MATCHING
     */
    else if (benchmark_choice == 2)
    {
        run_string_matching_benchmark();
    }


    /*
     * MATRIX MULTIPLICATION
     */
    else if (benchmark_choice == 3)
    {
        run_matrix_benchmark();
    }


    /*
     * GRAPH ALGORITHMS
     */
    else if (benchmark_choice == 4)
    {
        run_graph_benchmark();
    }


    /*
     * COMPLETE NON-INTERACTIVE SUITE
     */
    else if (benchmark_choice == 5)
    {
        run_complete_benchmark_suite();
    }


    /*
     * PAYSIM LARGE-DATA BENCHMARK
     */
    else if (benchmark_choice == 6)
    {
        if (
            !is_paysim ||
            transactions == NULL ||
            transaction_count == 0
        )
        {
            printf("\n");
            printf(
                "PaySim dataset is not loaded.\n"
            );

            printf(
                "Load Option 1 -> "
                "PaySim Public Fraud Dataset first.\n"
            );

            return;
        }


        run_paysim_benchmark(
            transactions,
            transaction_count
        );
    }


    /*
     * BACK
     */
    else if (benchmark_choice == 0)
    {
        return;
    }


    else
    {
        printf(
            "Invalid benchmark choice.\n"
        );
    }
}
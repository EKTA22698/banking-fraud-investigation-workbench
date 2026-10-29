#include <stdio.h>
#include <time.h>

#include "benchmark.h"
#include "matrix_algorithms.h"


static void generate_matrix_data(
    int size,
    int A[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    int B[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE]
)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            /*
             * Deterministic values so both
             * algorithms always receive
             * exactly the same matrices.
             */
            A[i][j] =
                ((i * size + j + 1) % 9) + 1;

            B[i][j] =
                (((i + 1) * (j + 2)) % 9) + 1;
        }
    }
}


static double matrix_elapsed_ms(
    clock_t start,
    clock_t end
)
{
    return (
        (double)(end - start) /
        CLOCKS_PER_SEC
    ) * 1000.0;
}


static void benchmark_matrix_size(
    int size
)
{
    int A
        [MATRIX_MAX_SIZE]
        [MATRIX_MAX_SIZE] = {0};

    int B
        [MATRIX_MAX_SIZE]
        [MATRIX_MAX_SIZE] = {0};

    int classical_result
        [MATRIX_MAX_SIZE]
        [MATRIX_MAX_SIZE] = {0};

    int strassen_result
        [MATRIX_MAX_SIZE]
        [MATRIX_MAX_SIZE] = {0};


    generate_matrix_data(
        size,
        A,
        B
    );


    /*
     * Classical multiplication.
     */
    clock_t classical_start =
        clock();

    classical_matrix_multiply(
        size,
        A,
        B,
        classical_result
    );

    clock_t classical_end =
        clock();


    /*
     * Recursive Strassen.
     */
    clock_t strassen_start =
        clock();

    strassen_matrix_multiply(
        size,
        A,
        B,
        strassen_result
    );

    clock_t strassen_end =
        clock();


    double classical_ms =
        matrix_elapsed_ms(
            classical_start,
            classical_end
        );

    double strassen_ms =
        matrix_elapsed_ms(
            strassen_start,
            strassen_end
        );


    int correct =
        matrices_equal(
            size,
            classical_result,
            strassen_result
        );


    printf(
        "%-8s %-15.6f %-15.6f %-12s\n",
        size == 2 ? "2x2" :
        size == 4 ? "4x4" : "8x8",
        classical_ms,
        strassen_ms,
        correct ? "PASS" : "FAIL"
    );
}


void run_matrix_benchmark(void)
{
    int benchmark_choice;

    printf("\n");
    printf("============================================================\n");
    printf("             MATRIX MULTIPLICATION BENCHMARK\n");
    printf("============================================================\n");

    printf("1. Benchmark 2 x 2\n");
    printf("2. Benchmark 4 x 4\n");
    printf("3. Benchmark 8 x 8\n");
    printf("4. Compare All Sizes\n");
    printf("0. Back\n");

    printf("============================================================\n");
    printf("Select matrix benchmark: ");

    if (
        scanf(
            "%d",
            &benchmark_choice
        ) != 1
    )
    {
        printf("Invalid input.\n");

        while (getchar() != '\n')
        {
        }

        return;
    }


    if (
        benchmark_choice < 0 ||
        benchmark_choice > 4
    )
    {
        printf(
            "Invalid matrix benchmark choice.\n"
        );

        return;
    }


    if (benchmark_choice == 0)
    {
        return;
    }


    printf("\n");
    printf("====================================================================\n");
    printf("                   MATRIX BENCHMARK RESULTS\n");
    printf("====================================================================\n");

    printf(
        "%-8s %-15s %-15s %-12s\n",
        "SIZE",
        "CLASSICAL(ms)",
        "STRASSEN(ms)",
        "CORRECT"
    );

    printf(
        "--------------------------------------------------------------------\n"
    );


    if (benchmark_choice == 1)
    {
        benchmark_matrix_size(2);
    }

    else if (benchmark_choice == 2)
    {
        benchmark_matrix_size(4);
    }

    else if (benchmark_choice == 3)
    {
        benchmark_matrix_size(8);
    }

    else if (benchmark_choice == 4)
    {
        benchmark_matrix_size(2);
        benchmark_matrix_size(4);
        benchmark_matrix_size(8);
    }


    printf(
        "--------------------------------------------------------------------\n"
    );

    printf("\nTheoretical Complexity\n");
    printf("----------------------------------------\n");

    printf(
        "Classical : O(n^3)\n"
    );

    printf(
        "Strassen  : O(n^log2(7)) "
        "~ O(n^2.807)\n"
    );

    printf("\nInterpretation:\n");

    printf(
        "For very small matrices, Classical "
        "multiplication may be faster because "
        "Strassen has recursion and temporary-"
        "matrix overhead.\n"
    );

    printf(
        "Strassen's asymptotic advantage becomes "
        "relevant only at sufficiently large "
        "matrix sizes with an efficient implementation.\n"
    );
}
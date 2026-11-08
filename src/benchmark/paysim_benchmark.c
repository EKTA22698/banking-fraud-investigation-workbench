#include <stdio.h>
#include <time.h>

#include "benchmark.h"
#include "fraud.h"
#include "transaction.h"


static void benchmark_paysim_size(
    Transaction transactions[],
    size_t count,
    int threshold
)
{
    clock_t start = clock();

    FraudEvaluation evaluation =
        evaluate_paysim_fraud(
            transactions,
            count,
            threshold
        );

    clock_t end = clock();


    double seconds =
        (double)(end - start) /
        CLOCKS_PER_SEC;

    double milliseconds =
        seconds * 1000.0;


    double throughput = 0.0;

    if (seconds > 0.0)
    {
        throughput =
            count / seconds;
    }


    double memory_mb =
        (
            (double)count *
            sizeof(Transaction)
        ) /
        (1024.0 * 1024.0);


    printf(
        "%-12zu %-12.3f %-15.0f %-12.2f "
        "%-10.2f %-10.2f %-10.2f\n",
        count,
        milliseconds,
        throughput,
        memory_mb,
        evaluation.precision,
        evaluation.recall,
        evaluation.f1_score
    );
}


void run_paysim_benchmark(
    Transaction transactions[],
    size_t count
)
{
    if (
        transactions == NULL ||
        count == 0
    )
    {
        printf(
            "\nPaySim dataset is not loaded.\n"
        );

        return;
    }


    const int threshold = 50;


    printf("\n");
    printf(
        "==========================================================================\n"
    );

    printf(
        "                         PAYSIM SCALABILITY BENCHMARK\n"
    );

    printf(
        "==========================================================================\n"
    );

    printf(
        "Risk threshold: %d\n\n",
        threshold
    );


    printf(
        "%-12s %-12s %-15s %-12s "
        "%-10s %-10s %-10s\n",
        "RECORDS",
        "TIME(ms)",
        "TXN/SEC",
        "MEMORY(MB)",
        "PREC(%)",
        "RECALL(%)",
        "F1(%)"
    );

    printf(
        "--------------------------------------------------------------------------\n"
    );


    /*
     * Small scalability sample.
     */
    if (count >= 10000)
    {
        benchmark_paysim_size(
            transactions,
            10000,
            threshold
        );
    }


    /*
     * Medium scalability sample.
     */
    if (count >= 100000)
    {
        benchmark_paysim_size(
            transactions,
            100000,
            threshold
        );
    }


    /*
     * Large scalability sample.
     */
    if (count >= 1000000)
    {
        benchmark_paysim_size(
            transactions,
            1000000,
            threshold
        );
    }


    /*
     * Full dataset.
     */
    benchmark_paysim_size(
        transactions,
        count,
        threshold
    );


    printf(
        "--------------------------------------------------------------------------\n"
    );

    printf(
        "\nInterpretation:\n"
    );

    printf(
        "- Runtime should grow approximately "
        "linearly with transaction count.\n"
    );

    printf(
        "- Dataset memory grows linearly because "
        "each transaction occupies fixed struct storage.\n"
    );

    printf(
        "- Precision, Recall and F1 measure fraud "
        "detection quality rather than raw speed.\n"
    );

    printf(
        "==========================================================================\n"
    );
}
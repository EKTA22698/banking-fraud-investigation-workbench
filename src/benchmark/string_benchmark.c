#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "benchmark.h"
#include "string_matching.h"


static void generate_benchmark_text(
    char text[],
    int length,
    int adversarial
)
{
    int i;

    if (adversarial)
    {
        /*
         * Repeated characters create a difficult
         * case for simple matching strategies.
         */
        for (i = 0; i < length; i++)
        {
            text[i] = 'A';
        }
    }
    else
    {
        const char sequence[] =
            "TRANSFER_CARD_ATM_CRYPTO_PAYMENT_";

        int sequence_length =
            (int)strlen(sequence);

        for (i = 0; i < length; i++)
        {
            text[i] =
                sequence[i % sequence_length];
        }
    }

    text[length] = '\0';
}


static double elapsed_ms(
    clock_t start,
    clock_t end
)
{
    return (
        (double)(end - start) /
        CLOCKS_PER_SEC
    ) * 1000.0;
}


void run_string_matching_benchmark(void)
{
    int dataset_choice;
    int text_length;

    char pattern[PATTERN_MAX_LENGTH + 1];

    printf("\n");
    printf("============================================================\n");
    printf("              STRING MATCHING BENCHMARK\n");
    printf("============================================================\n");
    printf("1. Small Dataset       (1,000 characters)\n");
    printf("2. Medium Dataset      (10,000 characters)\n");
    printf("3. Large Dataset       (100,000 characters)\n");
    printf("4. Adversarial Dataset (100,000 repeated characters)\n");
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
        text_length = 1000;
    }
    else if (dataset_choice == 2)
    {
        text_length = 10000;
    }
    else if (
        dataset_choice == 3 ||
        dataset_choice == 4
    )
    {
        text_length = 100000;
    }
    else
    {
        printf("Invalid dataset selection.\n");
        return;
    }


    char *text =
        malloc(
            (text_length + 1) *
            sizeof(char)
        );

    if (text == NULL)
    {
        printf(
            "ERROR: Unable to allocate benchmark text.\n"
        );

        return;
    }


    generate_benchmark_text(
        text,
        text_length,
        dataset_choice == 4
    );


    if (dataset_choice == 4)
    {
        strcpy(
            pattern,
            "AAAAAB"
        );
    }
    else
    {
        strcpy(
            pattern,
            "CRYPTO"
        );
    }


    printf("\nBenchmark Input\n");
    printf("----------------------------------------\n");
    printf("Text length    : %d\n", text_length);
    printf("Pattern        : %s\n", pattern);

    if (dataset_choice == 4)
    {
        printf(
            "Input condition : Repeated-character adversarial case\n"
        );
    }
    else
    {
        printf(
            "Input condition : Banking event sequence\n"
        );
    }


    clock_t start;
    clock_t end;


    /*
     * NAIVE
     */
    start = clock();

    MatchResult naive =
        naive_pattern_search(
            text,
            pattern
        );

    end = clock();

    double naive_ms =
        elapsed_ms(
            start,
            end
        );


    /*
     * RABIN-KARP
     */
    start = clock();

    MatchResult rabin =
        rabin_karp_search(
            text,
            pattern
        );

    end = clock();

    double rabin_ms =
        elapsed_ms(
            start,
            end
        );


    /*
     * FINITE AUTOMATON
     */
    start = clock();

    MatchResult automaton =
        finite_automaton_search(
            text,
            pattern
        );

    end = clock();

    double automaton_ms =
        elapsed_ms(
            start,
            end
        );


    /*
     * KMP
     */
    start = clock();

    MatchResult kmp =
        kmp_search(
            text,
            pattern
        );

    end = clock();

    double kmp_ms =
        elapsed_ms(
            start,
            end
        );


    int correctness =
        match_results_equal(
            &naive,
            &rabin
        ) &&
        match_results_equal(
            &naive,
            &automaton
        ) &&
        match_results_equal(
            &naive,
            &kmp
        );


    printf("\n");
    printf("====================================================================\n");
    printf("                  STRING MATCHING RESULTS\n");
    printf("====================================================================\n");

    printf(
        "%-20s %-15s %-15s\n",
        "ALGORITHM",
        "TIME (ms)",
        "MATCHES"
    );

    printf(
        "--------------------------------------------------------------------\n"
    );

    printf(
        "%-20s %-15.3f %-15d\n",
        "Naive",
        naive_ms,
        naive.count
    );

    printf(
        "%-20s %-15.3f %-15d\n",
        "Rabin-Karp",
        rabin_ms,
        rabin.count
    );

    printf(
        "%-20s %-15.3f %-15d\n",
        "Finite Automaton",
        automaton_ms,
        automaton.count
    );

    printf(
        "%-20s %-15.3f %-15d\n",
        "KMP",
        kmp_ms,
        kmp.count
    );

    printf(
        "--------------------------------------------------------------------\n"
    );


    printf(
        "Correctness Check: %s\n",
        correctness ? "PASS" : "FAIL"
    );

    if (correctness)
    {
        printf(
            "All algorithms produced identical match positions.\n"
        );
    }


    printf("\nTheoretical Complexity\n");
    printf("----------------------------------------\n");
    printf("Naive            : O(n*m) worst case\n");
    printf(
        "Rabin-Karp       : O(n+m) average, O(n*m) worst case\n"
    );
    printf(
        "Finite Automaton : O(n) search after preprocessing\n"
    );
    printf("KMP              : O(n+m)\n");


    free(text);
}
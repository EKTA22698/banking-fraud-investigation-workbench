#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "benchmark.h"
#include "transaction.h"
#include "sorting.h"
#include "string_matching.h"
#include "matrix_algorithms.h"
#include "graph_algorithms.h"


static double benchmark_ms(
    clock_t start,
    clock_t end
)
{
    return (
        (double)(end - start) /
        CLOCKS_PER_SEC
    ) * 1000.0;
}


static int benchmark_is_sorted(
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


static void generate_sort_data(
    Transaction transactions[],
    int count
)
{
    for (int i = 0; i < count; i++)
    {
        memset(
            &transactions[i],
            0,
            sizeof(Transaction)
        );

        transactions[i].amount =
            (double)(
                ((i * 7919) + 104729)
                % 100000
            ) + 1.0;
    }
}


static void run_complete_sorting(void)
{
    const int count = 10000;

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
            "%-24s %-12s\n",
            "Sorting",
            "MEMORY FAIL"
        );

        free(original);
        free(merge_data);
        free(quick_data);

        return;
    }


    generate_sort_data(
        original,
        count
    );

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


    clock_t start =
        clock();

    merge_sort_transactions(
        merge_data,
        count
    );

    clock_t end =
        clock();

    double merge_ms =
        benchmark_ms(
            start,
            end
        );


    start = clock();

    quick_sort_transactions(
        quick_data,
        count
    );

    end = clock();

    double quick_ms =
        benchmark_ms(
            start,
            end
        );


    int correct =
        benchmark_is_sorted(
            merge_data,
            count
        ) &&
        benchmark_is_sorted(
            quick_data,
            count
        );


    for (
        int i = 0;
        i < count && correct;
        i++
    )
    {
        if (
            merge_data[i].amount !=
            quick_data[i].amount
        )
        {
            correct = 0;
        }
    }


    printf("\n[SORTING - 10,000 TRANSACTIONS]\n");

    printf(
        "%-24s %12.3f ms\n",
        "Merge Sort",
        merge_ms
    );

    printf(
        "%-24s %12.3f ms\n",
        "Quick Sort",
        quick_ms
    );

    printf(
        "%-24s %12s\n",
        "Correctness",
        correct ? "PASS" : "FAIL"
    );


    double memory_mb =
        (
            3.0 *
            count *
            sizeof(Transaction)
        ) /
        (1024.0 * 1024.0);


    printf(
        "%-24s %12.2f MB\n",
        "Benchmark data memory",
        memory_mb
    );


    free(original);
    free(merge_data);
    free(quick_data);
}


static void run_complete_strings(void)
{
    const int text_length =
        100000;

    char *text =
        malloc(
            (text_length + 1) *
            sizeof(char)
        );


    if (text == NULL)
    {
        printf(
            "\n[STRING MATCHING]\n"
            "Memory allocation failed.\n"
        );

        return;
    }


    const char sequence[] =
        "TRANSFER_CARD_ATM_CRYPTO_PAYMENT_";

    int sequence_length =
        (int)strlen(sequence);


    for (
        int i = 0;
        i < text_length;
        i++
    )
    {
        text[i] =
            sequence[
                i %
                sequence_length
            ];
    }

    text[text_length] =
        '\0';


    const char *pattern =
        "CRYPTO";


    clock_t start;
    clock_t end;


    start = clock();

    MatchResult naive =
        naive_pattern_search(
            text,
            pattern
        );

    end = clock();

    double naive_ms =
        benchmark_ms(
            start,
            end
        );


    start = clock();

    MatchResult rabin =
        rabin_karp_search(
            text,
            pattern
        );

    end = clock();

    double rabin_ms =
        benchmark_ms(
            start,
            end
        );


    start = clock();

    MatchResult automaton =
        finite_automaton_search(
            text,
            pattern
        );

    end = clock();

    double automaton_ms =
        benchmark_ms(
            start,
            end
        );


    start = clock();

    MatchResult kmp =
        kmp_search(
            text,
            pattern
        );

    end = clock();

    double kmp_ms =
        benchmark_ms(
            start,
            end
        );


    int correct =
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


    printf(
        "\n[STRING MATCHING - 100,000 CHARACTERS]\n"
    );

    printf(
        "%-24s %12.3f ms\n",
        "Naive",
        naive_ms
    );

    printf(
        "%-24s %12.3f ms\n",
        "Rabin-Karp",
        rabin_ms
    );

    printf(
        "%-24s %12.3f ms\n",
        "Finite Automaton",
        automaton_ms
    );

    printf(
        "%-24s %12.3f ms\n",
        "KMP",
        kmp_ms
    );

    printf(
        "%-24s %12s\n",
        "Correctness",
        correct ? "PASS" : "FAIL"
    );


    free(text);
}


static void fill_matrix(
    int size,
    int A[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    int B[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE]
)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            A[i][j] =
                (
                    i * size +
                    j +
                    1
                ) % 10;

            B[i][j] =
                (
                    (i + j + 2) *
                    2
                ) % 10;
        }
    }
}


static void run_complete_matrix(void)
{
    int A
        [MATRIX_MAX_SIZE]
        [MATRIX_MAX_SIZE] = {0};

    int B
        [MATRIX_MAX_SIZE]
        [MATRIX_MAX_SIZE] = {0};

    int classical
        [MATRIX_MAX_SIZE]
        [MATRIX_MAX_SIZE] = {0};

    int strassen
        [MATRIX_MAX_SIZE]
        [MATRIX_MAX_SIZE] = {0};


    int size = 8;

    fill_matrix(
        size,
        A,
        B
    );


    clock_t start =
        clock();

    classical_matrix_multiply(
        size,
        A,
        B,
        classical
    );

    clock_t end =
        clock();

    double classical_ms =
        benchmark_ms(
            start,
            end
        );


    start = clock();

    strassen_matrix_multiply(
        size,
        A,
        B,
        strassen
    );

    end = clock();

    double strassen_ms =
        benchmark_ms(
            start,
            end
        );


    int correct =
        matrices_equal(
            size,
            classical,
            strassen
        );


    printf(
        "\n[MATRIX MULTIPLICATION - 8x8]\n"
    );

    printf(
        "%-24s %12.6f ms\n",
        "Classical",
        classical_ms
    );

    printf(
        "%-24s %12.6f ms\n",
        "Strassen",
        strassen_ms
    );

    printf(
        "%-24s %12s\n",
        "Correctness",
        correct ? "PASS" : "FAIL"
    );
}


static int edge_total(
    const GraphEdge edges[],
    int count
)
{
    int total = 0;

    for (int i = 0; i < count; i++)
    {
        total +=
            edges[i].weight;
    }

    return total;
}


static void run_complete_graph(void)
{
    WeightedGraph graph;

    initialize_graph(
        &graph,
        6
    );

    add_undirected_edge(
        &graph,
        0,
        1,
        1
    );

    add_undirected_edge(
        &graph,
        1,
        2,
        1
    );

    add_undirected_edge(
        &graph,
        1,
        4,
        1
    );

    add_undirected_edge(
        &graph,
        0,
        3,
        4
    );

    add_undirected_edge(
        &graph,
        2,
        3,
        2
    );

    add_undirected_edge(
        &graph,
        4,
        3,
        3
    );

    add_undirected_edge(
        &graph,
        0,
        5,
        5
    );

    add_undirected_edge(
        &graph,
        3,
        5,
        2
    );


    int dijkstra_distance[
        GRAPH_MAX_VERTICES
    ];

    int dijkstra_previous[
        GRAPH_MAX_VERTICES
    ];

    int bellman_distance[
        GRAPH_MAX_VERTICES
    ];

    int bellman_previous[
        GRAPH_MAX_VERTICES
    ];


    clock_t start =
        clock();

    dijkstra(
        &graph,
        0,
        dijkstra_distance,
        dijkstra_previous
    );

    clock_t end =
        clock();

    double dijkstra_ms =
        benchmark_ms(
            start,
            end
        );


    start = clock();

    int bellman_valid =
        bellman_ford(
            &graph,
            0,
            bellman_distance,
            bellman_previous
        );

    end = clock();

    double bellman_ms =
        benchmark_ms(
            start,
            end
        );


    int shortest_correct =
        bellman_valid;

    for (
        int i = 0;
        i < graph.vertices;
        i++
    )
    {
        if (
            dijkstra_distance[i] !=
            bellman_distance[i]
        )
        {
            shortest_correct = 0;
        }
    }


    GraphEdge prim_result[
        GRAPH_MAX_VERTICES
    ];

    GraphEdge kruskal_result[
        GRAPH_MAX_VERTICES
    ];


    start = clock();

    int prim_count =
        prim_mst(
            &graph,
            prim_result
        );

    end = clock();

    double prim_ms =
        benchmark_ms(
            start,
            end
        );


    start = clock();

    int kruskal_count =
        kruskal_mst(
            &graph,
            kruskal_result
        );

    end = clock();

    double kruskal_ms =
        benchmark_ms(
            start,
            end
        );


    int mst_correct =
        prim_count ==
            graph.vertices - 1 &&
        kruskal_count ==
            graph.vertices - 1 &&
        edge_total(
            prim_result,
            prim_count
        ) ==
        edge_total(
            kruskal_result,
            kruskal_count
        );


    printf(
        "\n[GRAPH ALGORITHMS - 6 VERTICES]\n"
    );

    printf(
        "%-24s %12.6f ms\n",
        "Dijkstra",
        dijkstra_ms
    );

    printf(
        "%-24s %12.6f ms\n",
        "Bellman-Ford",
        bellman_ms
    );

    printf(
        "%-24s %12.6f ms\n",
        "Prim",
        prim_ms
    );

    printf(
        "%-24s %12.6f ms\n",
        "Kruskal",
        kruskal_ms
    );

    printf(
        "%-24s %12s\n",
        "Shortest paths",
        shortest_correct ?
            "PASS" :
            "FAIL"
    );

    printf(
        "%-24s %12s\n",
        "MST comparison",
        mst_correct ?
            "PASS" :
            "FAIL"
    );
}


void run_complete_benchmark_suite(void)
{
    printf("\n");
    printf(
        "====================================================================\n"
    );

    printf(
        "                    COMPLETE BENCHMARK SUITE\n"
    );

    printf(
        "====================================================================\n"
    );


    run_complete_sorting();

    run_complete_strings();

    run_complete_matrix();

    run_complete_graph();


    printf("\n");
    printf(
        "====================================================================\n"
    );

    printf(
        "Benchmark suite completed.\n"
    );

    printf(
        "All correctness checks should report PASS.\n"
    );

    printf(
        "====================================================================\n"
    );
}
#include <stdio.h>
#include <string.h>

#include "test_suite.h"

#include "transaction.h"
#include "sorting.h"
#include "searching.h"
#include "divide_conquer.h"
#include "matrix_algorithms.h"
#include "dynamic_programming.h"
#include "backtracking.h"
#include "graph_algorithms.h"
#include "string_matching.h"
#include "number_theory.h"
#include "greedy.h"
#include "branch_bound.h"
#include "network_flow.h"


static int tests_run = 0;
static int tests_passed = 0;


static void record_test(
    const char *name,
    int passed
)
{
    tests_run++;

    printf(
        "%-48s : %s\n",
        name,
        passed ? "PASS" : "FAIL"
    );

    if (passed)
    {
        tests_passed++;
    }
}


static int transactions_sorted(
    const Transaction data[],
    int count
)
{
    for (int i = 1; i < count; i++)
    {
        if (
            data[i - 1].amount >
            data[i].amount
        )
        {
            return 0;
        }
    }

    return 1;
}


static void test_sorting(void)
{
    Transaction merge_data[5] = {0};
    Transaction quick_data[5] = {0};

    double amounts[] = {
        500.0,
        100.0,
        900.0,
        250.0,
        50.0
    };

    for (int i = 0; i < 5; i++)
    {
        merge_data[i].amount =
            amounts[i];

        quick_data[i].amount =
            amounts[i];
    }

    merge_sort_transactions(
        merge_data,
        5
    );

    quick_sort_transactions(
        quick_data,
        5
    );

    record_test(
        "Merge Sort orders transaction amounts",
        transactions_sorted(
            merge_data,
            5
        )
    );

    record_test(
        "Quick Sort orders transaction amounts",
        transactions_sorted(
            quick_data,
            5
        )
    );

    int identical = 1;

    for (int i = 0; i < 5; i++)
    {
        if (
            merge_data[i].amount !=
            quick_data[i].amount
        )
        {
            identical = 0;
        }
    }

    record_test(
        "Merge and Quick produce identical ordering",
        identical
    );
}


static void test_binary_search(void)
{
    Transaction data[5] = {0};

    strcpy(
        data[0].transaction_id,
        "T0001"
    );

    strcpy(
        data[1].transaction_id,
        "T0002"
    );

    strcpy(
        data[2].transaction_id,
        "T0003"
    );

    strcpy(
        data[3].transaction_id,
        "T0004"
    );

    strcpy(
        data[4].transaction_id,
        "T0005"
    );


    int iterative =
        binary_search_iterative(
            data,
            5,
            "T0003"
        );

    int recursive =
        binary_search_recursive(
            data,
            5,
            "T0003"
        );


    record_test(
        "Iterative Binary Search finds known ID",
        iterative == 2
    );

    record_test(
        "Recursive Binary Search finds known ID",
        recursive == 2
    );


    record_test(
        "Binary Search rejects missing ID",
        binary_search_iterative(
            data,
            5,
            "T9999"
        ) == -1
    );
}


static void test_divide_conquer(void)
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

    MaxSubarrayResult result =
        maximum_subarray(
            values,
            7
        );

    record_test(
        "Maximum Subarray oracle sum = 25",
        result.sum == 25.0
    );


    record_test(
        "Fast Power oracle 2^10 = 1024",
        fast_power(
            2,
            10
        ) == 1024
    );


    int relationships[10][10] = {0};

    relationships[0][2] = 1;
    relationships[1][2] = 1;
    relationships[3][2] = 1;

    int celebrity =
        find_celebrity(
            relationships,
            4
        );

    record_test(
        "Celebrity oracle finds Person 2",
        celebrity == 2
    );
}


static void test_matrix(void)
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


    A[0][0] = 1;
    A[0][1] = 2;
    A[1][0] = 3;
    A[1][1] = 4;

    B[0][0] = 5;
    B[0][1] = 6;
    B[1][0] = 7;
    B[1][1] = 8;


    classical_matrix_multiply(
        2,
        A,
        B,
        classical
    );

    strassen_matrix_multiply(
        2,
        A,
        B,
        strassen
    );


    record_test(
        "Classical matrix known-value oracle",
        classical[0][0] == 19 &&
        classical[0][1] == 22 &&
        classical[1][0] == 43 &&
        classical[1][1] == 50
    );


    record_test(
        "Strassen equals Classical",
        matrices_equal(
            2,
            classical,
            strassen
        )
    );
}


static void test_dynamic_programming(void)
{
    InvestigationCase cases[] = {
        {1, 95, 4},
        {2, 60, 2},
        {3, 80, 3},
        {4, 30, 1},
        {5, 90, 5}
    };

    KnapsackResult knapsack =
        solve_zero_one_knapsack(
            cases,
            5,
            8
        );

    record_test(
        "0/1 Knapsack optimum risk = 205",
        knapsack.maximum_risk == 205
    );


    int dimensions[] = {
        10,
        30,
        5,
        60
    };

    record_test(
        "Matrix Chain optimum cost = 4500",
        matrix_chain_min_cost(
            dimensions,
            3
        ) == 4500
    );


    char lcs_result[
        MAX_SEQUENCE_LENGTH + 1
    ];

    int lcs_length =
        longest_common_subsequence(
            "ABCBDAB",
            "BDCABA",
            lcs_result
        );

    record_test(
        "LCS known length = 4",
        lcs_length == 4
    );


    int frequencies[] = {
        34,
        8,
        50
    };

    record_test(
        "Optimal BST minimum cost = 142",
        optimal_bst_cost(
            frequencies,
            3
        ) == 142
    );
}


static void test_backtracking(void)
{
    NQueensResult queens =
        solve_n_queens(4);

    record_test(
        "N-Queens N=4 has exactly 2 solutions",
        queens.solution_count == 2
    );


    int values[] = {
        3,
        34,
        4,
        12,
        5,
        2
    };

    SubsetResult subset =
        solve_subset_sum(
            values,
            6,
            9
        );

    record_test(
        "Subset Sum finds target 9",
        subset.found &&
        subset.sum == 9
    );


    SubsetResult missing =
        solve_subset_sum(
            values,
            6,
            30
        );

    record_test(
        "Subset Sum rejects impossible target 30",
        !missing.found
    );
}


static void test_graph(void)
{
    WeightedGraph graph;

    initialize_graph(
        &graph,
        4
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
        2
    );

    add_undirected_edge(
        &graph,
        0,
        2,
        5
    );

    add_undirected_edge(
        &graph,
        2,
        3,
        1
    );


    int dijkstra_distance[
        GRAPH_MAX_VERTICES
    ];

    int dijkstra_previous[
        GRAPH_MAX_VERTICES
    ];


    dijkstra(
        &graph,
        0,
        dijkstra_distance,
        dijkstra_previous
    );


    record_test(
        "Dijkstra shortest distance 0->3 = 4",
        dijkstra_distance[3] == 4
    );


    int bellman_distance[
        GRAPH_MAX_VERTICES
    ];

    int bellman_previous[
        GRAPH_MAX_VERTICES
    ];


    int valid =
        bellman_ford(
            &graph,
            0,
            bellman_distance,
            bellman_previous
        );


    record_test(
        "Bellman-Ford agrees with Dijkstra",
        valid &&
        bellman_distance[3] ==
        dijkstra_distance[3]
    );


    int all_pairs
        [GRAPH_MAX_VERTICES]
        [GRAPH_MAX_VERTICES];

    floyd_warshall(
        &graph,
        all_pairs
    );

    record_test(
        "Floyd-Warshall distance 0->3 = 4",
        all_pairs[0][3] == 4
    );


    GraphEdge prim_edges[
        GRAPH_MAX_VERTICES
    ];

    GraphEdge kruskal_edges[
        GRAPH_MAX_VERTICES
    ];

    int prim_count =
        prim_mst(
            &graph,
            prim_edges
        );

    int kruskal_count =
        kruskal_mst(
            &graph,
            kruskal_edges
        );


    int prim_cost = 0;
    int kruskal_cost = 0;

    for (int i = 0; i < prim_count; i++)
    {
        prim_cost +=
            prim_edges[i].weight;
    }

    for (int i = 0; i < kruskal_count; i++)
    {
        kruskal_cost +=
            kruskal_edges[i].weight;
    }


    record_test(
        "Prim and Kruskal MST costs agree",
        prim_count == 3 &&
        kruskal_count == 3 &&
        prim_cost == kruskal_cost
    );
}


static void test_string_matching(void)
{
    const char *text =
        "AAAAAAAAAA";

    const char *pattern =
        "AAA";


    MatchResult naive =
        naive_pattern_search(
            text,
            pattern
        );

    MatchResult rabin =
        rabin_karp_search(
            text,
            pattern
        );

    MatchResult automaton =
        finite_automaton_search(
            text,
            pattern
        );

    MatchResult kmp =
        kmp_search(
            text,
            pattern
        );


    record_test(
        "Overlapping string matches count = 8",
        naive.count == 8
    );


    record_test(
        "All four string matchers agree",
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
        )
    );


    MatchResult missing =
        kmp_search(
            "TRANSFER PAYMENT ATM",
            "CRYPTO"
        );

    record_test(
        "String matcher handles no-match case",
        missing.count == 0
    );
}


static void test_crt(void)
{
    long long remainders[] = {
        2,
        3,
        2
    };

    long long moduli[] = {
        3,
        5,
        7
    };


    CRTResult result =
        chinese_remainder_theorem(
            remainders,
            moduli,
            3
        );


    record_test(
        "CRT oracle solution = 23",
        result.valid &&
        result.solution == 23 &&
        result.modulus_product == 105
    );
}
static void test_greedy(void)
{
    Activity activities[] = {
        {1, 9, 10},
        {2, 9, 11},
        {3, 10, 11},
        {4, 10, 12},
        {5, 11, 12},
        {6, 12, 13}
    };

    Activity selected[MAX_ACTIVITIES];

    int count =
        sizeof(activities) /
        sizeof(activities[0]);

    int selected_count =
        activity_selection(
            activities,
            count,
            selected
        );

    record_test(
        "Activity Selection optimum count = 4",
        selected_count == 4
    );


    Activity intervals[] = {
        {1, 9, 11},
        {2, 9, 10},
        {3, 10, 12},
        {4, 11, 13},
        {5, 12, 14}
    };

    IntervalAssignment assignments[
        MAX_ACTIVITIES
    ];

    int investigators =
        interval_partitioning(
            intervals,
            5,
            assignments
        );

    record_test(
        "Interval Partitioning minimum resources = 2",
        investigators == 2
    );
}
static void test_tsp(void)
{
    int graph
        [TSP_MAX_VERTICES]
        [TSP_MAX_VERTICES] = {0};

    int costs[4][4] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            graph[i][j] =
                costs[i][j];
        }
    }

    TSPResult result =
        solve_bounded_tsp(
            4,
            graph
        );

    record_test(
        "Bounded TSP optimum route cost = 80",
        result.minimum_cost == 80
    );

    record_test(
        "TSP tour starts and ends at vertex 0",
        result.path_length == 5 &&
        result.path[0] == 0 &&
        result.path[
            result.path_length - 1
        ] == 0
    );
}
static void test_branch_bound(void)
{
    BBItem items[] = {
        {1, 2, 40},
        {2, 3, 50},
        {3, 4, 65},
        {4, 5, 75}
    };

    int count =
        sizeof(items) /
        sizeof(items[0]);

    int capacity = 7;


    BBResult fifo =
        branch_bound_fifo(
            items,
            count,
            capacity
        );

    BBResult lifo =
        branch_bound_lifo(
            items,
            count,
            capacity
        );

    BBResult least =
        branch_bound_least_cost(
            items,
            count,
            capacity
        );


    record_test(
        "FIFO Branch-and-Bound optimum = 115",
        fifo.maximum_value == 115
    );

    record_test(
        "LIFO Branch-and-Bound optimum = 115",
        lifo.maximum_value == 115
    );

    record_test(
        "Least-Cost Branch-and-Bound optimum = 115",
        least.maximum_value == 115
    );

    record_test(
        "All B&B strategies agree",
        fifo.maximum_value ==
            lifo.maximum_value &&
        fifo.maximum_value ==
            least.maximum_value
    );
}
static void test_max_flow(void)
{
    int capacity
        [FLOW_MAX_VERTICES]
        [FLOW_MAX_VERTICES] = {0};

    int vertex_count = 5;

    capacity[0][1] = 10;
    capacity[0][2] = 8;

    capacity[1][3] = 5;
    capacity[1][4] = 5;

    capacity[2][3] = 6;
    capacity[2][4] = 4;

    capacity[3][4] = 8;


    int maximum_flow =
        ford_fulkerson(
            vertex_count,
            capacity,
            0,
            4
        );


    record_test(
        "Ford-Fulkerson maximum flow = 17",
        maximum_flow == 17
    );
}
static void test_bipartite_matching(void)
{
    int compatibility
        [MATCH_MAX_LEFT]
        [MATCH_MAX_RIGHT] = {0};

    compatibility[0][0] = 1;
    compatibility[0][1] = 1;

    compatibility[1][1] = 1;
    compatibility[1][2] = 1;

    compatibility[2][0] = 1;
    compatibility[2][2] = 1;

    compatibility[3][2] = 1;
    compatibility[3][3] = 1;


    int matches[
        MATCH_MAX_RIGHT
    ];


    int maximum_matches =
        maximum_bipartite_matching(
            4,
            4,
            compatibility,
            matches
        );


    record_test(
        "Maximum Bipartite Matching size = 4",
        maximum_matches == 4
    );
}
static void test_edge_cases(void)
{
    /*
     * Empty sorting input must not crash.
     */
    Transaction dummy[1] = {0};

    merge_sort_transactions(
        dummy,
        0
    );

    quick_sort_transactions(
        dummy,
        0
    );

    record_test(
        "Sorting handles empty input",
        1
    );


    /*
     * Empty binary search.
     */
    record_test(
        "Binary Search handles empty input",
        binary_search_iterative(
            dummy,
            0,
            "T0001"
        ) == -1
    );


    /*
     * Fast Power exponent zero.
     */
    record_test(
        "Fast Power exponent zero returns 1",
        fast_power(
            999,
            0
        ) == 1
    );


    /*
     * N-Queens impossible board.
     */
    NQueensResult queens =
        solve_n_queens(3);

    record_test(
        "N-Queens N=3 has no solution",
        queens.solution_count == 0
    );


    /*
     * Empty pattern should not produce
     * matches under our interface contract.
     */
    MatchResult empty_pattern =
        kmp_search(
            "ABCDEF",
            ""
        );

    record_test(
        "KMP handles empty pattern",
        empty_pattern.count == 0
    );


    /*
     * Pattern longer than text.
     */
    MatchResult long_pattern =
        naive_pattern_search(
            "ABC",
            "ABCDEFG"
        );

    record_test(
        "Pattern longer than text returns no match",
        long_pattern.count == 0
    );


    /*
     * Invalid CRT:
     * 4 and 6 are not coprime.
     */
    long long remainders[] = {
        1,
        2
    };

    long long moduli[] = {
        4,
        6
    };

    CRTResult crt =
        chinese_remainder_theorem(
            remainders,
            moduli,
            2
        );

    record_test(
        "CRT rejects non-coprime moduli",
        !crt.valid
    );


    /*
     * Invalid Knapsack capacity.
     */
    InvestigationCase cases[] = {
        {1, 10, 1}
    };

    KnapsackResult invalid_knapsack =
        solve_zero_one_knapsack(
            cases,
            1,
            0
        );

    record_test(
        "Knapsack rejects zero capacity",
        invalid_knapsack.maximum_risk == 0 &&
        invalid_knapsack.selected_count == 0
    );
}
void run_test_suite(void)
{
    tests_run = 0;
    tests_passed = 0;


    printf("\n");
    printf("====================================================================\n");
    printf("                     AUTOMATED TEST SUITE\n");
    printf("====================================================================\n");


    printf("\n[SORTING]\n");
    test_sorting();

    printf("\n[SEARCHING]\n");
    test_binary_search();

    printf("\n[DIVIDE AND CONQUER]\n");
    test_divide_conquer();
    printf("\n[GREEDY]\n");
test_greedy();

printf("\n[TSP]\n");
test_tsp();

    printf("\n[MATRIX]\n");
    test_matrix();

    printf("\n[DYNAMIC PROGRAMMING]\n");
    test_dynamic_programming();

    printf("\n[BACKTRACKING]\n");
    test_backtracking();
    printf("\n[BRANCH AND BOUND]\n");
test_branch_bound();


    printf("\n[GRAPH]\n");
    test_graph();
    printf("\n[NETWORK FLOW]\n");
test_max_flow();

printf("\n[BIPARTITE MATCHING]\n");
test_bipartite_matching();

    printf("\n[STRING MATCHING]\n");
    test_string_matching();

    printf("\n[NUMBER THEORY]\n");
    test_crt();
    printf("\n[EDGE AND INVALID INPUTS]\n");
test_edge_cases();


    printf("\n");
    printf("====================================================================\n");
    printf("                         TEST SUMMARY\n");
    printf("====================================================================\n");

    printf(
        "Tests Run    : %d\n",
        tests_run
    );

    printf(
        "Tests Passed : %d\n",
        tests_passed
    );

    printf(
        "Tests Failed : %d\n",
        tests_run - tests_passed
    );


    if (tests_run == tests_passed)
    {
        printf(
            "\nOVERALL RESULT: PASS\n"
        );
    }
    else
    {
        printf(
            "\nOVERALL RESULT: FAIL\n"
        );
    }

    printf(
        "====================================================================\n"
    );
}
#include <stdio.h>
#include <stddef.h>
#include "algorithm_lab_menu.h"

#include "divide_conquer.h"
#include "matrix_algorithms.h"
#include "greedy.h"
#include "dynamic_programming.h"
#include "backtracking.h"
#include "branch_bound.h"
#include "network_flow.h"
#include "number_theory.h"
static void print_bb_result(
    const char *name,
    const BBResult *result
)
{
    printf("\n%s\n", name);
    printf("----------------------------------------\n");

    printf(
        "Maximum Risk Value : %d\n",
        result->maximum_value
    );

    printf(
        "Total Time Used    : %d\n",
        result->total_cost
    );

    printf(
        "Selected Cases     : "
    );

    for (
        int i = 0;
        i < result->selected_count;
        i++
    )
    {
        printf(
            "F%d",
            result->selected_ids[i]
        );

        if (
            i < result->selected_count - 1
        )
        {
            printf(", ");
        }
    }

    printf("\n");

    printf(
        "Nodes Explored     : %d\n",
        result->nodes_explored
    );
}
void run_algorithm_lab_menu(void)
{
                int algorithm_choice;

                printf("\n");
                printf("============================================================\n");
                printf("                DAA ALGORITHM LABORATORY\n");
                printf("============================================================\n");
                printf("1. Maximum Subarray\n");
                printf("2. Fast Power\n");
                printf("3. Celebrity Problem\n");
                printf("4. Classical vs Strassen "
                    "Matrix Multiplication\n"
                );
                printf("5. Activity Selection\n");
                printf("6. Interval Partitioning\n");
                printf("7. Huffman Coding\n");
                printf("8. Matrix Chain Multiplication\n");
printf("9. Longest Common Subsequence\n");
printf("10. Optimal Binary Search Tree\n");
printf("11. Bounded TSP (Investigation Route)\n");
printf("12. N-Queens Backtracking\n");
printf("13. Subset Sum Backtracking\n");
printf("14. FIFO Branch and Bound\n");
printf("15. LIFO Branch and Bound\n");
printf("16. Least-Cost Branch and Bound\n");
printf("17. Compare All Branch and Bound Strategies\n");
printf("18. Ford-Fulkerson Maximum Flow\n");
printf("19. Maximum Bipartite Matching\n");
printf("20. Chinese Remainder Theorem\n");
printf("21. Fractional Knapsack - Investigation Allocation\n");
printf("22. 0/1 Knapsack - Backtracking\n");
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

                    return;
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
                        return;
                    }

                    printf("Enter exponent: ");

                    if (scanf("%u", &exponent) != 1)
                    {
                        printf("Invalid exponent.\n");
                        return;
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

    int size_choice;
    int size;
    int input_choice;

    int i;
    int j;

    printf("\n");
    printf("============================================================\n");
    printf("             MATRIX MULTIPLICATION LAB\n");
    printf("============================================================\n");

    printf("1. 2 x 2 Matrix\n");
    printf("2. 4 x 4 Matrix\n");
    printf("3. 8 x 8 Matrix\n");
    printf("0. Back\n");

    printf("Select matrix size: ");

    if (scanf("%d", &size_choice) != 1)
    {
        printf("Invalid input.\n");

        while (getchar() != '\n')
        {
        }

     return;
    }

    if (size_choice == 0)
    {
        return;
    }

    if (size_choice == 1)
    {
        size = 2;
    }
    else if (size_choice == 2)
    {
        size = 4;
    }
    else if (size_choice == 3)
    {
        size = 8;
    }
    else
    {
        printf("Invalid matrix size.\n");
        return;
    }

    printf("\nInput Method\n");
    printf("1. Enter matrix values manually\n");
    printf("2. Generate test matrices automatically\n");
    printf("Select input method: ");

    if (scanf("%d", &input_choice) != 1)
    {
        printf("Invalid input.\n");

        while (getchar() != '\n')
        {
        }

     return;
    }


    /*
     * Manual input
     */
    if (input_choice == 1)
    {
        printf(
            "\nEnter values for Matrix A (%d x %d):\n",
            size,
            size
        );

        for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
            {
                printf(
                    "A[%d][%d] = ",
                    i,
                    j
                );

                scanf(
                    "%d",
                    &A[i][j]
                );
            }
        }

        printf(
            "\nEnter values for Matrix B (%d x %d):\n",
            size,
            size
        );

        for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
            {
                printf(
                    "B[%d][%d] = ",
                    i,
                    j
                );

                scanf(
                    "%d",
                    &B[i][j]
                );
            }
        }
    }

    /*
     * Automatic deterministic test data.
     *
     * Deterministic values are useful because
     * the same input is supplied to both
     * algorithms.
     */
    else if (input_choice == 2)
    {
        for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
            {
                A[i][j] =
                    (i * size + j + 1) % 10;

                B[i][j] =
                    ((i + j + 2) * 2) % 10;
            }
        }

        printf(
            "\nTest matrices generated successfully.\n"
        );
    }
    else
    {
        printf("Invalid input method.\n");
        return;
    }


    /*
     * Run both algorithms on exactly
     * the same matrices.
     */
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
    print_matrix(
        size,
        A
    );

    printf("\nMatrix B:\n");
    print_matrix(
        size,
        B
    );

    printf(
        "\nClassical Multiplication Result:\n"
    );

    print_matrix(
        size,
        classical_result
    );

    printf(
        "\nRecursive Strassen Result:\n"
    );

    print_matrix(
        size,
        strassen_result
    );


    printf("\nCorrectness Check: ");

    if (
        matrices_equal(
            size,
            classical_result,
            strassen_result
        )
    )
    {
        printf("PASS\n");
        printf(
            "Both algorithms produced "
            "identical matrices.\n"
        );
    }
    else
    {
        printf("FAIL\n");
        printf(
            "Results do not match.\n"
        );
    }


    printf("\nComplexity Comparison\n");
    printf("----------------------------------------\n");
    printf("Classical : O(n^3)\n");
    printf("Strassen  : O(n^log2(7)) ~ O(n^2.807)\n");
}
else if (algorithm_choice == 5)
{
    Activity activities[] = {
        {1, 9, 10},
        {2, 9, 11},
        {3, 10, 11},
        {4, 10, 12},
        {5, 11, 12},
        {6, 12, 13}
    };

    int count =
        sizeof(activities) /
        sizeof(activities[0]);

    Activity selected[MAX_ACTIVITIES];

    int selected_count =
        activity_selection(
            activities,
            count,
            selected
        );

    printf("\nSelected Investigation Cases\n");
    printf("----------------------------------------\n");
    printf("Case     Start     Finish\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < selected_count; i++)
    {
        printf(
            "%-8d %-9d %d\n",
            selected[i].id,
            selected[i].start,
            selected[i].finish
        );
    }

    printf("----------------------------------------\n");

    printf(
        "Maximum non-overlapping cases: %d\n",
        selected_count
    );
}
else if (algorithm_choice == 6)
{
    Activity activities[] = {
        {1, 9, 11},
        {2, 9, 10},
        {3, 10, 12},
        {4, 11, 13},
        {5, 12, 14}
    };

    int count =
        sizeof(activities) /
        sizeof(activities[0]);

    IntervalAssignment assignments[
        MAX_ACTIVITIES
    ];

    int investigators =
        interval_partitioning(
            activities,
            count,
            assignments
        );

    printf("\nInvestigation Assignment\n");
    printf("----------------------------------------\n");
    printf("Case       Investigator\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        printf(
            "%-10d %d\n",
            assignments[i].activity_id,
            assignments[i].resource_id
        );
    }

    printf("----------------------------------------\n");

    printf(
        "Minimum investigators required: %d\n",
        investigators
    );
}
else if (algorithm_choice == 7)
{
    char text[256];

    printf("\nEnter banking/fraud log text:\n");

    /*
     * Remove newline left by previous scanf.
     */
    int ch;

    while (
        (ch = getchar()) != '\n' &&
        ch != EOF
    )
    {
    }

    if (
        fgets(
            text,
            sizeof(text),
            stdin
        ) != NULL
    )
    {
        /*
         * Remove trailing newline.
         */
        for (int i = 0; text[i] != '\0'; i++)
        {
            if (text[i] == '\n')
            {
                text[i] = '\0';
                break;
            }
        }

        run_huffman_demo(text);
    }
}
else if (algorithm_choice == 8)
{
    int dimensions[] = {
        10,
        30,
        5,
        60
    };

    int matrix_count = 3;

    printf("\nMatrix Chain\n");
    printf("----------------------------------------\n");
    printf("A1 = 10 x 30\n");
    printf("A2 = 30 x 5\n");
    printf("A3 = 5 x 60\n");

    long long minimum_cost =
        matrix_chain_min_cost(
            dimensions,
            matrix_count
        );

    printf(
        "\nMinimum scalar multiplications: %lld\n",
        minimum_cost
    );
}
else if (algorithm_choice == 9)
{
    char first[
        MAX_SEQUENCE_LENGTH + 1
    ];

    char second[
        MAX_SEQUENCE_LENGTH + 1
    ];

    char result[
        MAX_SEQUENCE_LENGTH + 1
    ];

    printf(
        "\nEnter first event sequence "
        "(no spaces): "
    );

    scanf(
        "%100s",
        first
    );

    printf(
        "Enter second event sequence "
        "(no spaces): "
    );

    scanf(
        "%100s",
        second
    );

    int length =
        longest_common_subsequence(
            first,
            second,
            result
        );

    printf("\nLCS Result\n");
    printf("----------------------------------------\n");

    printf(
        "Sequence 1 : %s\n",
        first
    );

    printf(
        "Sequence 2 : %s\n",
        second
    );

    printf(
        "LCS        : %s\n",
        result
    );

    printf(
        "LCS Length : %d\n",
        length
    );
}
else if (algorithm_choice == 10)
{
    int frequencies[] = {
        34,
        8,
        50
    };

    int key_count = 3;

    printf("\nOptimal BST Input\n");
    printf("----------------------------------------\n");

    printf("Account Index K1 frequency: 34\n");
    printf("Account Index K2 frequency: 8\n");
    printf("Account Index K3 frequency: 50\n");

    int cost =
        optimal_bst_cost(
            frequencies,
            key_count
        );

    printf(
        "\nMinimum weighted search cost: %d\n",
        cost
    );
}
else if (algorithm_choice == 11)
{
    int graph
        [TSP_MAX_VERTICES]
        [TSP_MAX_VERTICES] = {0};

    /*
     * Four investigation locations:
     *
     * 0 = Bank Branch
     * 1 = Merchant Site
     * 2 = ATM Location
     * 3 = Investigation Office
     */

    int vertex_count = 4;

    const char *location_names[] = {
        "Bank Branch",
        "Merchant Site",
        "ATM Location",
        "Investigation Office"
    };

    int costs[4][4] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    for (int i = 0; i < vertex_count; i++)
    {
        for (int j = 0; j < vertex_count; j++)
        {
            graph[i][j] = costs[i][j];
        }
    }

    printf("\n");
    printf("============================================================\n");
    printf("             BOUNDED TSP INVESTIGATION ROUTE\n");
    printf("============================================================\n");

    printf("Locations:\n");

    for (int i = 0; i < vertex_count; i++)
    {
        printf(
            "%d = %s\n",
            i,
            location_names[i]
        );
    }

    printf("\nTravel / Evidence Cost Matrix\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < vertex_count; i++)
    {
        for (int j = 0; j < vertex_count; j++)
        {
            printf(
                "%6d",
                graph[i][j]
            );
        }

        printf("\n");
    }

    TSPResult result =
        solve_bounded_tsp(
            vertex_count,
            graph
        );

    if (result.minimum_cost >= TSP_INF)
    {
        printf(
            "\nNo complete investigation route exists.\n"
        );
    }
    else
    {
        printf(
            "\nMinimum Route Cost: %d\n",
            result.minimum_cost
        );

        printf("Optimal Route: ");

        for (
            int i = 0;
            i < result.path_length;
            i++
        )
        {
            printf(
                "%s",
                location_names[result.path[i]]
            );

            if (i < result.path_length - 1)
            {
                printf(" -> ");
            }
        }

        printf("\n");
    }

    printf("\nComplexity\n");
    printf("Time  : O(n^2 * 2^n)\n");
    printf("Space : O(n * 2^n)\n");
    printf(
        "Bound  : maximum %d vertices\n",
        TSP_MAX_VERTICES
    );
}
else if (algorithm_choice == 12)
{
    int board_size;

    printf("\n");
    printf("============================================\n");
    printf("              N-QUEENS PROBLEM\n");
    printf("============================================\n");

    printf(
        "Enter board size "
        "(1-%d): ",
        NQUEENS_MAX_SIZE
    );

    if (
        scanf(
            "%d",
            &board_size
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
        board_size <= 0 ||
        board_size >
        NQUEENS_MAX_SIZE
    )
    {
        printf(
            "Invalid board size.\n"
        );

        return;
    }

    NQueensResult result =
        solve_n_queens(
            board_size
        );

    print_n_queens_solution(
        &result
    );

    printf("\nComplexity\n");
    printf(
        "Worst-case search is "
        "exponential / combinatorial.\n"
    );
}
else if (algorithm_choice == 13)
{
    int values[] = {
        3,
        34,
        4,
        12,
        5,
        2
    };

    int count =
        sizeof(values) /
        sizeof(values[0]);

    int target;

    printf("\n");
    printf("============================================\n");
    printf("              SUBSET SUM\n");
    printf("============================================\n");

    printf("Available values: ");

    for (int i = 0;
         i < count;
         i++)
    {
        printf(
            "%d ",
            values[i]
        );
    }

    printf("\n");

    printf(
        "Enter target sum: "
    );

    if (
        scanf(
            "%d",
            &target
        ) != 1
    )
    {
        printf("Invalid input.\n");

        while (getchar() != '\n')
        {
        }

        return;
    }

    SubsetResult result =
        solve_subset_sum(
            values,
            count,
            target
        );

    if (result.found)
    {
        printf(
            "\nSubset found: "
        );

        for (
            int i = 0;
            i < result.selected_count;
            i++
        )
        {
            printf(
                "%d",
                result.selected[i]
            );

            if (
                i <
                result.selected_count - 1
            )
            {
                printf(" + ");
            }
        }

        printf(
            " = %d\n",
            result.sum
        );
    }
    else
    {
        printf(
            "\nNo subset produces "
            "target %d.\n",
            target
        );
    }

    printf(
        "Worst-case complexity: O(2^n)\n"
    );
}
else if (
    algorithm_choice >= 14 &&
    algorithm_choice <= 17
)
{
    BBItem items[] = {
        {1, 2, 40},
        {2, 3, 50},
        {3, 4, 65},
        {4, 5, 75}
    };

    int item_count =
        sizeof(items) /
        sizeof(items[0]);

    int capacity = 7;

    printf("\n");
    printf("============================================================\n");
    printf("          BRANCH AND BOUND CASE SELECTION\n");
    printf("============================================================\n");

    printf(
        "%-8s %-12s %-12s\n",
        "CASE",
        "TIME",
        "RISK"
    );

    printf(
        "----------------------------------------\n"
    );

    for (int i = 0; i < item_count; i++)
    {
        printf(
            "F%-7d %-12d %-12d\n",
            items[i].id,
            items[i].cost,
            items[i].value
        );
    }

    printf(
        "----------------------------------------\n"
    );

    printf(
        "Available investigation time: %d\n",
        capacity
    );


    if (algorithm_choice == 14)
    {
        BBResult result =
            branch_bound_fifo(
                items,
                item_count,
                capacity
            );

        print_bb_result(
            "FIFO Branch and Bound",
            &result
        );
    }

    else if (algorithm_choice == 15)
    {
        BBResult result =
            branch_bound_lifo(
                items,
                item_count,
                capacity
            );

        print_bb_result(
            "LIFO Branch and Bound",
            &result
        );
    }

    else if (algorithm_choice == 16)
    {
        BBResult result =
            branch_bound_least_cost(
                items,
                item_count,
                capacity
            );

        print_bb_result(
            "Least-Cost / Best-Bound",
            &result
        );
    }

    else
    {
        BBResult fifo =
            branch_bound_fifo(
                items,
                item_count,
                capacity
            );

        BBResult lifo =
            branch_bound_lifo(
                items,
                item_count,
                capacity
            );

        BBResult least_cost =
            branch_bound_least_cost(
                items,
                item_count,
                capacity
            );

        print_bb_result(
            "FIFO Branch and Bound",
            &fifo
        );

        print_bb_result(
            "LIFO Branch and Bound",
            &lifo
        );

        print_bb_result(
            "Least-Cost / Best-Bound",
            &least_cost
        );


        printf("\n");
        printf("============================================================\n");
        printf("             STRATEGY COMPARISON\n");
        printf("============================================================\n");

        printf(
            "%-20s %-12s %-12s\n",
            "STRATEGY",
            "BEST RISK",
            "NODES"
        );

        printf(
            "%-20s %-12d %-12d\n",
            "FIFO",
            fifo.maximum_value,
            fifo.nodes_explored
        );

        printf(
            "%-20s %-12d %-12d\n",
            "LIFO",
            lifo.maximum_value,
            lifo.nodes_explored
        );

        printf(
            "%-20s %-12d %-12d\n",
            "Least-Cost",
            least_cost.maximum_value,
            least_cost.nodes_explored
        );


        if (
            fifo.maximum_value ==
            lifo.maximum_value &&
            fifo.maximum_value ==
            least_cost.maximum_value
        )
        {
            printf(
                "\nCorrectness Check: PASS\n"
            );

            printf(
                "All strategies found the "
                "same optimal value.\n"
            );
        }
        else
        {
            printf(
                "\nCorrectness Check: FAIL\n"
            );
        }
    }
}
else if (algorithm_choice == 18)
{
    int capacity
        [FLOW_MAX_VERTICES]
        [FLOW_MAX_VERTICES] = {0};

    /*
     * Investigation capacity network:
     *
     * 0 = Fraud Alerts
     * 1 = Team A
     * 2 = Team B
     * 3 = Review Unit
     * 4 = Completed Cases
     */

    int vertex_count = 5;

    capacity[0][1] = 10;
    capacity[0][2] = 8;

    capacity[1][3] = 5;
    capacity[1][4] = 5;

    capacity[2][3] = 6;
    capacity[2][4] = 4;

    capacity[3][4] = 8;


    printf("\n");
    printf("============================================================\n");
    printf("          INVESTIGATION CAPACITY NETWORK\n");
    printf("============================================================\n");

    printf("Source          : Fraud Alerts\n");
    printf("Intermediate    : Team A, Team B, Review Unit\n");
    printf("Sink            : Completed Cases\n");


    int maximum_flow =
        ford_fulkerson(
            vertex_count,
            capacity,
            0,
            4
        );


    printf(
        "\nMaximum investigation flow: %d cases\n",
        maximum_flow
    );

    printf(
        "\nInterpretation:\n"
    );

    printf(
        "At most %d cases can pass through "
        "the current investigation capacity "
        "network simultaneously.\n",
        maximum_flow
    );
}
else if (algorithm_choice == 19)
{
    int compatibility
        [MATCH_MAX_LEFT]
        [MATCH_MAX_RIGHT] = {0};

    /*
     * Four fraud cases.
     */
    int case_count = 4;

    /*
     * Four investigators.
     */
    int investigator_count = 4;


    const char *case_names[] = {
        "Fraud Case F1",
        "Fraud Case F2",
        "Fraud Case F3",
        "Fraud Case F4"
    };

    const char *investigator_names[] = {
        "Analyst A",
        "Analyst B",
        "Analyst C",
        "Analyst D"
    };


    /*
     * Compatibility matrix:
     *
     *          A B C D
     * F1       1 1 0 0
     * F2       0 1 1 0
     * F3       1 0 1 0
     * F4       0 0 1 1
     */

    compatibility[0][0] = 1;
    compatibility[0][1] = 1;

    compatibility[1][1] = 1;
    compatibility[1][2] = 1;

    compatibility[2][0] = 1;
    compatibility[2][2] = 1;

    compatibility[3][2] = 1;
    compatibility[3][3] = 1;


    int right_matches[
        MATCH_MAX_RIGHT
    ];


    int maximum_matches =
        maximum_bipartite_matching(
            case_count,
            investigator_count,
            compatibility,
            right_matches
        );


    printf("\n");
    printf("============================================================\n");
    printf("           INVESTIGATOR CASE ASSIGNMENT\n");
    printf("============================================================\n");

    for (
        int investigator = 0;
        investigator < investigator_count;
        investigator++
    )
    {
        if (
            right_matches[investigator] != -1
        )
        {
            int case_index =
                right_matches[investigator];

            printf(
                "%s -> %s\n",
                case_names[case_index],
                investigator_names[investigator]
            );
        }
        else
        {
            printf(
                "%s -> Unassigned\n",
                investigator_names[investigator]
            );
        }
    }


    printf(
        "------------------------------------------------------------\n"
    );

    printf(
        "Maximum cases assigned: %d\n",
        maximum_matches
    );
}
else if (algorithm_choice == 20)
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

    int count = 3;

    printf("\n");
    printf("============================================================\n");
    printf("       DISTRIBUTED TRANSACTION ID RECONSTRUCTION\n");
printf("============================================================\n");

printf(
    "Reconstructing a transaction batch identifier\n"
    "from residues stored by independent banking nodes.\n\n"
);
printf("Node residues:\n");

    for (int i = 0; i < count; i++)
    {
        printf(
            "x = %lld (mod %lld)\n",
            remainders[i],
            moduli[i]
        );
    }


    CRTResult result =
        chinese_remainder_theorem(
            remainders,
            moduli,
            count
        );


    if (result.valid)
    {
        printf(
            "\nSmallest non-negative solution: %lld\n",
            result.solution
        );

        printf(
            "General solution: x = %lld (mod %lld)\n",
            result.solution,
            result.modulus_product
        );
         printf("\nInterpretation:\n");

    printf(
        "Transaction batch ID %lld satisfies "
        "all banking-node residues.\n",
        result.solution
    );

    printf(
        "The reconstructed identifier is unique "
        "modulo %lld.\n",
        result.modulus_product
    );

    printf(
        "This demonstrates modular identifier "
        "reconstruction across distributed "
        "financial-processing nodes.\n"
    );
    }
    else
    {
        printf(
            "\nCRT could not solve "
            "the supplied system.\n"
        );

        printf(
            "This implementation requires "
            "pairwise coprime moduli.\n"
        );
    }
}
else if (algorithm_choice == 21)
{
    FractionalItem cases[] = {
        {1, 95.0, 4.0},
        {2, 60.0, 2.0},
        {3, 80.0, 3.0},
        {4, 30.0, 1.0},
        {5, 90.0, 5.0}
    };

    int case_count =
        sizeof(cases) /
        sizeof(cases[0]);

    double available_hours;


    printf("\n");
    printf("============================================================\n");
    printf("       FRACTIONAL INVESTIGATION RESOURCE ALLOCATION\n");
    printf("============================================================\n");

    printf(
        "%-8s %-12s %-12s %-12s\n",
        "CASE",
        "RISK",
        "HOURS",
        "RISK/HOUR"
    );

    printf(
        "------------------------------------------------------------\n"
    );


    for (int i = 0; i < case_count; i++)
    {
        printf(
            "F%-7d %-12.2f %-12.2f %-12.2f\n",
            cases[i].id,
            cases[i].risk_value,
            cases[i].investigation_time,
            cases[i].risk_value /
                cases[i].investigation_time
        );
    }


    printf(
        "------------------------------------------------------------\n"
    );

    printf(
        "Enter available analyst hours: "
    );


    if (
        scanf(
            "%lf",
            &available_hours
        ) != 1
    )
    {
        printf(
            "Invalid investigation capacity.\n"
        );

        while (getchar() != '\n')
        {
        }

        return;
    }


    if (available_hours <= 0.0)
    {
        printf(
            "Available hours must be positive.\n"
        );

        return;
    }


    FractionalKnapsackResult result =
        fractional_knapsack(
            cases,
            case_count,
            available_hours
        );


    printf("\n");
    printf("============================================================\n");
    printf("              GREEDY ALLOCATION RESULT\n");
    printf("============================================================\n");

    printf(
        "%-8s %-12s %-15s %-15s\n",
        "CASE",
        "FRACTION",
        "HOURS USED",
        "RISK COVERED"
    );


    for (
        int i = 0;
        i < result.selected_count;
        i++
    )
    {
        printf(
            "F%-7d %-12.2f %-15.2f %-15.2f\n",
            result.selected[i].id,
            result.selected[i].fraction,
            result.selected[i].time_used,
            result.selected[i].risk_obtained
        );
    }


    printf(
        "------------------------------------------------------------\n"
    );

    printf(
        "Available Hours       : %.2f\n",
        available_hours
    );

    printf(
        "Hours Allocated       : %.2f\n",
        result.total_time
    );

    printf(
        "Maximum Risk Coverage : %.2f\n",
        result.maximum_risk
    );


    printf("\nGreedy Strategy\n");

    printf(
        "Cases are prioritized by decreasing "
        "risk-per-investigation-hour ratio.\n"
    );

    printf(
        "Partial allocation of the final case "
        "is permitted.\n"
    );

    printf("\nComplexity\n");

    printf(
        "Ranking in this implementation : O(n^2)\n"
    );

    printf(
        "Greedy allocation              : O(n)\n"
    );

    printf(
        "Auxiliary space                : O(n)\n"
    );
}
else if (algorithm_choice == 22)
{
    BacktrackingKnapsackItem items[] = {
        {1, 95, 4},
        {2, 60, 2},
        {3, 80, 3},
        {4, 30, 1},
        {5, 90, 5}
    };


    int item_count =
        sizeof(items) /
        sizeof(items[0]);


    int capacity;


    printf("\n");
    printf("============================================================\n");
    printf("          0/1 KNAPSACK USING BACKTRACKING\n");
    printf("============================================================\n");

    printf(
        "%-8s %-12s %-12s\n",
        "CASE",
        "RISK",
        "HOURS"
    );

    printf(
        "----------------------------------------\n"
    );


    for (
        int i = 0;
        i < item_count;
        i++
    )
    {
        printf(
            "F%-7d %-12d %-12d\n",
            items[i].id,
            items[i].risk_value,
            items[i].investigation_time
        );
    }


    printf(
        "----------------------------------------\n"
    );

    printf(
        "Enter available investigation hours: "
    );


    if (
        scanf(
            "%d",
            &capacity
        ) != 1
    )
    {
        printf(
            "Invalid investigation capacity.\n"
        );

        while (getchar() != '\n')
        {
        }

        return;
    }


    if (capacity <= 0)
    {
        printf(
            "Available hours must be positive.\n"
        );

        return;
    }


    BacktrackingKnapsackResult result =
        solve_knapsack_backtracking(
            items,
            item_count,
            capacity
        );


    printf("\n");
    printf("============================================================\n");
    printf("            BACKTRACKING OPTIMAL PLAN\n");
    printf("============================================================\n");

    printf(
        "Selected Cases : "
    );


    if (result.selected_count == 0)
    {
        printf("None");
    }
    else
    {
        for (
            int i = 0;
            i < result.selected_count;
            i++
        )
        {
            printf(
                "F%d",
                result.selected_ids[i]
            );

            if (
                i <
                result.selected_count - 1
            )
            {
                printf(", ");
            }
        }
    }


    printf("\n");

    printf(
        "Hours Used     : %d\n",
        result.total_time
    );

    printf(
        "Maximum Risk   : %d\n",
        result.maximum_risk
    );


    printf("\nMethod\n");

    printf(
        "Each case creates two recursive choices: "
        "include or exclude.\n"
    );

    printf(
        "Branches exceeding the available "
        "investigation time are pruned.\n"
    );


    printf("\nComplexity\n");
    printf(
        "Worst-case time : O(2^n)\n"
    );

    printf(
        "Recursion space : O(n)\n"
    );
}
else if (algorithm_choice != 0)
{
    printf(
        "Invalid algorithm choice.\n"
    );
}
}

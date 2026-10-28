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
#include "greedy.h"
#include "graph_algorithms.h"

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
    int graph_choice;

    WeightedGraph graph;

    /*
     * Demonstration fraud evidence graph:
     *
     * 0 = Account A501
     * 1 = Device D099
     * 2 = Account A502
     * 3 = Merchant M080
     * 4 = Account A503
     * 5 = Merchant M081
     */

    const char *labels[] = {
        "Account A501",
        "Device D099",
        "Account A502",
        "Merchant M080",
        "Account A503",
        "Merchant M081"
    };

    initialize_graph(
        &graph,
        6
    );

    add_undirected_edge(&graph, 0, 1, 1);
    add_undirected_edge(&graph, 1, 2, 1);
    add_undirected_edge(&graph, 1, 4, 1);

    add_undirected_edge(&graph, 0, 3, 4);
    add_undirected_edge(&graph, 2, 3, 2);
    add_undirected_edge(&graph, 4, 3, 3);

    add_undirected_edge(&graph, 0, 5, 5);
    add_undirected_edge(&graph, 3, 5, 2);

    printf("\n");
    printf("============================================================\n");
    printf("               FRAUD NETWORK ANALYSIS\n");
    printf("============================================================\n");

    printf("Graph Entities:\n");

    for (int i = 0; i < graph.vertices; i++)
    {
        printf(
            "%d = %s\n",
            i,
            labels[i]
        );
    }

    printf("\n1. Dijkstra Evidence Path\n");
    printf("2. Prim Minimum Evidence Network\n");
    printf("3. Kruskal Minimum Evidence Network\n");
    printf("0. Back\n");

    printf("Select graph algorithm: ");

    if (scanf("%d", &graph_choice) != 1)
    {
        printf("Invalid input.\n");

        while (getchar() != '\n')
        {
        }

        break;
    }


    /*
     * DIJKSTRA
     */
    if (graph_choice == 1)
    {
        int source;
        int destination;

        int distances[GRAPH_MAX_VERTICES];
        int previous[GRAPH_MAX_VERTICES];

        printf("Enter source vertex: ");
        scanf("%d", &source);

        printf("Enter destination vertex: ");
        scanf("%d", &destination);

        if (
            source < 0 ||
            source >= graph.vertices ||
            destination < 0 ||
            destination >= graph.vertices
        )
        {
            printf("Invalid vertex.\n");
            break;
        }

        dijkstra(
            &graph,
            source,
            distances,
            previous
        );

        if (
            distances[destination] ==
            GRAPH_INF
        )
        {
            printf(
                "No evidence path exists.\n"
            );
        }
        else
        {
            printf(
                "\nShortest evidence cost: %d\n",
                distances[destination]
            );

            printf("Evidence path: ");

            /*
             * Display names rather than only
             * numeric vertices.
             */
            int path[GRAPH_MAX_VERTICES];
            int path_length = 0;

            int current = destination;

            while (current != -1)
            {
                path[path_length++] =
                    current;

                current =
                    previous[current];
            }

            for (
                int i = path_length - 1;
                i >= 0;
                i--
            )
            {
                printf(
                    "%s",
                    labels[path[i]]
                );

                if (i > 0)
                {
                    printf(" -> ");
                }
            }

            printf("\n");
        }
    }


    /*
     * PRIM
     */
    else if (graph_choice == 2)
    {
        GraphEdge mst[
            GRAPH_MAX_VERTICES
        ];

        int edge_count =
            prim_mst(
                &graph,
                mst
            );

        int total_cost = 0;

        printf(
            "\nPrim Minimum Evidence Network\n"
        );

        printf(
            "------------------------------------------------------------\n"
        );

        for (int i = 0; i < edge_count; i++)
        {
            printf(
                "%s -> %s  cost=%d\n",
                labels[mst[i].source],
                labels[mst[i].destination],
                mst[i].weight
            );

            total_cost +=
                mst[i].weight;
        }

        printf(
            "------------------------------------------------------------\n"
        );

        printf(
            "Total evidence network cost: %d\n",
            total_cost
        );
    }


    /*
     * KRUSKAL
     */
    else if (graph_choice == 3)
    {
        GraphEdge mst[
            GRAPH_MAX_VERTICES
        ];

        int edge_count =
            kruskal_mst(
                &graph,
                mst
            );

        int total_cost = 0;

        printf(
            "\nKruskal Minimum Evidence Network\n"
        );

        printf(
            "------------------------------------------------------------\n"
        );

        for (int i = 0; i < edge_count; i++)
        {
            printf(
                "%s -> %s  cost=%d\n",
                labels[mst[i].source],
                labels[mst[i].destination],
                mst[i].weight
            );

            total_cost +=
                mst[i].weight;
        }

        printf(
            "------------------------------------------------------------\n"
        );

        printf(
            "Total evidence network cost: %d\n",
            total_cost
        );
    }

    else if (graph_choice != 0)
    {
        printf(
            "Invalid graph algorithm.\n"
        );
    }

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
                printf("4. Classical vs Strassen "
                    "Matrix Multiplication\n"
                );
                printf("5. Activity Selection\n");
                printf("6. Interval Partitioning\n");
                printf("7. Huffman Coding\n"); 
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

        break;
    }

    if (size_choice == 0)
    {
        break;
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
        break;
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

        break;
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
        break;
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
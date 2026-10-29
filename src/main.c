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
#include "dynamic_programming.h"
#include "backtracking.h"
#include "branch_bound.h"
#include "network_flow.h"
#include "number_theory.h"
#include "string_matching.h"
#include "benchmark.h"
#include "test_suite.h"
#include "export.h"
#include "fraud_graph.h"


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
            i <
            result->selected_count - 1
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

    TransactionDataset paysim_dataset = {0};
    int using_dynamic_dataset = 0;
    Transaction *active_transactions = transactions;
size_t active_count = 0;

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
    int dataset_choice;

    const char *filename = NULL;
    const char *dataset_name = NULL;

    printf("\n");
    printf("============================================================\n");
    printf("                     DATASET LOADER\n");
    printf("============================================================\n");

    printf("1. Small Dataset       (10 transactions)\n");
    printf("2. Medium Dataset      (1,000 transactions)\n");
    printf("3. Capacity Shock      (1,000 transactions)\n");
    printf("4. Large Dataset       (10,000 transactions)\n");
    printf("5. Adversarial Dataset (10,000 transactions)\n");
    printf("6. PaySim Public Fraud Dataset (Full)\n");
    printf("0. Back\n");

    printf("============================================================\n");
    printf("Select dataset: ");

    if (scanf("%d", &dataset_choice) != 1)
    {
        printf("Invalid input.\n");

        while (getchar() != '\n')
        {
            /* Clear invalid input */
        }

        break;
    }

    /*
     * Return to main menu.
     */
    if (dataset_choice == 0)
    {
        break;
    }

    /*
     * Select dataset.
     */
    if (dataset_choice == 1)
    {
        filename =
            "data/small/transactions_small.csv";

        dataset_name =
            "Small / Normal Operation";
    }

    else if (dataset_choice == 2)
    {
        filename =
            "data/medium/transactions_medium.csv";

        dataset_name =
            "Medium";
    }

    else if (dataset_choice == 3)
    {
        filename =
            "data/medium/transactions_shock.csv";

        dataset_name =
            "Capacity / Constraint Shock";
    }

    else if (dataset_choice == 4)
    {
        filename =
            "data/large/transactions_large.csv";

        dataset_name =
            "Large Data Stress";
    }

    else if (dataset_choice == 5)
    {
        filename =
            "data/adversarial/transactions_adversarial.csv";

        dataset_name =
            "Adversarial";
    }

    else if (dataset_choice == 6)
    {
        filename =
            "data/raw/PS_20174392719_1491204439457_log.csv";

        dataset_name =
            "PaySim Public Fraud Dataset";
    }

    else
    {
        printf(
            "Invalid dataset selection.\n"
        );

        break;
    }

    /*
     * PAYSim uses a different schema and
     * may contain millions of transactions.
     *
     * Therefore it uses dynamic storage.
     */
    if (dataset_choice == 6)
    {
        /*
         * If PaySim was previously loaded,
         * release it before loading again.
         */
        if (using_dynamic_dataset)
        {
            free_transaction_dataset(
                &paysim_dataset
            );

            using_dynamic_dataset = 0;
        }

        printf(
            "\nLoading full PaySim dataset dynamically...\n"
        );

        if (
            load_paysim_dynamic(
                filename,
                &paysim_dataset
            )
        )
        {
            using_dynamic_dataset = 1;
            active_transactions = paysim_dataset.items;
active_count = paysim_dataset.count;

            printf(
                "\nFull PaySim dataset loaded successfully.\n"
            );

            printf(
                "Scenario: %s\n",
                dataset_name
            );

            printf(
                "Source  : %s\n",
                filename
            );

            printf(
                "Transactions loaded: %zu\n",
                paysim_dataset.count
            );

            printf(
                "Allocated capacity : %zu\n",
                paysim_dataset.capacity
            );
        }
        else
        {
            printf(
                "\nERROR: PaySim dynamic loading failed.\n"
            );
        }

        /*
         * IMPORTANT:
         *
         * At this stage PaySim remains inside
         * paysim_dataset.items.
         *
         * Existing menu options still use the
         * original transactions pointer.
         *
         * We will connect them through an active
         * dataset abstraction next.
         */
        break;
    }

    /*
     * Normal workbench CSV datasets use
     * the existing fixed-buffer loader.
     */
    transaction_count =
        load_transactions_csv(
            filename,
            transactions,
            MAX_TRANSACTIONS
        );

    if (transaction_count >= 0)
    {
        active_transactions = transactions;
active_count = (size_t)transaction_count;
        printf(
            "\nDataset loaded successfully.\n"
        );

        printf(
            "Scenario: %s\n",
            dataset_name
        );

        printf(
            "Source  : %s\n",
            filename
        );

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
    if (
        active_transactions == NULL ||
        active_count == 0
    )
    {
        printf(
            "No dataset is currently loaded.\n"
        );

        printf(
            "Please load a dataset first.\n"
        );

        break;
    }

    const size_t page_size = 25;
    size_t page = 0;

    char command = '\0';

    do
    {
        size_t start =
            page * page_size;

        /*
         * Safety check.
         */
        if (start >= active_count)
        {
            page = 0;
            start = 0;
        }

        size_t end =
            start + page_size;

        if (end > active_count)
        {
            end = active_count;
        }


        printf("\n");
        printf(
            "============================================================\n"
        );

        printf(
            "          TRANSACTIONS %zu - %zu OF %zu\n",
            start + 1,
            end,
            active_count
        );

        printf(
            "============================================================\n"
        );


        for (
            size_t i = start;
            i < end;
            i++
        )
        {
            printf(
                "\nTransaction #%zu\n",
                i + 1
            );

            printf(
                "------------------------------------------------------------\n"
            );

            print_transaction(
                &active_transactions[i]
            );
        }


        printf("\n");
        printf(
            "============================================================\n"
        );

        printf("[N] Next Page\n");
        printf("[P] Previous Page\n");
        printf("[Q] Back to Main Menu\n");

        printf(
            "============================================================\n"
        );

        printf("Choice: ");


        if (
            scanf(
                " %c",
                &command
            ) != 1
        )
        {
            printf(
                "Invalid input.\n"
            );

            while (getchar() != '\n')
            {
            }

            command = 'Q';

            continue;
        }


        /*
         * NEXT PAGE
         */
        if (
            command == 'N' ||
            command == 'n'
        )
        {
            if (
                (page + 1) *
                page_size <
                active_count
            )
            {
                page++;
            }
            else
            {
                printf(
                    "\nAlready at the last page.\n"
                );
            }
        }


        /*
         * PREVIOUS PAGE
         */
        else if (
            command == 'P' ||
            command == 'p'
        )
        {
            if (page > 0)
            {
                page--;
            }
            else
            {
                printf(
                    "\nAlready at the first page.\n"
                );
            }
        }


        /*
         * QUIT VIEWER
         */
        else if (
            command == 'Q' ||
            command == 'q'
        )
        {
            /* Exit loop */
        }


        else
        {
            printf(
                "\nInvalid command. "
                "Use N, P or Q.\n"
            );
        }

    } while (
        command != 'Q' &&
        command != 'q'
    );

    break;
}

            /*
             * OPTION 3
             * Fraud investigation
             */
            case 3:
{
    if (
        active_transactions == NULL ||
        active_count == 0
    )
    {
        printf(
            "No dataset is currently loaded.\n"
        );

        printf(
            "Please load a dataset first.\n"
        );

        break;
    }


    /*
     * Full PaySim dataset:
     * evaluate silently over all transactions
     * rather than printing millions of rows.
     */
    if (using_dynamic_dataset)
    {
        int threshold;

        printf("\n");
        printf("============================================================\n");
        printf("             PAYSIM FRAUD INVESTIGATION\n");
        printf("============================================================\n");

        printf(
            "Transactions: %zu\n",
            active_count
        );

        printf(
            "Enter risk threshold (0-100) "
            "[recommended: 50]: "
        );


        if (
            scanf(
                "%d",
                &threshold
            ) != 1
        )
        {
            printf(
                "Invalid threshold.\n"
            );

            while (getchar() != '\n')
            {
            }

            break;
        }


        if (
            threshold < 0 ||
            threshold > 100
        )
        {
            printf(
                "Risk threshold must be "
                "between 0 and 100.\n"
            );

            break;
        }


        printf(
            "\nAnalyzing %zu transactions...\n",
            active_count
        );


        FraudEvaluation evaluation =
            evaluate_paysim_fraud(
                active_transactions,
                active_count,
                threshold
            );


        print_fraud_evaluation(
            &evaluation,
            threshold
        );
    }

    /*
     * Original/synthetic datasets retain
     * the existing fraud-analysis module.
     */
    else
    {
        analyze_fraud(
            active_transactions,
            (int)active_count
        );
    }


    break;
}

            /*
             * OPTION 4
             * Sorting and searching
             */
            case 4:
            {
                int operation_choice;

            if (
    active_transactions == NULL ||
    active_count == 0
)
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

                    merge_sort_transactions(
    active_transactions,
    (int)active_count
);

printf(
    "\nMerge Sort completed successfully.\n"
);

printf(
    "Transactions sorted: %zu\n",
    active_count
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

                   quick_sort_transactions(
    active_transactions,
    (int)active_count
);

printf(
    "\nQuick Sort completed successfully.\n"
);

printf(
    "Transactions sorted: %zu\n",
    active_count
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

                    if (scanf("%31s", search_id) != 1)
                    {
                        printf("Invalid Transaction ID.\n");
                        break;
                    }

                    /*
                     * Binary search requires sorted data.
                     */
                    sort_transactions_by_id(
    active_transactions,
    (int)active_count
);

                    /*
                     * Iterative Binary Search
                     */
                    if (operation_choice == 3)
                    {
                        result = binary_search_iterative(
    active_transactions,
    (int)active_count,
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
    active_transactions,
    (int)active_count,
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
                            &active_transactions[result]
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
    char text[STRING_MAX_LENGTH + 1];
    char pattern[PATTERN_MAX_LENGTH + 1];

    int pattern_choice;

    printf("\n");
    printf("============================================================\n");
    printf("                 FRAUD PATTERN SEARCH\n");
    printf("============================================================\n");

    /*
     * scanf leaves a newline in stdin.
     */
    int ch;

    while (
        (ch = getchar()) != '\n' &&
        ch != EOF
    )
    {
    }


    printf(
        "Enter transaction/event text:\n"
    );

    if (
        fgets(
            text,
            sizeof(text),
            stdin
        ) == NULL
    )
    {
        printf("Unable to read text.\n");
        break;
    }


    /*
     * Remove trailing newline.
     */
    for (
        int i = 0;
        text[i] != '\0';
        i++
    )
    {
        if (text[i] == '\n')
        {
            text[i] = '\0';
            break;
        }
    }


    printf(
        "Enter suspicious pattern: "
    );

    if (
        fgets(
            pattern,
            sizeof(pattern),
            stdin
        ) == NULL
    )
    {
        printf(
            "Unable to read pattern.\n"
        );

        break;
    }


    for (
        int i = 0;
        pattern[i] != '\0';
        i++
    )
    {
        if (pattern[i] == '\n')
        {
            pattern[i] = '\0';
            break;
        }
    }


    printf("\n");
    printf("1. Naive Pattern Matching\n");
    printf("2. Rabin-Karp\n");
    printf("3. Finite Automaton\n");
    printf("4. KMP\n");
    printf("5. Compare All Algorithms\n");
    printf("0. Back\n");

    printf(
        "Select pattern algorithm: "
    );

    if (
        scanf(
            "%d",
            &pattern_choice
        ) != 1
    )
    {
        printf("Invalid input.\n");

        while (getchar() != '\n')
        {
        }

        break;
    }


    MatchResult result;


    if (pattern_choice == 1)
    {
        result =
            naive_pattern_search(
                text,
                pattern
            );

        printf(
            "\nAlgorithm: Naive Pattern Matching\n"
        );
    }

    else if (pattern_choice == 2)
    {
        result =
            rabin_karp_search(
                text,
                pattern
            );

        printf(
            "\nAlgorithm: Rabin-Karp\n"
        );
    }

    else if (pattern_choice == 3)
    {
        result =
            finite_automaton_search(
                text,
                pattern
            );

        printf(
            "\nAlgorithm: Finite Automaton\n"
        );
    }

    else if (pattern_choice == 4)
    {
        result =
            kmp_search(
                text,
                pattern
            );

        printf(
            "\nAlgorithm: KMP\n"
        );
    }

    else if (pattern_choice == 5)
    {
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


        printf("\n");
        printf("============================================================\n");
        printf("             STRING MATCHING COMPARISON\n");
        printf("============================================================\n");


        printf("Naive            : ");

        for (int i = 0;
             i < naive.count;
             i++)
        {
            printf(
                "%d ",
                naive.positions[i]
            );
        }

        printf("\n");


        printf("Rabin-Karp       : ");

        for (int i = 0;
             i < rabin.count;
             i++)
        {
            printf(
                "%d ",
                rabin.positions[i]
            );
        }

        printf("\n");


        printf("Finite Automaton : ");

        for (int i = 0;
             i < automaton.count;
             i++)
        {
            printf(
                "%d ",
                automaton.positions[i]
            );
        }

        printf("\n");


        printf("KMP              : ");

        for (int i = 0;
             i < kmp.count;
             i++)
        {
            printf(
                "%d ",
                kmp.positions[i]
            );
        }

        printf("\n");


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


        printf("\nCorrectness Check: ");

        if (correct)
        {
            printf("PASS\n");

            printf(
                "All four algorithms found "
                "identical match positions.\n"
            );
        }
        else
        {
            printf("FAIL\n");
        }


        printf("\nComplexity Summary\n");
        printf("----------------------------------------\n");
        printf("Naive            : O(n*m) worst case\n");
        printf("Rabin-Karp       : O(n+m) average, O(n*m) worst\n");
        printf("Finite Automaton : O(n) search after preprocessing\n");
        printf("KMP              : O(n+m)\n");

        break;
    }

    else if (pattern_choice == 0)
    {
        break;
    }

    else
    {
        printf(
            "Invalid pattern algorithm.\n"
        );

        break;
    }


    /*
     * Individual algorithm output.
     */
    if (result.count == 0)
    {
        printf(
            "Pattern not found.\n"
        );
    }
    else
    {
        printf(
            "Matches found: %d\n",
            result.count
        );

        printf(
            "Match positions: "
        );

        for (
            int i = 0;
            i < result.count;
            i++
        )
        {
            printf(
                "%d ",
                result.positions[i]
            );
        }

        printf("\n");
    }

    break;
}

            /*
             * OPTION 6
             * Graph algorithms
             */
            case 6:
{
        /*
     * Real PaySim investigation graph.
     */
    if (using_dynamic_dataset)
    {
        int threshold;

        printf("\n");
        printf("============================================================\n");
        printf("           PAYSIM FRAUD NETWORK ANALYSIS\n");
        printf("============================================================\n");

        printf(
            "Enter risk threshold (0-100): "
        );

        if (
            scanf(
                "%d",
                &threshold
            ) != 1
        )
        {
            printf("Invalid threshold.\n");

            while (getchar() != '\n')
            {
            }

            break;
        }

        if (
            threshold < 0 ||
            threshold > 100
        )
        {
            printf(
                "Threshold must be between "
                "0 and 100.\n"
            );

            break;
        }


        /*
         * Risk scores must exist before
         * constructing the suspicious graph.
         */
        FraudEvaluation evaluation =
            evaluate_paysim_fraud(
                active_transactions,
                active_count,
                threshold
            );

        FraudInvestigationGraph fraud_graph;

        if (
            !build_paysim_investigation_graph(
                active_transactions,
                active_count,
                threshold,
                &fraud_graph
            )
        )
        {
            printf(
                "Unable to build investigation graph.\n"
            );

            break;
        }


        printf("\n");
        printf(
            "Investigation graph created.\n"
        );
        printf(
    "Source Dataset     : PaySim\n"
);

printf(
    "Dataset Records    : %zu\n",
    active_count
);

printf(
    "Risk Threshold     : %d\n",
    threshold
);

        printf(
            "Vertices          : %d\n",
            fraud_graph.graph.vertices
        );

        printf(
            "Suspicious links : %d\n",
            fraud_graph.transaction_edges
        );

        printf(
            "Actual fraud in full dataset: %zu\n",
            evaluation.actual_fraud
        );


        printf("\nGraph Entities\n");
        printf(
            "------------------------------------------------------------\n"
        );

        for (
            int i = 0;
            i < fraud_graph.graph.vertices;
            i++
        )
        {
            printf(
                "%2d = %s\n",
                i,
                fraud_graph.labels[i]
            );
        }


        printf("\n");
        printf("1. Dijkstra Evidence Path\n");
        printf("2. Prim Minimum Evidence Network\n");
        printf("3. Kruskal Minimum Evidence Network\n");
        printf("4. Bellman-Ford Evidence Path\n");
        printf("5. Floyd-Warshall All-Pairs Analysis\n");
        printf("0. Back\n");

        printf(
            "Select graph algorithm: "
        );

        int paysim_graph_choice;

        if (
            scanf(
                "%d",
                &paysim_graph_choice
            ) != 1
        )
        {
            printf("Invalid input.\n");

            while (getchar() != '\n')
            {
            }

            break;
        }


        /*
         * Start with Dijkstra.
         * Other algorithms are wired below.
         */
        if (paysim_graph_choice == 1)
        {
            int source;
            int destination;

            printf(
                "Enter source vertex: "
            );

            scanf(
                "%d",
                &source
            );

            printf(
                "Enter destination vertex: "
            );

            scanf(
                "%d",
                &destination
            );


            if (
                source < 0 ||
                source >=
                    fraud_graph.graph.vertices ||
                destination < 0 ||
                destination >=
                    fraud_graph.graph.vertices
            )
            {
                printf(
                    "Invalid vertex.\n"
                );

                break;
            }


            int distances[
                GRAPH_MAX_VERTICES
            ];

            int previous[
                GRAPH_MAX_VERTICES
            ];


            dijkstra(
                &fraud_graph.graph,
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
                    "\nNo evidence path exists "
                    "between these accounts.\n"
                );
            }
            else
            {
                printf(
                    "\nEvidence cost: %d\n",
                    distances[destination]
                );


                int path[
                    GRAPH_MAX_VERTICES
                ];

                int path_length = 0;

                int current =
                    destination;


                while (
                    current != -1 &&
                    path_length <
                    GRAPH_MAX_VERTICES
                )
                {
                    path[path_length++] =
                        current;

                    current =
                        previous[current];
                }


                printf(
                    "Evidence path: "
                );

                for (
                    int i =
                        path_length - 1;
                    i >= 0;
                    i--
                )
                {
                    printf(
                        "%s",
                        fraud_graph
                            .labels[path[i]]
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
else if (paysim_graph_choice == 2)
{
    GraphEdge mst[
        GRAPH_MAX_VERTICES
    ];

    int edge_count =
        prim_mst(
            &fraud_graph.graph,
            mst
        );

    int total_cost = 0;

    printf("\n");
    printf("============================================================\n");
    printf("        PRIM MINIMUM EVIDENCE NETWORK\n");
    printf("============================================================\n");

    if (
        edge_count !=
        fraud_graph.graph.vertices - 1
    )
    {
        printf(
            "WARNING: Investigation graph is disconnected.\n"
        );

        printf(
            "A complete spanning tree could not be created.\n\n"
        );
    }

    for (int i = 0; i < edge_count; i++)
    {
        printf(
            "%s -> %s | Evidence Cost = %d\n",
            fraud_graph.labels[
                mst[i].source
            ],
            fraud_graph.labels[
                mst[i].destination
            ],
            mst[i].weight
        );

        total_cost +=
            mst[i].weight;
    }

    printf(
        "------------------------------------------------------------\n"
    );

    printf(
        "Edges selected : %d\n",
        edge_count
    );

    printf(
        "Total evidence network cost: %d\n",
        total_cost
    );
}


/*
 * KRUSKAL
 */
else if (paysim_graph_choice == 3)
{
    GraphEdge mst[
        GRAPH_MAX_VERTICES
    ];

    int edge_count =
        kruskal_mst(
            &fraud_graph.graph,
            mst
        );

    int total_cost = 0;

    printf("\n");
    printf("============================================================\n");
    printf("       KRUSKAL MINIMUM EVIDENCE NETWORK\n");
    printf("============================================================\n");

    if (
        edge_count !=
        fraud_graph.graph.vertices - 1
    )
    {
        printf(
            "WARNING: Investigation graph is disconnected.\n"
        );

        printf(
            "A complete spanning tree could not be created.\n\n"
        );
    }

    for (int i = 0; i < edge_count; i++)
    {
        printf(
            "%s -> %s | Evidence Cost = %d\n",
            fraud_graph.labels[
                mst[i].source
            ],
            fraud_graph.labels[
                mst[i].destination
            ],
            mst[i].weight
        );

        total_cost +=
            mst[i].weight;
    }

    printf(
        "------------------------------------------------------------\n"
    );

    printf(
        "Edges selected : %d\n",
        edge_count
    );

    printf(
        "Total evidence network cost: %d\n",
        total_cost
    );
}


/*
 * BELLMAN-FORD
 */
else if (paysim_graph_choice == 4)
{
    int source;
    int destination;

    printf(
        "Enter source vertex: "
    );

    if (
        scanf(
            "%d",
            &source
        ) != 1
    )
    {
        printf("Invalid source vertex.\n");

        while (getchar() != '\n')
        {
        }

        break;
    }

    printf(
        "Enter destination vertex: "
    );

    if (
        scanf(
            "%d",
            &destination
        ) != 1
    )
    {
        printf(
            "Invalid destination vertex.\n"
        );

        while (getchar() != '\n')
        {
        }

        break;
    }

    if (
        source < 0 ||
        source >= fraud_graph.graph.vertices ||
        destination < 0 ||
        destination >= fraud_graph.graph.vertices
    )
    {
        printf(
            "Invalid vertex selection.\n"
        );

        break;
    }

    int distances[
        GRAPH_MAX_VERTICES
    ];

    int previous[
        GRAPH_MAX_VERTICES
    ];

    int valid =
        bellman_ford(
            &fraud_graph.graph,
            source,
            distances,
            previous
        );

    if (!valid)
    {
        printf(
            "\nNegative-weight cycle detected.\n"
        );
    }

    else if (
        distances[destination] ==
        GRAPH_INF
    )
    {
        printf(
            "\nNo evidence path exists between "
            "these accounts.\n"
        );
    }

    else
    {
        printf("\n");
        printf(
            "Bellman-Ford Evidence Cost: %d\n",
            distances[destination]
        );

        int path[
            GRAPH_MAX_VERTICES
        ];

        int path_length = 0;

        int current =
            destination;

        while (
            current != -1 &&
            path_length <
            GRAPH_MAX_VERTICES
        )
        {
            path[path_length++] =
                current;

            current =
                previous[current];
        }

        printf(
            "Evidence Path: "
        );

        for (
            int i = path_length - 1;
            i >= 0;
            i--
        )
        {
            printf(
                "%s",
                fraud_graph.labels[
                    path[i]
                ]
            );

            if (i > 0)
            {
                printf(" -> ");
            }
        }

        printf("\n");

        /*
         * Correctness comparison:
         * PaySim graph contains only
         * positive evidence costs.
         */
        int dijkstra_distances[
            GRAPH_MAX_VERTICES
        ];

        int dijkstra_previous[
            GRAPH_MAX_VERTICES
        ];

        dijkstra(
            &fraud_graph.graph,
            source,
            dijkstra_distances,
            dijkstra_previous
        );

        printf(
            "Dijkstra Cost    : %d\n",
            dijkstra_distances[
                destination
            ]
        );

        printf(
            "Correctness Check: %s\n",
            dijkstra_distances[
                destination
            ] ==
            distances[
                destination
            ]
                ? "PASS"
                : "FAIL"
        );
    }
}


/*
 * FLOYD-WARSHALL
 */
else if (paysim_graph_choice == 5)
{
    int distances
        [GRAPH_MAX_VERTICES]
        [GRAPH_MAX_VERTICES];

    floyd_warshall(
        &fraud_graph.graph,
        distances
    );

    printf("\n");
    printf("============================================================\n");
    printf("       ALL-PAIRS PAYSIM EVIDENCE DISTANCES\n");
    printf("============================================================\n");

    /*
     * Numeric vertex IDs are used as column
     * headings because PaySim account IDs are
     * too long for a compact matrix.
     */
    printf("%8s", "");

    for (
        int j = 0;
        j < fraud_graph.graph.vertices;
        j++
    )
    {
        printf(
            "%7d",
            j
        );
    }

    printf("\n");

    for (
        int i = 0;
        i < fraud_graph.graph.vertices;
        i++
    )
    {
        printf(
            "%-7d",
            i
        );

        for (
            int j = 0;
            j < fraud_graph.graph.vertices;
            j++
        )
        {
            if (
                distances[i][j] ==
                GRAPH_INF
            )
            {
                printf(
                    "%7s",
                    "INF"
                );
            }
            else
            {
                printf(
                    "%7d",
                    distances[i][j]
                );
            }
        }

        printf("\n");
    }

    printf(
        "============================================================\n"
    );

    printf("\nVertex Legend\n");
    printf(
        "------------------------------------------------------------\n"
    );

    for (
        int i = 0;
        i < fraud_graph.graph.vertices;
        i++
    )
    {
        printf(
            "%2d = %s\n",
            i,
            fraud_graph.labels[i]
        );
    }
}


/*
 * BACK
 */
else if (paysim_graph_choice == 0)
{
    /* Return to main menu. */
}


else
{
    printf(
        "Invalid graph algorithm.\n"
    );
}
    break;
    }
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
    printf("4. Bellman-Ford Evidence Path\n");
printf("5. Floyd-Warshall All-Pairs Analysis\n");
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
    else if (graph_choice == 4)
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

    int valid =
        bellman_ford(
            &graph,
            source,
            distances,
            previous
        );

    if (!valid)
    {
        printf(
            "\nNegative-weight cycle detected.\n"
        );
    }
    else if (
        distances[destination] ==
        GRAPH_INF
    )
    {
        printf(
            "\nNo evidence path exists.\n"
        );
    }
    else
    {
        printf(
            "\nBellman-Ford shortest evidence cost: %d\n",
            distances[destination]
        );

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

        printf("Evidence path: ");

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
else if (graph_choice == 5)
{
    int distances
        [GRAPH_MAX_VERTICES]
        [GRAPH_MAX_VERTICES];

    floyd_warshall(
        &graph,
        distances
    );

    printf("\n");
    printf("============================================================\n");
    printf("          ALL-PAIRS EVIDENCE DISTANCES\n");
    printf("============================================================\n");

    printf("%12s", "");

    for (int j = 0; j < graph.vertices; j++)
    {
        printf(
            "%8d",
            j
        );
    }

    printf("\n");

    for (int i = 0; i < graph.vertices; i++)
    {
        printf(
            "Vertex %-5d",
            i
        );

        for (int j = 0; j < graph.vertices; j++)
        {
            if (
                distances[i][j] ==
                GRAPH_INF
            )
            {
                printf(
                    "%8s",
                    "INF"
                );
            }
            else
            {
                printf(
                    "%8d",
                    distances[i][j]
                );
            }
        }

        printf("\n");
    }

    printf(
        "============================================================\n"
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
    InvestigationCase cases[] = {
        {1, 95, 4},
        {2, 60, 2},
        {3, 80, 3},
        {4, 30, 1},
        {5, 90, 5}
    };

    int case_count =
        sizeof(cases) /
        sizeof(cases[0]);

    int available_hours;

    printf("\n");
    printf("============================================================\n");
    printf("              INVESTIGATION PLANNING\n");
    printf("============================================================\n");

    printf(
        "%-10s %-15s %-20s\n",
        "CASE",
        "RISK VALUE",
        "TIME REQUIRED"
    );

    printf(
        "------------------------------------------------------------\n"
    );

    for (int i = 0; i < case_count; i++)
    {
        printf(
            "F%-9d %-15d %-5d hours\n",
            cases[i].id,
            cases[i].risk_value,
            cases[i].investigation_time
        );
    }

    printf(
        "------------------------------------------------------------\n"
    );

    printf(
        "Enter available investigation hours: "
    );

    if (
        scanf(
            "%d",
            &available_hours
        ) != 1
    )
    {
        printf("Invalid input.\n");

        while (getchar() != '\n')
        {
            /* Clear invalid input */
        }

        break;
    }

    if (
        available_hours <= 0 ||
        available_hours > MAX_CAPACITY
    )
    {
        printf(
            "Available hours must be between "
            "1 and %d.\n",
            MAX_CAPACITY
        );

        break;
    }


    KnapsackResult result =
        solve_zero_one_knapsack(
            cases,
            case_count,
            available_hours
        );


    printf("\n");
    printf("============================================================\n");
    printf("             OPTIMAL INVESTIGATION PLAN\n");
    printf("============================================================\n");

    int total_time = 0;

    /*
     * Backtracking stores selected
     * indices in reverse order.
     */
    for (
        int i = result.selected_count - 1;
        i >= 0;
        i--
    )
    {
        int index =
            result.selected_indices[i];

        printf(
            "Case F%d  | Risk = %d | Time = %d hours\n",
            cases[index].id,
            cases[index].risk_value,
            cases[index].investigation_time
        );

        total_time +=
            cases[index].investigation_time;
    }

    printf(
        "------------------------------------------------------------\n"
    );

    printf(
        "Available Hours   : %d\n",
        available_hours
    );

    printf(
        "Hours Used        : %d\n",
        total_time
    );

    printf(
        "Maximum Risk Value: %d\n",
        result.maximum_risk
    );

    printf(
        "Cases Selected    : %d\n",
        result.selected_count
    );

    printf(
        "============================================================\n"
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

        break;
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

        break;
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

        break;
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
    printf("          CHINESE REMAINDER THEOREM\n");
    printf("============================================================\n");

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
        printf("Invalid input.\n");

        while (getchar() != '\n')
        {
        }

        break;
    }


    if (benchmark_choice == 1)
    {
        run_sorting_benchmark();
    }

    else if (benchmark_choice == 2)
    {
        run_string_matching_benchmark();
    }
else if (benchmark_choice == 3)
{
    run_matrix_benchmark();
}

    else if (benchmark_choice == 4)
{
    run_graph_benchmark();
}

    else if (benchmark_choice == 5)
    {
        printf(
            "Complete benchmark suite - Coming Soon\n"
        );
    }

    else if (benchmark_choice != 0)
    {
        printf(
            "Invalid benchmark choice.\n"
        );
    }

    break;
}

            /*
             * OPTION 10
             * Test suite
             */
            case 10:
{
    run_test_suite();
    break;
}

            /*
             * OPTION 11
             * Export results
             */
            case 11:
{
    if (
        active_transactions == NULL ||
        active_count == 0
    )
    {
        printf(
            "No dataset is currently loaded.\n"
        );

        break;
    }

    int export_choice;

    printf("\n");
    printf("============================================================\n");
    printf("                     EXPORT RESULTS\n");
    printf("============================================================\n");

    printf("1. Export Sample (first 1,000) as CSV\n");
    printf("2. Export Sample (first 1,000) as JSON\n");
    printf("3. Export Suspicious Transactions as CSV\n");

    if (using_dynamic_dataset)
    {
        printf(
            "4. Export Actual PaySim Fraud as CSV\n"
        );
    }

    printf("5. Export Full Dataset as CSV\n");
    printf("0. Back\n");

    printf("============================================================\n");
    printf("Select export: ");

    if (
        scanf(
            "%d",
            &export_choice
        ) != 1
    )
    {
        printf("Invalid input.\n");

        while (getchar() != '\n')
        {
        }

        break;
    }


    size_t sample_count =
        active_count < 1000 ?
        active_count :
        1000;


    if (export_choice == 1)
    {
        if (
            export_transactions_csv(
                "results/transactions_sample.csv",
                active_transactions,
                sample_count
            )
        )
        {
            printf(
                "\nExported %zu transactions to:\n"
                "results/transactions_sample.csv\n",
                sample_count
            );
        }
        else
        {
            printf(
                "\nERROR: CSV export failed.\n"
            );
        }
    }


    else if (export_choice == 2)
    {
        if (
            export_transactions_json(
                "results/transactions_sample.json",
                active_transactions,
                sample_count
            )
        )
        {
            printf(
                "\nExported %zu transactions to:\n"
                "results/transactions_sample.json\n",
                sample_count
            );
        }
        else
        {
            printf(
                "\nERROR: JSON export failed.\n"
            );
        }
    }


    else if (export_choice == 3)
    {
        int threshold;

        printf(
            "Enter risk threshold: "
        );

        if (
            scanf(
                "%d",
                &threshold
            ) != 1 ||
            threshold < 0 ||
            threshold > 100
        )
        {
            printf(
                "Invalid risk threshold.\n"
            );

            while (getchar() != '\n')
            {
            }

            break;
        }

        if (
            export_suspicious_csv(
                "results/suspicious_transactions.csv",
                active_transactions,
                active_count,
                threshold
            )
        )
        {
            printf(
                "\nSuspicious transactions exported to:\n"
                "results/suspicious_transactions.csv\n"
            );
        }
        else
        {
            printf(
                "\nERROR: Export failed.\n"
            );
        }
    }


    else if (
        export_choice == 4 &&
        using_dynamic_dataset
    )
    {
        if (
            export_actual_fraud_csv(
                "results/paysim_actual_fraud.csv",
                active_transactions,
                active_count
            )
        )
        {
            printf(
                "\nPaySim ground-truth fraud exported to:\n"
                "results/paysim_actual_fraud.csv\n"
            );
        }
        else
        {
            printf(
                "\nERROR: Export failed.\n"
            );
        }
    }


    else if (export_choice == 5)
    {
        printf(
            "\nWARNING: Full export contains %zu transactions.\n",
            active_count
        );

        printf(
            "This may create a very large file.\n"
        );

        printf(
            "Continue? (Y/N): "
        );

        char confirm;

        scanf(
            " %c",
            &confirm
        );

        if (
            confirm != 'Y' &&
            confirm != 'y'
        )
        {
            printf(
                "Full export cancelled.\n"
            );

            break;
        }

        if (
            export_transactions_csv(
                "results/transactions_full.csv",
                active_transactions,
                active_count
            )
        )
        {
            printf(
                "\nFull dataset exported successfully.\n"
            );
        }
        else
        {
            printf(
                "\nERROR: Full export failed.\n"
            );
        }
    }


    else if (export_choice != 0)
    {
        printf(
            "Invalid export choice.\n"
        );
    }

    break;
}
             /* EXIT
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
    if (using_dynamic_dataset)
{
    free_transaction_dataset(
        &paysim_dataset
    );
}
    free(transactions);

    return 0;
}


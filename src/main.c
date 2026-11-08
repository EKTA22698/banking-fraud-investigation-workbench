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
#include "benchmark.h"
#include "export_menu.h"
#include "benchmark_menu.h"
#include "pattern_menu.h"
#include "transaction_viewer.h"
#include "fraud_menu.h"
#include "search_sort_menu.h"
#include "app_state.h"
#include "dataset_menu.h"
#include "graph_menu.h"
#include "test_menu.h"
#include "planning_menu.h"
#include "algorithm_lab_menu.h"



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
    ApplicationState state;

if (
    !initialize_application_state(
        &state
    )
)
{
    return 1;
}

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
    run_dataset_menu(&state);
    break;
}

            /*
             * OPTION 2
             * View loaded transactions
             */
            case 2:
{
    run_transaction_viewer(
        state.active_transactions,
        state.active_count
    );

    break;
}
            /*
             * OPTION 3
             * Fraud investigation
             */
           case 3:
{
    run_fraud_menu(
        state.active_transactions,
        state.active_count,
        state.using_dynamic_dataset
    );

    break;
}
            /*
             * OPTION 4
             * Sorting and searching
             */

    case 4:
{
    run_search_sort_menu(
        state.active_transactions,
        state.active_count
    );

    break;
}

            /*
             * OPTION 5
             * Pattern matching module
             */
            case 5:
{
    run_pattern_menu();
    break;
}

            /*
             * OPTION 6
             * Graph algorithms
             */
            /*
 * OPTION 6
 * Fraud Network Analysis
 */
case 6:
{
    run_graph_menu(
        state.active_transactions,
        state.active_count,
        state.using_dynamic_dataset
    );

    break;
}
            /*
             * OPTION 7
             * Optimization and investigation planning
             */
            /*
 * OPTION 7
 * Optimization and Investigation Planning
 */
case 7:
{
    run_planning_menu();
    break;
}

            /*
             * OPTION 8
             * DAA Algorithm Laboratory
             */
           case 8:
{
    run_algorithm_lab_menu();
    break;
}
            /*
             * OPTION 9
             * Benchmark runner
             */
            case 9:
{
    run_benchmark_menu(
        state.active_transactions,
        state.active_count,
        state.using_dynamic_dataset
    );

    break;
}

            /*
             * OPTION 10
             * Test suite
             */
            /*
 * OPTION 10
 * Test Suite
 */
case 10:
{
    run_test_menu();
    break;
}

            /*
             * OPTION 11
             * Export results
             */
            case 11:
{
    run_export_menu(
        state.active_transactions,
        state.active_count,
        state.using_dynamic_dataset
    );

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
    cleanup_application_state(
    &state
);

return 0;
}

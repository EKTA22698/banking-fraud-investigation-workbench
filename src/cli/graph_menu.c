#include <stdio.h>

#include "graph_menu.h"

#include "fraud.h"
#include "graph_algorithms.h"
#include "fraud_graph.h"


void run_graph_menu(
    Transaction transactions[],
    size_t transaction_count,
    int is_paysim
)
{
    if (
        transactions == NULL ||
        transaction_count == 0
    )
    {
        printf(
            "No dataset is currently loaded.\n"
        );

        return;
    }

    /*
     * PASTE THE OLD CASE 6 BODY HERE.
     *
     * Do NOT include:
     *
     * case 6:
     * {
     *
     * or its final:
     *
     * break;
     * }
     */
}
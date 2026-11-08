#ifndef GRAPH_MENU_H
#define GRAPH_MENU_H

#include <stddef.h>

#include "transaction.h"

void run_graph_menu(
    Transaction transactions[],
    size_t transaction_count,
    int is_paysim
);

#endif
#ifndef SEARCH_SORT_MENU_H
#define SEARCH_SORT_MENU_H

#include <stddef.h>

#include "transaction.h"

void run_search_sort_menu(
    Transaction transactions[],
    size_t transaction_count
);

#endif
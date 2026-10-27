#ifndef SEARCHING_H
#define SEARCHING_H

#include "transaction.h"

void sort_transactions_by_id(
    Transaction transactions[],
    int count
);

int binary_search_iterative(
    const Transaction transactions[],
    int count,
    const char *transaction_id
);

int binary_search_recursive(
    const Transaction transactions[],
    int count,
    const char *transaction_id
);

#endif
#ifndef SORTING_H
#define SORTING_H

#include "transaction.h"

/*
 * Sort transactions in ascending order of amount.
 */
void merge_sort_transactions(
    Transaction transactions[],
    int count
);

void quick_sort_transactions(
    Transaction transactions[],
    int count
);

#endif
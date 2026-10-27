#ifndef DATASET_H
#define DATASET_H

#include "transaction.h"

#define MAX_TRANSACTIONS 10000

int load_transactions_csv(
    const char *filename,
    Transaction transactions[],
    int max_transactions
);

void print_dataset_summary(
    const Transaction transactions[],
    int transaction_count
);
void print_all_transactions(
    const Transaction transactions[],
    int transaction_count
);
#endif
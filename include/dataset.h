#ifndef DATASET_H
#define DATASET_H
#include <stddef.h>
#include "transaction.h"

#define MAX_TRANSACTIONS 20000

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
int load_paysim_csv(
    const char *filename,
    Transaction transactions[],
    int max_transactions
);
typedef struct
{
    Transaction *items;
    size_t count;
    size_t capacity;
} TransactionDataset;

int load_paysim_dynamic(
    const char *filename,
    TransactionDataset *dataset
);

void free_transaction_dataset(
    TransactionDataset *dataset
);
#endif
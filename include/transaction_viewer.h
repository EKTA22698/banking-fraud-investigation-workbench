#ifndef TRANSACTION_VIEWER_H
#define TRANSACTION_VIEWER_H

#include <stddef.h>

#include "transaction.h"

void run_transaction_viewer(
    const Transaction transactions[],
    size_t transaction_count
);

#endif
#ifndef EXPORT_H
#define EXPORT_H

#include <stddef.h>

#include "transaction.h"

int export_transactions_csv(
    const char *filename,
    const Transaction transactions[],
    size_t count
);

int export_transactions_json(
    const char *filename,
    const Transaction transactions[],
    size_t count
);

int export_suspicious_csv(
    const char *filename,
    const Transaction transactions[],
    size_t count,
    int risk_threshold
);

int export_actual_fraud_csv(
    const char *filename,
    const Transaction transactions[],
    size_t count
);

#endif
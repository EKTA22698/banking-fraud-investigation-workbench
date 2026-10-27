#ifndef FRAUD_H
#define FRAUD_H

#include "transaction.h"

int calculate_risk_score(
    Transaction transactions[],
    int transaction_count,
    int index
);

const char *get_risk_level(int risk_score);

void analyze_fraud(
    Transaction transactions[],
    int transaction_count
);

#endif
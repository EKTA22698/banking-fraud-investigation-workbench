#include <stddef.h>
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
typedef struct
{
    size_t total_transactions;

    size_t actual_fraud;
    size_t actual_normal;

    size_t predicted_fraud;
    size_t predicted_normal;

    size_t true_positive;
    size_t false_positive;
    size_t true_negative;
    size_t false_negative;

    double accuracy;
    double precision;
    double recall;
    double f1_score;

} FraudEvaluation;


FraudEvaluation evaluate_paysim_fraud(
    Transaction transactions[],
    size_t count,
    int risk_threshold
);

void print_fraud_evaluation(
    const FraudEvaluation *evaluation,
    int risk_threshold
);

#endif
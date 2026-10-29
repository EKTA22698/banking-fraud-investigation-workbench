#ifndef TRANSACTION_H
#define TRANSACTION_H

#define ID_LENGTH 32
#define TYPE_LENGTH 30
#define TIMESTAMP_LENGTH 30
#define DESCRIPTION_LENGTH 100

typedef struct
{
    /*
     * Existing internal/workbench fields.
     */
    char transaction_id[ID_LENGTH];
    char account_id[ID_LENGTH];
    char device_id[ID_LENGTH];
    char merchant_id[ID_LENGTH];

    double amount;

    char transaction_type[TYPE_LENGTH];
    char timestamp[TIMESTAMP_LENGTH];
    char description[DESCRIPTION_LENGTH];

    int risk_score;

    /*
     * PaySim-specific fields.
     */
    int step;

    char destination_id[ID_LENGTH];

    double old_balance_origin;
    double new_balance_origin;

    double old_balance_destination;
    double new_balance_destination;

    int actual_fraud;
    int flagged_fraud;

} Transaction;

void print_transaction(
    const Transaction *transaction
);

#endif
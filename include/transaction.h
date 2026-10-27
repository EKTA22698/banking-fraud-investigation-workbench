#ifndef TRANSACTION_H
#define TRANSACTION_H

#define ID_LENGTH 20
#define TYPE_LENGTH 30
#define TIMESTAMP_LENGTH 30
#define DESCRIPTION_LENGTH 100

typedef struct
{
    char transaction_id[ID_LENGTH];
    char account_id[ID_LENGTH];
    char device_id[ID_LENGTH];
    char merchant_id[ID_LENGTH];

    double amount;

    char transaction_type[TYPE_LENGTH];
    char timestamp[TIMESTAMP_LENGTH];
    char description[DESCRIPTION_LENGTH];

    int risk_score;

} Transaction;

void print_transaction(const Transaction *transaction);

#endif
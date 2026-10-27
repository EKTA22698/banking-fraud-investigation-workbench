#include <stdio.h>
#include "transaction.h"

void print_transaction(const Transaction *transaction)
{
    if (transaction == NULL)
    {
        printf("Invalid transaction.\n");
        return;
    }

    printf("\n----------------------------------------\n");
    printf("Transaction ID : %s\n", transaction->transaction_id);
    printf("Account ID     : %s\n", transaction->account_id);
    printf("Device ID      : %s\n", transaction->device_id);
    printf("Merchant ID    : %s\n", transaction->merchant_id);
    printf("Amount         : %.2f\n", transaction->amount);
    printf("Type           : %s\n", transaction->transaction_type);
    printf("Timestamp      : %s\n", transaction->timestamp);
    printf("Description    : %s\n", transaction->description);
    printf("Risk Score     : %d\n", transaction->risk_score);
    printf("----------------------------------------\n");
}
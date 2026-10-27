#include <stdio.h>
#include "dataset.h"

int load_transactions_csv(
    const char *filename,
    Transaction transactions[],
    int max_transactions
)
{
    FILE *file;
    char line[512];

    int count = 0;
    int invalid_count = 0;
    printf("DEBUG: Opening file: %s\n", filename);
    file = fopen(filename, "r");

if (file == NULL)
{
    printf("\nERROR: Could not open dataset.\n");
    printf("File: %s\n", filename);
    return -1;
}

printf("DEBUG: File opened successfully.\n");


    /* Read and skip CSV header */
    if (fgets(line, sizeof(line), file) == NULL)
    {
        printf("\nERROR: Dataset is empty.\n");
        fclose(file);
        return -1;
    }

    while (fgets(line, sizeof(line), file) != NULL &&
           count < max_transactions)
    {
        Transaction *transaction = &transactions[count];

        int fields_read = sscanf(
            line,
            "%19[^,],%19[^,],%19[^,],%19[^,],%lf,%29[^,],%29[^,],%99[^\r\n]",
            transaction->transaction_id,
            transaction->account_id,
            transaction->device_id,
            transaction->merchant_id,
            &transaction->amount,
            transaction->transaction_type,
            transaction->timestamp,
            transaction->description
        );

        if (fields_read == 8)
        {
            transaction->risk_score = 0;
            count++;
        }
        else
        {
            invalid_count++;
        }
    }

    fclose(file);

    printf("\nDataset validation complete.\n");
    printf("Valid records   : %d\n", count);
    printf("Invalid records : %d\n", invalid_count);

    return count;
}


void print_dataset_summary(
    const Transaction transactions[],
    int transaction_count
)
{
    double total_amount = 0.0;
    double highest_amount = 0.0;

    int i;

    if (transaction_count <= 0)
    {
        printf("\nNo dataset is currently loaded.\n");
        return;
    }

    for (i = 0; i < transaction_count; i++)
    {
        total_amount += transactions[i].amount;

        if (transactions[i].amount > highest_amount)
        {
            highest_amount = transactions[i].amount;
        }
    }

    printf("\n============================================================\n");
    printf("                    DATASET SUMMARY\n");
    printf("============================================================\n");

    printf("Transactions loaded : %d\n", transaction_count);
    printf("Total amount        : %.2f\n", total_amount);
    printf("Average amount      : %.2f\n",
           total_amount / transaction_count);
    printf("Highest transaction : %.2f\n", highest_amount);

    printf("============================================================\n");
}
void print_all_transactions(
    const Transaction transactions[],
    int transaction_count
)
{
    int i;

    if (transaction_count <= 0)
    {
        printf("\nNo dataset is currently loaded.\n");
        printf("Please load a dataset first.\n");
        return;
    }

    printf("\n");
    printf("====================================================================================================\n");
    printf("                                  LOADED TRANSACTIONS\n");
    printf("====================================================================================================\n");

    printf("%-8s %-10s %-8s %-10s %-12s %-12s %-18s\n",
           "TXN ID",
           "ACCOUNT",
           "DEVICE",
           "MERCHANT",
           "AMOUNT",
           "TYPE",
           "TIMESTAMP");

    printf("----------------------------------------------------------------------------------------------------\n");

    for (i = 0; i < transaction_count; i++)
    {
        printf("%-8s %-10s %-8s %-10s %12.2f %-12s %-18s\n",
               transactions[i].transaction_id,
               transactions[i].account_id,
               transactions[i].device_id,
               transactions[i].merchant_id,
               transactions[i].amount,
               transactions[i].transaction_type,
               transactions[i].timestamp);
    }

    printf("====================================================================================================\n");
    printf("Total transactions: %d\n", transaction_count);
}
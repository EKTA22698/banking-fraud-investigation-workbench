#include <stdio.h>

#include "transaction.h"


void print_transaction(
    const Transaction *transaction
)
{
    if (transaction == NULL)
    {
        printf("Invalid transaction.\n");
        return;
    }

    printf(
        "Transaction ID      : %s\n",
        transaction->transaction_id
    );

    printf(
        "Origin Account      : %s\n",
        transaction->account_id
    );

    /*
     * PaySim transaction.
     *
     * PaySim has destination accounts and
     * balance information but no equivalent
     * device/merchant fields.
     */
    if (
        transaction->destination_id[0] != '\0'
    )
    {
        printf(
            "Destination Account : %s\n",
            transaction->destination_id
        );

        printf(
            "Transaction Type    : %s\n",
            transaction->transaction_type
        );

        printf(
            "Amount              : %.2f\n",
            transaction->amount
        );

        printf(
            "Simulation Step     : %d\n",
            transaction->step
        );

        printf(
            "Origin Balance      : %.2f -> %.2f\n",
            transaction->old_balance_origin,
            transaction->new_balance_origin
        );

        printf(
            "Destination Balance : %.2f -> %.2f\n",
            transaction->old_balance_destination,
            transaction->new_balance_destination
        );

        printf(
            "Actual Fraud        : %s\n",
            transaction->actual_fraud ?
            "YES" :
            "NO"
        );

        printf(
            "PaySim Flagged      : %s\n",
            transaction->flagged_fraud ?
            "YES" :
            "NO"
        );

        printf(
            "Workbench Risk Score: %d\n",
            transaction->risk_score
        );
    }

    /*
     * Original/synthetic workbench dataset.
     */
    else
    {
        printf(
            "Device ID           : %s\n",
            transaction->device_id
        );

        printf(
            "Merchant ID         : %s\n",
            transaction->merchant_id
        );

        printf(
            "Transaction Type    : %s\n",
            transaction->transaction_type
        );

        printf(
            "Amount              : %.2f\n",
            transaction->amount
        );

        printf(
            "Timestamp           : %s\n",
            transaction->timestamp
        );

        printf(
            "Description         : %s\n",
            transaction->description
        );

        printf(
            "Risk Score          : %d\n",
            transaction->risk_score
        );
    }
}
#include <stdio.h>
#include <string.h>

#include "dataset.h"
#include "transaction.h"


int load_paysim_csv(
    const char *filename,
    Transaction transactions[],
    int max_transactions
)
{
    FILE *file;

    char line[1024];

    int count = 0;
    int invalid_count = 0;


    file = fopen(
        filename,
        "r"
    );


    if (file == NULL)
    {
        printf(
            "\nERROR: Could not open PaySim dataset.\n"
        );

        printf(
            "File: %s\n",
            filename
        );

        return -1;
    }


    /*
     * Skip CSV header.
     */
    if (
        fgets(
            line,
            sizeof(line),
            file
        ) == NULL
    )
    {
        printf(
            "\nERROR: PaySim dataset is empty.\n"
        );

        fclose(file);

        return -1;
    }


    while (
        fgets(
            line,
            sizeof(line),
            file
        ) != NULL &&
        count < max_transactions
    )
    {
        Transaction *transaction =
            &transactions[count];


        char type[
            TYPE_LENGTH
        ];

        char origin[
            ID_LENGTH
        ];

        char destination[
            ID_LENGTH
        ];


        int fields_read =
            sscanf(
                line,

                "%d,"
                "%29[^,],"
                "%lf,"
                "%31[^,],"
                "%lf,"
                "%lf,"
                "%31[^,],"
                "%lf,"
                "%lf,"
                "%d,"
                "%d",

                &transaction->step,

                type,

                &transaction->amount,

                origin,

                &transaction
                    ->old_balance_origin,

                &transaction
                    ->new_balance_origin,

                destination,

                &transaction
                    ->old_balance_destination,

                &transaction
                    ->new_balance_destination,

                &transaction
                    ->actual_fraud,

                &transaction
                    ->flagged_fraud
            );


        if (fields_read == 11)
        {
            /*
             * Generate our own stable
             * transaction ID because
             * PaySim does not provide one.
             */
            snprintf(
                transaction->transaction_id,
                ID_LENGTH,
                "P%07d",
                count + 1
            );


            /*
             * PaySim origin account.
             */
            snprintf(
                transaction->account_id,
                ID_LENGTH,
                "%s",
                origin
            );


            /*
             * PaySim destination account.
             */
            snprintf(
                transaction->destination_id,
                ID_LENGTH,
                "%s",
                destination
            );


            /*
             * Keep transaction type compatible
             * with existing workbench algorithms.
             */
            snprintf(
                transaction->transaction_type,
                TYPE_LENGTH,
                "%s",
                type
            );


            /*
             * PaySim has no device/merchant
             * fields equivalent to our original
             * synthetic schema.
             *
             * Do NOT invent them.
             */
            transaction->device_id[0] =
                '\0';

            transaction->merchant_id[0] =
                '\0';


            /*
             * PaySim uses simulation steps
             * instead of real timestamps.
             */
            snprintf(
                transaction->timestamp,
                TIMESTAMP_LENGTH,
                "STEP-%d",
                transaction->step
            );


            snprintf(
                transaction->description,
                DESCRIPTION_LENGTH,
                "PaySim %s transaction",
                type
            );


            /*
             * Our model/heuristic prediction
             * remains separate from ground truth.
             */
            transaction->risk_score = 0;


            count++;
        }
        else
        {
            invalid_count++;
        }
    }


    fclose(file);


    printf("\n");
    printf(
        "PaySim dataset validation complete.\n"
    );

    printf(
        "Valid records   : %d\n",
        count
    );

    printf(
        "Invalid records : %d\n",
        invalid_count
    );


    if (count == max_transactions)
    {
        printf(
            "Loader limit reached: %d records.\n",
            max_transactions
        );
    }


    return count;
}
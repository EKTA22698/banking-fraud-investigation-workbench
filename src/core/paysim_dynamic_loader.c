#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataset.h"
#include "transaction.h"

#define INITIAL_DATASET_CAPACITY 10000


static int grow_dataset(
    TransactionDataset *dataset
)
{
    size_t new_capacity;

    if (dataset == NULL)
    {
        return 0;
    }

    if (dataset->capacity == 0)
    {
        new_capacity =
            INITIAL_DATASET_CAPACITY;
    }
    else
    {
        new_capacity =
            dataset->capacity * 2;
    }


    /*
     * Protect against size_t overflow.
     */
    if (
        new_capacity <
        dataset->capacity ||
        new_capacity >
        SIZE_MAX / sizeof(Transaction)
    )
    {
        return 0;
    }


    Transaction *new_items =
        realloc(
            dataset->items,
            new_capacity *
            sizeof(Transaction)
        );


    if (new_items == NULL)
    {
        return 0;
    }


    dataset->items =
        new_items;

    dataset->capacity =
        new_capacity;

    return 1;
}


int load_paysim_dynamic(
    const char *filename,
    TransactionDataset *dataset
)
{
    if (
        filename == NULL ||
        dataset == NULL
    )
    {
        return 0;
    }


    /*
     * Start with an empty dataset.
     */
    dataset->items = NULL;
    dataset->count = 0;
    dataset->capacity = 0;


    FILE *file =
        fopen(
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

        return 0;
    }


    char line[1024];


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

        return 0;
    }


    size_t invalid_count = 0;


    while (
        fgets(
            line,
            sizeof(line),
            file
        ) != NULL
    )
    {
        /*
         * Grow storage only when full.
         */
        if (
            dataset->count ==
            dataset->capacity
        )
        {
            if (
                !grow_dataset(
                    dataset
                )
            )
            {
                printf(
                    "\nERROR: Unable to allocate "
                    "more memory for PaySim.\n"
                );

                fclose(file);

                free_transaction_dataset(
                    dataset
                );

                return 0;
            }
        }


        Transaction *transaction =
            &dataset->items[
                dataset->count
            ];


        /*
         * Initialize all fields because
         * Transaction also contains fields
         * not directly supplied by PaySim.
         */
        memset(
            transaction,
            0,
            sizeof(Transaction)
        );


        char type[
            TYPE_LENGTH
        ];

        char origin[
            ID_LENGTH
        ];

        char destination[
            ID_LENGTH
        ];


        /*
         * PaySim columns:
         *
         * step
         * type
         * amount
         * nameOrig
         * oldbalanceOrg
         * newbalanceOrig
         * nameDest
         * oldbalanceDest
         * newbalanceDest
         * isFraud
         * isFlaggedFraud
         */
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


        if (fields_read != 11)
        {
            invalid_count++;
            continue;
        }


        /*
         * PaySim does not provide a transaction
         * ID, so generate a stable workbench ID.
         */
        snprintf(
            transaction->transaction_id,
            ID_LENGTH,
            "P%07zu",
            dataset->count + 1
        );


        /*
         * Origin account.
         */
        snprintf(
            transaction->account_id,
            ID_LENGTH,
            "%s",
            origin
        );


        /*
         * Destination account.
         */
        snprintf(
            transaction->destination_id,
            ID_LENGTH,
            "%s",
            destination
        );


        /*
         * Transaction type.
         */
        snprintf(
            transaction->transaction_type,
            TYPE_LENGTH,
            "%s",
            type
        );


        /*
         * PaySim uses simulation steps instead
         * of real timestamps.
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
         * Workbench prediction is calculated
         * later by the fraud engine.
         */
        transaction->risk_score = 0;


        dataset->count++;


        /*
         * Progress feedback for millions
         * of transactions.
         */
        if (
            dataset->count %
            500000 == 0
        )
        {
            printf(
                "Loaded %zu transactions...\n",
                dataset->count
            );
        }
    }


    /*
     * File reading is complete.
     */
    fclose(file);


    /*
     * Shrink the oversized doubling allocation
     * to exactly the number of valid records.
     *
     * Example:
     *
     * capacity before = 10,240,000
     * actual records  =  6,362,620
     *
     * capacity after  =  6,362,620
     */
    if (
        dataset->count > 0 &&
        dataset->capacity >
            dataset->count
    )
    {
        Transaction *shrunk_items =
            realloc(
                dataset->items,
                dataset->count *
                sizeof(Transaction)
            );


        /*
         * realloc failure while SHRINKING is
         * not fatal. The original allocation
         * remains valid.
         */
        if (shrunk_items != NULL)
        {
            dataset->items =
                shrunk_items;

            dataset->capacity =
                dataset->count;
        }
    }


    printf("\n");
    printf(
        "PaySim dynamic loading complete.\n"
    );

    printf(
        "Valid records      : %zu\n",
        dataset->count
    );

    printf(
        "Invalid records    : %zu\n",
        invalid_count
    );

    printf(
        "Allocated capacity : %zu transactions\n",
        dataset->capacity
    );


    return 1;
}


void free_transaction_dataset(
    TransactionDataset *dataset
)
{
    if (dataset == NULL)
    {
        return;
    }


    free(
        dataset->items
    );


    dataset->items = NULL;
    dataset->count = 0;
    dataset->capacity = 0;
}
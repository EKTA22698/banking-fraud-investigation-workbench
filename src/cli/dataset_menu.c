#include <stdio.h>

#include "dataset_menu.h"
#include "dataset.h"


void run_dataset_menu(
    ApplicationState *state
)
{
    if (state == NULL)
    {
        return;
    }

    int dataset_choice;

    const char *filename = NULL;
    const char *dataset_name = NULL;

    printf("\n");
    printf("============================================================\n");
    printf("                     DATASET LOADER\n");
    printf("============================================================\n");

    printf("1. Small Dataset       (10 transactions)\n");
    printf("2. Medium Dataset      (1,000 transactions)\n");
    printf("3. Capacity Shock      (1,000 transactions)\n");
    printf("4. Large Dataset       (10,000 transactions)\n");
    printf("5. Adversarial Dataset (10,000 transactions)\n");
    printf("6. PaySim Public Fraud Dataset (Full)\n");
    printf("0. Back\n");

    printf("============================================================\n");
    printf("Select dataset: ");

    if (
        scanf(
            "%d",
            &dataset_choice
        ) != 1
    )
    {
        printf("Invalid input.\n");

        while (getchar() != '\n')
        {
        }

        return;
    }


    if (dataset_choice == 0)
    {
        return;
    }


    /*
     * ------------------------------------------------
     * PAYSIM DYNAMIC DATASET
     * ------------------------------------------------
     */
    if (dataset_choice == 6)
    {
        filename =
            "data/raw/PS_20174392719_1491204439457_log.csv";

        dataset_name =
            "PaySim Public Fraud Dataset";


        /*
         * Release an older PaySim dataset before
         * loading it again.
         */
        if (state->using_dynamic_dataset)
        {
            free_transaction_dataset(
                &state->paysim_dataset
            );

            state->using_dynamic_dataset = 0;
        }


        printf(
            "\nLoading full PaySim dataset dynamically...\n"
        );


        if (
            !load_paysim_dynamic(
                filename,
                &state->paysim_dataset
            )
        )
        {
            printf(
                "\nERROR: PaySim dataset loading failed.\n"
            );

            /*
             * Fall back to no active dataset rather
             * than leaving a dangling PaySim pointer.
             */
            state->active_transactions =
                state->transactions;

            state->active_count = 0;

            return;
        }


        state->using_dynamic_dataset = 1;

        state->active_transactions =
            state->paysim_dataset.items;

        state->active_count =
            state->paysim_dataset.count;


        printf(
            "\nFull PaySim dataset loaded successfully.\n"
        );

        printf(
            "Scenario: %s\n",
            dataset_name
        );

        printf(
            "Source  : %s\n",
            filename
        );

        printf(
            "Transactions loaded: %zu\n",
            state->active_count
        );

        printf(
            "Allocated capacity : %zu\n",
            state->paysim_dataset.capacity
        );

        return;
    }


    /*
     * ------------------------------------------------
     * FIXED / SYNTHETIC DATASETS
     * ------------------------------------------------
     */

    if (dataset_choice == 1)
    {
        filename =
            "data/small/transactions_small.csv";

        dataset_name =
            "Small / Normal Operation";
    }

    else if (dataset_choice == 2)
    {
        filename =
            "data/medium/transactions_medium.csv";

        dataset_name =
            "Medium";
    }

    else if (dataset_choice == 3)
    {
        filename =
            "data/medium/transactions_shock.csv";

        dataset_name =
            "Capacity / Constraint Shock";
    }

    else if (dataset_choice == 4)
    {
        filename =
            "data/large/transactions_large.csv";

        dataset_name =
            "Large Data Stress";
    }

    else if (dataset_choice == 5)
    {
        filename =
            "data/adversarial/transactions_adversarial.csv";

        dataset_name =
            "Adversarial";
    }

    else
    {
        printf(
            "Invalid dataset selection.\n"
        );

        return;
    }


    /*
     * If PaySim was previously active, release its
     * dynamically allocated memory before switching
     * back to fixed storage.
     */
    if (state->using_dynamic_dataset)
    {
        free_transaction_dataset(
            &state->paysim_dataset
        );

        state->using_dynamic_dataset = 0;
    }


    state->transaction_count =
        load_transactions_csv(
            filename,
            state->transactions,
            MAX_TRANSACTIONS
        );


    if (state->transaction_count < 0)
    {
        printf(
            "\nERROR: Dataset loading failed.\n"
        );

        state->transaction_count = 0;
        state->active_transactions =
            state->transactions;
        state->active_count = 0;

        return;
    }


    state->active_transactions =
        state->transactions;

    state->active_count =
        (size_t)state->transaction_count;


    printf(
        "\nDataset loaded successfully.\n"
    );

    printf(
        "Scenario: %s\n",
        dataset_name
    );

    printf(
        "Source  : %s\n",
        filename
    );


    print_dataset_summary(
        state->active_transactions,
        state->active_count
    );
}
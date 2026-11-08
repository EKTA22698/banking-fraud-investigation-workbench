#include <stdio.h>
#include <stdlib.h>

#include "app_state.h"
#include "dataset.h"


int initialize_application_state(
    ApplicationState *state
)
{
    if (state == NULL)
    {
        return 0;
    }


    state->transactions =
        malloc(
            MAX_TRANSACTIONS *
            sizeof(Transaction)
        );


    if (state->transactions == NULL)
    {
        printf(
            "ERROR: Unable to allocate "
            "transaction storage.\n"
        );

        return 0;
    }


    state->transaction_count = 0;


    state->paysim_dataset.items = NULL;
    state->paysim_dataset.count = 0;
    state->paysim_dataset.capacity = 0;


    state->using_dynamic_dataset = 0;


    state->active_transactions =
        state->transactions;

    state->active_count = 0;


    return 1;
}


void cleanup_application_state(
    ApplicationState *state
)
{
    if (state == NULL)
    {
        return;
    }


    if (state->using_dynamic_dataset)
    {
        free_transaction_dataset(
            &state->paysim_dataset
        );
    }


    free(
        state->transactions
    );


    state->transactions = NULL;
    state->transaction_count = 0;

    state->active_transactions = NULL;
    state->active_count = 0;

    state->using_dynamic_dataset = 0;
}
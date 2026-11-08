#ifndef APP_STATE_H
#define APP_STATE_H

#include <stddef.h>

#include "transaction.h"
#include "dataset.h"

typedef struct
{
    /*
     * Original fixed-size dataset storage.
     */
    Transaction *transactions;

    int transaction_count;


    /*
     * Dynamically allocated PaySim storage.
     */
    TransactionDataset paysim_dataset;

    int using_dynamic_dataset;


    /*
     * Dataset currently selected by the user.
     */
    Transaction *active_transactions;

    size_t active_count;

} ApplicationState;


int initialize_application_state(
    ApplicationState *state
);

void cleanup_application_state(
    ApplicationState *state
);

#endif
#ifndef FRAUD_MENU_H
#define FRAUD_MENU_H

#include <stddef.h>

#include "transaction.h"

void run_fraud_menu(
    Transaction transactions[],
    size_t transaction_count,
    int is_paysim
);

#endif
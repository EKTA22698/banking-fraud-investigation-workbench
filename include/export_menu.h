#ifndef EXPORT_MENU_H
#define EXPORT_MENU_H

#include <stddef.h>

#include "transaction.h"

void run_export_menu(
    Transaction transactions[],
    size_t transaction_count,
    int is_paysim
);

#endif
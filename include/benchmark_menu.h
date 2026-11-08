#ifndef BENCHMARK_MENU_H
#define BENCHMARK_MENU_H

#include <stddef.h>

#include "transaction.h"

void run_benchmark_menu(
    Transaction transactions[],
    size_t transaction_count,
    int is_paysim
);

#endif
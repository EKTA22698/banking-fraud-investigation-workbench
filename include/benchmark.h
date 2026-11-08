#ifndef BENCHMARK_H
#define BENCHMARK_H
#include <stddef.h>
#include "transaction.h"

void run_paysim_benchmark(
    Transaction transactions[],
    size_t count
);
void run_sorting_benchmark(void);
void run_string_matching_benchmark(void);
void run_matrix_benchmark(void);
void run_graph_benchmark(void);
void run_complete_benchmark_suite(void);

#endif
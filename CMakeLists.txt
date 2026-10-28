cmake_minimum_required(VERSION 3.16)

project(BankingFraudWorkbench LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(fraud_workbench
    src/main.c
    src/core/transaction.c
    src/core/dataset.c
    src/core/fraud.c
    src/cli/cli.c
    src/algorithms/sorting/merge_sort.c
    src/algorithms/sorting/quick_sort.c
    src/algorithms/searching/binary_search.c
    src/algorithms/divide_conquer/maximum_subarray.c
src/algorithms/divide_conquer/fast_power.c
src/algorithms/divide_conquer/celebrity.c
src/algorithms/divide_conquer/matrix_multiplication.c
src/algorithms/greedy/activity_selection.c
src/algorithms/greedy/interval_partitioning.c
src/algorithms/greedy/huffman.c
src/algorithms/graph/dijkstra.c
src/algorithms/graph/prim.c
src/algorithms/graph/kruskal.c
src/algorithms/dynamic_programming/knapsack.c
src/algorithms/dynamic_programming/matrix_chain.c
src/algorithms/dynamic_programming/lcs.c
src/algorithms/dynamic_programming/optimal_bst.c
src/algorithms/graph/bellman_ford.c
src/algorithms/graph/floyd_warshall.c
src/algorithms/dynamic_programming/tsp.c
src/algorithms/backtracking/n_queens.c
src/algorithms/backtracking/subset_sum.c
src/algorithms/branch_bound/branch_bound.c
src/algorithms/network_flow/ford_fulkerson.c
src/algorithms/network_flow/bipartite_matching.c
src/algorithms/number_theory/crt.c
src/algorithms/string_matching/naive.c
src/algorithms/string_matching/rabin_karp.c
src/algorithms/string_matching/finite_automaton.c
src/algorithms/string_matching/kmp.c
src/benchmark/benchmark.c
)

target_include_directories(fraud_workbench PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
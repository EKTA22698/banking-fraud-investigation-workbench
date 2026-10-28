#ifndef DYNAMIC_PROGRAMMING_H
#define DYNAMIC_PROGRAMMING_H

#define MAX_CASES 50
#define MAX_CAPACITY 100

typedef struct
{
    int id;
    int risk_value;
    int investigation_time;
} InvestigationCase;

typedef struct
{
    int maximum_risk;
    int selected_count;
    int selected_indices[MAX_CASES];
} KnapsackResult;


KnapsackResult solve_zero_one_knapsack(
    const InvestigationCase cases[],
    int case_count,
    int available_hours
);
#define MAX_MATRIX_CHAIN 20
#define MAX_SEQUENCE_LENGTH 100
#define MAX_OBST_KEYS 20


/* Matrix Chain Multiplication */
long long matrix_chain_min_cost(
    const int dimensions[],
    int matrix_count
);


/* Longest Common Subsequence */
int longest_common_subsequence(
    const char *first,
    const char *second,
    char result[]
);


/* Optimal Binary Search Tree */
int optimal_bst_cost(
    const int frequencies[],
    int key_count
);
#define TSP_MAX_VERTICES 10
#define TSP_INF 1000000000

typedef struct
{
    int minimum_cost;
    int path[TSP_MAX_VERTICES + 1];
    int path_length;
} TSPResult;

TSPResult solve_bounded_tsp(
    int vertex_count,
    const int graph[TSP_MAX_VERTICES][TSP_MAX_VERTICES]
);
#endif
#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#define NQUEENS_MAX_SIZE 12
#define SUBSET_MAX_SIZE 30
#define BACKTRACK_KNAPSACK_MAX_ITEMS 30

typedef struct
{
    int size;
    int positions[NQUEENS_MAX_SIZE];
    int solution_count;
} NQueensResult;

typedef struct
{
    int found;
    int selected[SUBSET_MAX_SIZE];
    int selected_count;
    int sum;
} SubsetResult;


/* N-Queens */
NQueensResult solve_n_queens(
    int board_size
);

void print_n_queens_solution(
    const NQueensResult *result
);


/* Subset Sum */
SubsetResult solve_subset_sum(
    const int values[],
    int count,
    int target
);
typedef struct
{
    int id;
    int risk_value;
    int investigation_time;
} BacktrackingKnapsackItem;


typedef struct
{
    int maximum_risk;
    int total_time;

    int selected_ids[
        BACKTRACK_KNAPSACK_MAX_ITEMS
    ];

    int selected_count;
} BacktrackingKnapsackResult;
/* 0/1 Knapsack using Backtracking */
BacktrackingKnapsackResult
solve_knapsack_backtracking(
    const BacktrackingKnapsackItem items[],
    int count,
    int capacity
);
#endif
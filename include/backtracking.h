#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#define NQUEENS_MAX_SIZE 12
#define SUBSET_MAX_SIZE 30

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

#endif
#include <stdio.h>

#include "backtracking.h"


static int is_safe(
    const int positions[],
    int row,
    int column
)
{
    for (int previous_row = 0;
         previous_row < row;
         previous_row++)
    {
        int previous_column =
            positions[previous_row];

        /*
         * Same column.
         */
        if (previous_column == column)
        {
            return 0;
        }

        /*
         * Same diagonal.
         */
        int row_difference =
            row - previous_row;

        int column_difference =
            column - previous_column;

        if (column_difference < 0)
        {
            column_difference =
                -column_difference;
        }

        if (
            row_difference ==
            column_difference
        )
        {
            return 0;
        }
    }

    return 1;
}


static void solve_recursive(
    int board_size,
    int row,
    int positions[],
    NQueensResult *result
)
{
    /*
     * All queens successfully placed.
     */
    if (row == board_size)
    {
        result->solution_count++;

        /*
         * Save the first valid solution
         * for display.
         */
        if (result->solution_count == 1)
        {
            for (int i = 0;
                 i < board_size;
                 i++)
            {
                result->positions[i] =
                    positions[i];
            }
        }

        return;
    }

    /*
     * Try every column in this row.
     */
    for (int column = 0;
         column < board_size;
         column++)
    {
        if (
            is_safe(
                positions,
                row,
                column
            )
        )
        {
            /*
             * Choose.
             */
            positions[row] =
                column;

            /*
             * Explore.
             */
            solve_recursive(
                board_size,
                row + 1,
                positions,
                result
            );

            /*
             * Backtracking happens
             * naturally when we return
             * and try another column.
             */
        }
    }
}


NQueensResult solve_n_queens(
    int board_size
)
{
    NQueensResult result;

    result.size = board_size;
    result.solution_count = 0;

    for (int i = 0;
         i < NQUEENS_MAX_SIZE;
         i++)
    {
        result.positions[i] = -1;
    }

    if (
        board_size <= 0 ||
        board_size > NQUEENS_MAX_SIZE
    )
    {
        result.size = 0;
        return result;
    }

    int positions[NQUEENS_MAX_SIZE];

    for (int i = 0;
         i < NQUEENS_MAX_SIZE;
         i++)
    {
        positions[i] = -1;
    }

    solve_recursive(
        board_size,
        0,
        positions,
        &result
    );

    return result;
}


void print_n_queens_solution(
    const NQueensResult *result
)
{
    if (
        result == NULL ||
        result->size <= 0
    )
    {
        printf(
            "Invalid N-Queens result.\n"
        );

        return;
    }

    if (result->solution_count == 0)
    {
        printf(
            "No solution exists.\n"
        );

        return;
    }

    printf("\nFirst Valid Solution\n");
    printf("------------------------------\n");

    for (int row = 0;
         row < result->size;
         row++)
    {
        for (int column = 0;
             column < result->size;
             column++)
        {
            if (
                result->positions[row] ==
                column
            )
            {
                printf(" Q ");
            }
            else
            {
                printf(" . ");
            }
        }

        printf("\n");
    }

    printf("------------------------------\n");

    printf(
        "Total solutions: %d\n",
        result->solution_count
    );
}
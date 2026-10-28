#include <stdio.h>
#include <string.h>

#include "matrix_algorithms.h"

void classical_matrix_multiply(
    int size,
    const int A[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    const int B[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    int C[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE]
)
{
    int i;
    int j;
    int k;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            C[i][j] = 0;

            for (k = 0; k < size; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
static void strassen_2x2(
    const int A[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    const int B[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    int C[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE]
)
{
    int m1;
    int m2;
    int m3;
    int m4;
    int m5;
    int m6;
    int m7;

    m1 = (A[0][0] + A[1][1]) *
         (B[0][0] + B[1][1]);

    m2 = (A[1][0] + A[1][1]) *
         B[0][0];

    m3 = A[0][0] *
         (B[0][1] - B[1][1]);

    m4 = A[1][1] *
         (B[1][0] - B[0][0]);

    m5 = (A[0][0] + A[0][1]) *
         B[1][1];

    m6 = (A[1][0] - A[0][0]) *
         (B[0][0] + B[0][1]);

    m7 = (A[0][1] - A[1][1]) *
         (B[1][0] + B[1][1]);

    C[0][0] = m1 + m4 - m5 + m7;
    C[0][1] = m3 + m5;
    C[1][0] = m2 + m4;
    C[1][1] = m1 - m2 + m3 + m6;
}


void strassen_matrix_multiply(
    int size,
    const int A[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    const int B[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    int C[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE]
)
{
    memset(
        C,
        0,
        sizeof(int) *
        MATRIX_MAX_SIZE *
        MATRIX_MAX_SIZE
    );

    /*
     * Initial syllabus demonstration:
     * Strassen's seven-product method for 2x2 matrices.
     */
    if (size == 2)
    {
        strassen_2x2(A, B, C);
        return;
    }

    /*
     * Temporary safe fallback for other sizes.
     * Full recursive Strassen will be used in benchmarks.
     */
    classical_matrix_multiply(
        size,
        A,
        B,
        C
    );
}
void print_matrix(
    int size,
    const int matrix[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE]
)
{
    int i;
    int j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            printf("%6d", matrix[i][j]);
        }

        printf("\n");
    }
}
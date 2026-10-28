#include <stdio.h>

#include "matrix_algorithms.h"


/*
 * Classical matrix multiplication.
 *
 * Time complexity:
 * O(n^3)
 */
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
                C[i][j] +=
                    A[i][k] * B[k][j];
            }
        }
    }
}


/*
 * Add two square matrices.
 */
static void add_matrix(
    int size,
    int A[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    int B[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    int result[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE]
)
{
    int i;
    int j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            result[i][j] =
                A[i][j] + B[i][j];
        }
    }
}


/*
 * Subtract matrix B from matrix A.
 */
static void subtract_matrix(
    int size,
    int A[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    int B[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    int result[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE]
)
{
    int i;
    int j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            result[i][j] =
                A[i][j] - B[i][j];
        }
    }
}


/*
 * Recursive Strassen implementation.
 *
 * Supported sizes:
 * 1, 2, 4, 8
 *
 * Time complexity:
 * O(n ^ log2(7))
 * approximately O(n^2.807)
 */
static void strassen_recursive(
    int size,
    int A[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    int B[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    int C[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE]
)
{
    int i;
    int j;

    /*
     * Base case:
     * multiplication of two 1 x 1 matrices.
     */
    if (size == 1)
    {
        C[0][0] =
            A[0][0] * B[0][0];

        return;
    }

    int half = size / 2;

    /*
     * Divide A into:
     *
     * A11 A12
     * A21 A22
     */
    int A11[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};
    int A12[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};
    int A21[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};
    int A22[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};

    /*
     * Divide B into:
     *
     * B11 B12
     * B21 B22
     */
    int B11[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};
    int B12[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};
    int B21[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};
    int B22[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};

    for (i = 0; i < half; i++)
    {
        for (j = 0; j < half; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    /*
     * Strassen requires only seven
     * recursive matrix multiplications.
     */
    int M1[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};
    int M2[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};
    int M3[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};
    int M4[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};
    int M5[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};
    int M6[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};
    int M7[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};

    int temp1[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};
    int temp2[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};


    /*
     * M1 = (A11 + A22)(B11 + B22)
     */
    add_matrix(
        half,
        A11,
        A22,
        temp1
    );

    add_matrix(
        half,
        B11,
        B22,
        temp2
    );

    strassen_recursive(
        half,
        temp1,
        temp2,
        M1
    );


    /*
     * M2 = (A21 + A22)B11
     */
    add_matrix(
        half,
        A21,
        A22,
        temp1
    );

    strassen_recursive(
        half,
        temp1,
        B11,
        M2
    );


    /*
     * M3 = A11(B12 - B22)
     */
    subtract_matrix(
        half,
        B12,
        B22,
        temp2
    );

    strassen_recursive(
        half,
        A11,
        temp2,
        M3
    );


    /*
     * M4 = A22(B21 - B11)
     */
    subtract_matrix(
        half,
        B21,
        B11,
        temp2
    );

    strassen_recursive(
        half,
        A22,
        temp2,
        M4
    );


    /*
     * M5 = (A11 + A12)B22
     */
    add_matrix(
        half,
        A11,
        A12,
        temp1
    );

    strassen_recursive(
        half,
        temp1,
        B22,
        M5
    );


    /*
     * M6 = (A21 - A11)(B11 + B12)
     */
    subtract_matrix(
        half,
        A21,
        A11,
        temp1
    );

    add_matrix(
        half,
        B11,
        B12,
        temp2
    );

    strassen_recursive(
        half,
        temp1,
        temp2,
        M6
    );


    /*
     * M7 = (A12 - A22)(B21 + B22)
     */
    subtract_matrix(
        half,
        A12,
        A22,
        temp1
    );

    add_matrix(
        half,
        B21,
        B22,
        temp2
    );

    strassen_recursive(
        half,
        temp1,
        temp2,
        M7
    );


    /*
     * Result quadrants:
     *
     * C11 = M1 + M4 - M5 + M7
     * C12 = M3 + M5
     * C21 = M2 + M4
     * C22 = M1 - M2 + M3 + M6
     */

    for (i = 0; i < half; i++)
    {
        for (j = 0; j < half; j++)
        {
            C[i][j] =
                M1[i][j] +
                M4[i][j] -
                M5[i][j] +
                M7[i][j];

            C[i][j + half] =
                M3[i][j] +
                M5[i][j];

            C[i + half][j] =
                M2[i][j] +
                M4[i][j];

            C[i + half][j + half] =
                M1[i][j] -
                M2[i][j] +
                M3[i][j] +
                M6[i][j];
        }
    }
}


/*
 * Public Strassen function.
 */
void strassen_matrix_multiply(
    int size,
    const int A[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    const int B[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    int C[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE]
)
{
    int local_A[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};
    int local_B[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE] = {0};

    int i;
    int j;

    if (
        size != 1 &&
        size != 2 &&
        size != 4 &&
        size != 8
    )
    {
        printf(
            "ERROR: Strassen requires a "
            "power-of-two matrix size.\n"
        );

        return;
    }

    /*
     * Copy const input matrices into
     * local working matrices.
     */
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            local_A[i][j] = A[i][j];
            local_B[i][j] = B[i][j];
            C[i][j] = 0;
        }
    }

    strassen_recursive(
        size,
        local_A,
        local_B,
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
            printf(
                "%8d",
                matrix[i][j]
            );
        }

        printf("\n");
    }
}


int matrices_equal(
    int size,
    const int A[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    const int B[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE]
)
{
    int i;
    int j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (A[i][j] != B[i][j])
            {
                return 0;
            }
        }
    }

    return 1;
}
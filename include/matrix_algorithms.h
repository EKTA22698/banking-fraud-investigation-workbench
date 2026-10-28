#ifndef MATRIX_ALGORITHMS_H
#define MATRIX_ALGORITHMS_H

#define MATRIX_MAX_SIZE 8

void classical_matrix_multiply(
    int size,
    const int A[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    const int B[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    int C[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE]
);

void strassen_matrix_multiply(
    int size,
    const int A[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    const int B[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
    int C[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE]
);

void print_matrix(
    int size,
    const int matrix[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE]
);

#endif
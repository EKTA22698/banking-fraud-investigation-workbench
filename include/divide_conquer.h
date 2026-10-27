#ifndef DIVIDE_CONQUER_H
#define DIVIDE_CONQUER_H

typedef struct
{
    int left;
    int right;
    double sum;
} MaxSubarrayResult;

MaxSubarrayResult maximum_subarray(
    const double values[],
    int count
);

long long fast_power(
    long long base,
    unsigned int exponent
);

int find_celebrity(
    const int matrix[][10],
    int count
);

#endif
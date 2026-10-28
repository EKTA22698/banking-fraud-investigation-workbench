#include "dynamic_programming.h"


long long matrix_chain_min_cost(
    const int dimensions[],
    int matrix_count
)
{
    long long dp
        [MAX_MATRIX_CHAIN]
        [MAX_MATRIX_CHAIN] = {0};

    int chain_length;
    int i;
    int j;
    int k;

    if (
        dimensions == 0 ||
        matrix_count <= 0 ||
        matrix_count >= MAX_MATRIX_CHAIN
    )
    {
        return -1;
    }

    /*
     * One matrix requires no multiplication.
     */
    for (i = 0; i < matrix_count; i++)
    {
        dp[i][i] = 0;
    }

    /*
     * Build solutions for increasingly
     * larger matrix chains.
     */
    for (
        chain_length = 2;
        chain_length <= matrix_count;
        chain_length++
    )
    {
        for (
            i = 0;
            i <= matrix_count - chain_length;
            i++
        )
        {
            j = i + chain_length - 1;

            dp[i][j] = 9223372036854775807LL;

            for (k = i; k < j; k++)
            {
                long long cost =
                    dp[i][k] +
                    dp[k + 1][j] +
                    (long long)dimensions[i] *
                    dimensions[k + 1] *
                    dimensions[j + 1];

                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                }
            }
        }
    }

    return dp[0][matrix_count - 1];
}
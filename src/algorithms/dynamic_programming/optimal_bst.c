#include "dynamic_programming.h"


static int frequency_sum(
    const int frequencies[],
    int left,
    int right
)
{
    int sum = 0;

    for (int i = left; i <= right; i++)
    {
        sum += frequencies[i];
    }

    return sum;
}


int optimal_bst_cost(
    const int frequencies[],
    int key_count
)
{
    int dp
        [MAX_OBST_KEYS]
        [MAX_OBST_KEYS] = {0};

    int length;
    int left;
    int right;
    int root;

    if (
        frequencies == 0 ||
        key_count <= 0 ||
        key_count > MAX_OBST_KEYS
    )
    {
        return -1;
    }

    /*
     * One key:
     * search cost equals its frequency.
     */
    for (left = 0; left < key_count; left++)
    {
        dp[left][left] =
            frequencies[left];
    }

    for (
        length = 2;
        length <= key_count;
        length++
    )
    {
        for (
            left = 0;
            left <= key_count - length;
            left++
        )
        {
            right =
                left + length - 1;

            dp[left][right] =
                2147483647;

            int total_frequency =
                frequency_sum(
                    frequencies,
                    left,
                    right
                );

            /*
             * Try every key as root.
             */
            for (
                root = left;
                root <= right;
                root++
            )
            {
                int left_cost = 0;
                int right_cost = 0;

                if (root > left)
                {
                    left_cost =
                        dp[left][root - 1];
                }

                if (root < right)
                {
                    right_cost =
                        dp[root + 1][right];
                }

                int cost =
                    left_cost +
                    right_cost +
                    total_frequency;

                if (
                    cost <
                    dp[left][right]
                )
                {
                    dp[left][right] =
                        cost;
                }
            }
        }
    }

    return dp[0][key_count - 1];
}
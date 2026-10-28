#include <string.h>

#include "dynamic_programming.h"


int longest_common_subsequence(
    const char *first,
    const char *second,
    char result[]
)
{
    int dp
        [MAX_SEQUENCE_LENGTH + 1]
        [MAX_SEQUENCE_LENGTH + 1] = {0};

    int first_length;
    int second_length;

    int i;
    int j;

    if (
        first == 0 ||
        second == 0 ||
        result == 0
    )
    {
        return 0;
    }

    first_length =
        (int)strlen(first);

    second_length =
        (int)strlen(second);

    if (
        first_length > MAX_SEQUENCE_LENGTH ||
        second_length > MAX_SEQUENCE_LENGTH
    )
    {
        result[0] = '\0';
        return 0;
    }

    /*
     * Build LCS length table.
     */
    for (i = 1; i <= first_length; i++)
    {
        for (j = 1; j <= second_length; j++)
        {
            if (
                first[i - 1] ==
                second[j - 1]
            )
            {
                dp[i][j] =
                    dp[i - 1][j - 1] + 1;
            }
            else
            {
                if (
                    dp[i - 1][j] >
                    dp[i][j - 1]
                )
                {
                    dp[i][j] =
                        dp[i - 1][j];
                }
                else
                {
                    dp[i][j] =
                        dp[i][j - 1];
                }
            }
        }
    }

    /*
     * Reconstruct actual subsequence.
     */
    int length =
        dp[first_length][second_length];

    result[length] = '\0';

    i = first_length;
    j = second_length;

    int position = length - 1;

    while (i > 0 && j > 0)
    {
        if (
            first[i - 1] ==
            second[j - 1]
        )
        {
            result[position] =
                first[i - 1];

            position--;
            i--;
            j--;
        }
        else if (
            dp[i - 1][j] >
            dp[i][j - 1]
        )
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    return length;
}
#include "dynamic_programming.h"


static int maximum(
    int first,
    int second
)
{
    if (first > second)
    {
        return first;
    }

    return second;
}


KnapsackResult solve_zero_one_knapsack(
    const InvestigationCase cases[],
    int case_count,
    int available_hours
)
{
    int dp[MAX_CASES + 1][MAX_CAPACITY + 1] = {0};

    KnapsackResult result;

    result.maximum_risk = 0;
    result.selected_count = 0;

    /*
     * Input validation.
     */
    if (
        cases == 0 ||
        case_count <= 0 ||
        case_count > MAX_CASES ||
        available_hours <= 0 ||
        available_hours > MAX_CAPACITY
    )
    {
        return result;
    }


    /*
     * dp[i][hours]
     *
     * Maximum risk value obtainable
     * using first i cases with the
     * given number of available hours.
     */
    for (int i = 1; i <= case_count; i++)
    {
        int case_time =
            cases[i - 1].investigation_time;

        int case_risk =
            cases[i - 1].risk_value;

        for (
            int hours = 0;
            hours <= available_hours;
            hours++
        )
        {
            /*
             * Case cannot fit.
             */
            if (case_time > hours)
            {
                dp[i][hours] =
                    dp[i - 1][hours];
            }

            /*
             * Either:
             *
             * 1. Skip the case
             * 2. Investigate the case
             *
             * Choose the better value.
             */
            else
            {
                int skip_case =
                    dp[i - 1][hours];

                int take_case =
                    case_risk +
                    dp[i - 1]
                      [hours - case_time];

                dp[i][hours] =
                    maximum(
                        skip_case,
                        take_case
                    );
            }
        }
    }


    result.maximum_risk =
        dp[case_count][available_hours];


    /*
     * Backtrack through DP table
     * to determine which cases
     * were selected.
     */
    int remaining_hours =
        available_hours;

    for (
        int i = case_count;
        i > 0;
        i--
    )
    {
        if (
            dp[i][remaining_hours] !=
            dp[i - 1][remaining_hours]
        )
        {
            result.selected_indices
                [result.selected_count] =
                i - 1;

            result.selected_count++;

            remaining_hours -=
                cases[i - 1]
                    .investigation_time;
        }
    }

    return result;
}
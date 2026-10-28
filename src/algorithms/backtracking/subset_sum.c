#include "backtracking.h"


static int subset_recursive(
    const int values[],
    int count,
    int index,
    int current_sum,
    int target,
    int selected[],
    int selected_count,
    SubsetResult *result
)
{
    /*
     * Target reached.
     */
    if (current_sum == target)
    {
        result->found = 1;
        result->sum = current_sum;
        result->selected_count =
            selected_count;

        for (int i = 0;
             i < selected_count;
             i++)
        {
            result->selected[i] =
                selected[i];
        }

        return 1;
    }

    /*
     * No more values available.
     */
    if (index >= count)
    {
        return 0;
    }

    /*
     * CHOICE 1:
     * Include current value.
     */
    selected[selected_count] =
        values[index];

    if (
        subset_recursive(
            values,
            count,
            index + 1,
            current_sum + values[index],
            target,
            selected,
            selected_count + 1,
            result
        )
    )
    {
        return 1;
    }

    /*
     * BACKTRACK:
     * Remove current value implicitly
     * and explore without it.
     */

    /*
     * CHOICE 2:
     * Exclude current value.
     */
    if (
        subset_recursive(
            values,
            count,
            index + 1,
            current_sum,
            target,
            selected,
            selected_count,
            result
        )
    )
    {
        return 1;
    }

    return 0;
}


SubsetResult solve_subset_sum(
    const int values[],
    int count,
    int target
)
{
    SubsetResult result;

    result.found = 0;
    result.selected_count = 0;
    result.sum = 0;

    if (
        values == 0 ||
        count <= 0 ||
        count > SUBSET_MAX_SIZE
    )
    {
        return result;
    }

    int selected[
        SUBSET_MAX_SIZE
    ];

    subset_recursive(
        values,
        count,
        0,
        0,
        target,
        selected,
        0,
        &result
    );

    return result;
}
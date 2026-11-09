#include <stddef.h>

#include "backtracking.h"


static void search_knapsack(
    const BacktrackingKnapsackItem items[],
    int count,
    int capacity,
    int index,
    int current_risk,
    int current_time,
    int current_ids[],
    int current_count,
    BacktrackingKnapsackResult *best
)
{
    /*
     * Capacity exceeded:
     * this branch cannot produce a valid solution.
     */
    if (current_time > capacity)
    {
        return;
    }


    /*
     * All items have been considered.
     */
    if (index == count)
    {
        if (
            current_risk >
            best->maximum_risk
        )
        {
            best->maximum_risk =
                current_risk;

            best->total_time =
                current_time;

            best->selected_count =
                current_count;


            for (
                int i = 0;
                i < current_count;
                i++
            )
            {
                best->selected_ids[i] =
                    current_ids[i];
            }
        }

        return;
    }


    /*
     * ------------------------------------------------
     * CHOICE 1:
     * Include the current investigation case.
     * ------------------------------------------------
     */
    if (
        current_time +
        items[index].investigation_time
        <= capacity
    )
    {
        current_ids[current_count] =
            items[index].id;


        search_knapsack(
            items,
            count,
            capacity,
            index + 1,

            current_risk +
                items[index].risk_value,

            current_time +
                items[index].investigation_time,

            current_ids,
            current_count + 1,
            best
        );
    }


    /*
     * ------------------------------------------------
     * CHOICE 2:
     * Exclude the current investigation case.
     * ------------------------------------------------
     */
    search_knapsack(
        items,
        count,
        capacity,
        index + 1,
        current_risk,
        current_time,
        current_ids,
        current_count,
        best
    );
}


BacktrackingKnapsackResult
solve_knapsack_backtracking(
    const BacktrackingKnapsackItem items[],
    int count,
    int capacity
)
{
    BacktrackingKnapsackResult result = {0};


    if (
        items == NULL ||
        count <= 0 ||
        capacity <= 0
    )
    {
        return result;
    }


    if (
        count >
        BACKTRACK_KNAPSACK_MAX_ITEMS
    )
    {
        count =
            BACKTRACK_KNAPSACK_MAX_ITEMS;
    }


    int current_ids[
        BACKTRACK_KNAPSACK_MAX_ITEMS
    ] = {0};


    search_knapsack(
        items,
        count,
        capacity,
        0,
        0,
        0,
        current_ids,
        0,
        &result
    );


    return result;
}
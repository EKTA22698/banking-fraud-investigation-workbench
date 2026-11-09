#include "greedy.h"
#include <stddef.h>

typedef struct
{
    FractionalItem item;
    double ratio;
} RankedFractionalItem;


static void sort_by_ratio(
    RankedFractionalItem items[],
    int count
)
{
    /*
     * Small deterministic teaching/demo workload.
     * Simple insertion sort keeps this helper
     * independent of the transaction sort module.
     */
    for (int i = 1; i < count; i++)
    {
        RankedFractionalItem key =
            items[i];

        int j = i - 1;

        while (
            j >= 0 &&
            items[j].ratio < key.ratio
        )
        {
            items[j + 1] =
                items[j];

            j--;
        }

        items[j + 1] =
            key;
    }
}


FractionalKnapsackResult
fractional_knapsack(
    const FractionalItem items[],
    int count,
    double capacity
)
{
    FractionalKnapsackResult result = {0};

    if (
        items == NULL ||
        count <= 0 ||
        capacity <= 0.0
    )
    {
        return result;
    }


    if (count > MAX_FRACTIONAL_ITEMS)
    {
        count =
            MAX_FRACTIONAL_ITEMS;
    }


    RankedFractionalItem ranked[
        MAX_FRACTIONAL_ITEMS
    ];


    int valid_count = 0;


    for (int i = 0; i < count; i++)
    {
        /*
         * Zero/negative investigation time
         * cannot produce a meaningful ratio.
         */
        if (
            items[i].investigation_time <= 0.0
        )
        {
            continue;
        }


        ranked[valid_count].item =
            items[i];

        ranked[valid_count].ratio =
            items[i].risk_value /
            items[i].investigation_time;

        valid_count++;
    }


    sort_by_ratio(
        ranked,
        valid_count
    );


    double remaining =
        capacity;


    for (
        int i = 0;
        i < valid_count &&
        remaining > 0.0;
        i++
    )
    {
        FractionalItem current =
            ranked[i].item;


        double fraction;

        if (
            current.investigation_time <=
            remaining
        )
        {
            fraction = 1.0;
        }
        else
        {
            fraction =
                remaining /
                current.investigation_time;
        }


        FractionalSelection *selection =
            &result.selected[
                result.selected_count
            ];


        selection->id =
            current.id;

        selection->fraction =
            fraction;

        selection->time_used =
            current.investigation_time *
            fraction;

        selection->risk_obtained =
            current.risk_value *
            fraction;


        result.total_time +=
            selection->time_used;

        result.maximum_risk +=
            selection->risk_obtained;

        remaining -=
            selection->time_used;

        result.selected_count++;
    }


    return result;
}
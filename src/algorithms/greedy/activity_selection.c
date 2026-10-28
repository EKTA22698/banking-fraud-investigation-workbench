#include "greedy.h"

static void swap_activity(
    Activity *first,
    Activity *second
)
{
    Activity temp = *first;
    *first = *second;
    *second = temp;
}


static void sort_by_finish_time(
    Activity activities[],
    int count
)
{
    int i;
    int j;

    /*
     * Simple insertion-style ordering.
     * Activities are sorted by finish time.
     */
    for (i = 1; i < count; i++)
    {
        j = i;

        while (
            j > 0 &&
            activities[j - 1].finish >
            activities[j].finish
        )
        {
            swap_activity(
                &activities[j - 1],
                &activities[j]
            );

            j--;
        }
    }
}


int activity_selection(
    Activity activities[],
    int count,
    Activity selected[]
)
{
    int selected_count = 0;
    int i;
    int last_finish;

    if (count <= 0)
    {
        return 0;
    }

    sort_by_finish_time(
        activities,
        count
    );

    /*
     * Greedy choice:
     * always select the activity
     * finishing earliest.
     */
    selected[selected_count] =
        activities[0];

    selected_count++;

    last_finish =
        activities[0].finish;

    for (i = 1; i < count; i++)
    {
        if (
            activities[i].start >=
            last_finish
        )
        {
            selected[selected_count] =
                activities[i];

            selected_count++;

            last_finish =
                activities[i].finish;
        }
    }

    return selected_count;
}
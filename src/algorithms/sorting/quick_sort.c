#include <stddef.h>
#include "sorting.h"

static void swap_transactions(
    Transaction *first,
    Transaction *second
)
{
    Transaction temporary = *first;
    *first = *second;
    *second = temporary;
}


static int partition(
    Transaction transactions[],
    int low,
    int high
)
{
    double pivot = transactions[high].amount;

    int i = low - 1;
    int j;

    for (j = low; j < high; j++)
    {
        if (transactions[j].amount <= pivot)
        {
            i++;

            swap_transactions(
                &transactions[i],
                &transactions[j]
            );
        }
    }

    swap_transactions(
        &transactions[i + 1],
        &transactions[high]
    );

    return i + 1;
}


static void quick_sort_recursive(
    Transaction transactions[],
    int low,
    int high
)
{
    if (low < high)
    {
        int pivot_index = partition(
            transactions,
            low,
            high
        );

        quick_sort_recursive(
            transactions,
            low,
            pivot_index - 1
        );

        quick_sort_recursive(
            transactions,
            pivot_index + 1,
            high
        );
    }
}


void quick_sort_transactions(
    Transaction transactions[],
    int count
)
{
    if (transactions == NULL || count <= 1)
    {
        return;
    }

    quick_sort_recursive(
        transactions,
        0,
        count - 1
    );
}
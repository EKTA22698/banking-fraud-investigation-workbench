#include <stdlib.h>

#include "sorting.h"

static void merge(
    Transaction transactions[],
    int left,
    int middle,
    int right
)
{
    int left_size = middle - left + 1;
    int right_size = right - middle;

    Transaction *left_array =
        malloc(left_size * sizeof(Transaction));

    Transaction *right_array =
        malloc(right_size * sizeof(Transaction));

    if (left_array == NULL || right_array == NULL)
    {
        free(left_array);
        free(right_array);
        return;
    }

    int i;
    int j;
    int k;

    for (i = 0; i < left_size; i++)
    {
        left_array[i] = transactions[left + i];
    }

    for (j = 0; j < right_size; j++)
    {
        right_array[j] = transactions[middle + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;

    while (i < left_size && j < right_size)
    {
        if (left_array[i].amount <= right_array[j].amount)
        {
            transactions[k] = left_array[i];
            i++;
        }
        else
        {
            transactions[k] = right_array[j];
            j++;
        }

        k++;
    }

    while (i < left_size)
    {
        transactions[k] = left_array[i];
        i++;
        k++;
    }

    while (j < right_size)
    {
        transactions[k] = right_array[j];
        j++;
        k++;
    }

    free(left_array);
    free(right_array);
}


static void merge_sort_recursive(
    Transaction transactions[],
    int left,
    int right
)
{
    if (left >= right)
    {
        return;
    }

    int middle = left + (right - left) / 2;

    merge_sort_recursive(
        transactions,
        left,
        middle
    );

    merge_sort_recursive(
        transactions,
        middle + 1,
        right
    );

    merge(
        transactions,
        left,
        middle,
        right
    );
}


void merge_sort_transactions(
    Transaction transactions[],
    int count
)
{
    if (transactions == NULL || count <= 1)
    {
        return;
    }

    merge_sort_recursive(
        transactions,
        0,
        count - 1
    );
}
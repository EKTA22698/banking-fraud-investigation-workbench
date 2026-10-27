#include <stddef.h>
#include <string.h>

#include "searching.h"

static void swap_transactions(
    Transaction *first,
    Transaction *second
)
{
    Transaction temporary = *first;
    *first = *second;
    *second = temporary;
}


/*
 * Sort by Transaction ID.
 *
 * This helper prepares the array for binary search.
 * We use insertion sort here only as an internal preparation step.
 * The mandatory sorting algorithms remain our Merge Sort and Quick Sort.
 */
void sort_transactions_by_id(
    Transaction transactions[],
    int count
)
{
    int i;

    if (transactions == NULL || count <= 1)
    {
        return;
    }

    for (i = 1; i < count; i++)
    {
        int j = i;

        while (
            j > 0 &&
            strcmp(
                transactions[j - 1].transaction_id,
                transactions[j].transaction_id
            ) > 0
        )
        {
            swap_transactions(
                &transactions[j - 1],
                &transactions[j]
            );

            j--;
        }
    }
}


int binary_search_iterative(
    const Transaction transactions[],
    int count,
    const char *transaction_id
)
{
    int left = 0;
    int right = count - 1;

    if (transactions == NULL ||
        transaction_id == NULL ||
        count <= 0)
    {
        return -1;
    }

    while (left <= right)
    {
        int middle = left + (right - left) / 2;

        int comparison = strcmp(
            transactions[middle].transaction_id,
            transaction_id
        );

        if (comparison == 0)
        {
            return middle;
        }

        if (comparison < 0)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }

    return -1;
}


static int binary_search_recursive_helper(
    const Transaction transactions[],
    int left,
    int right,
    const char *transaction_id
)
{
    if (left > right)
    {
        return -1;
    }

    int middle = left + (right - left) / 2;

    int comparison = strcmp(
        transactions[middle].transaction_id,
        transaction_id
    );

    if (comparison == 0)
    {
        return middle;
    }

    if (comparison < 0)
    {
        return binary_search_recursive_helper(
            transactions,
            middle + 1,
            right,
            transaction_id
        );
    }

    return binary_search_recursive_helper(
        transactions,
        left,
        middle - 1,
        transaction_id
    );
}


int binary_search_recursive(
    const Transaction transactions[],
    int count,
    const char *transaction_id
)
{
    if (transactions == NULL ||
        transaction_id == NULL ||
        count <= 0)
    {
        return -1;
    }

    return binary_search_recursive_helper(
        transactions,
        0,
        count - 1,
        transaction_id
    );
}
#ifndef BRANCH_BOUND_H
#define BRANCH_BOUND_H

#define BB_MAX_ITEMS 20
#define BB_MAX_NODES 10000

typedef struct
{
    int id;
    int cost;
    int value;
} BBItem;

typedef struct
{
    int maximum_value;
    int total_cost;

    int selected_count;
    int selected_ids[BB_MAX_ITEMS];

    int nodes_explored;
} BBResult;


/*
 * FIFO Branch and Bound
 * Queue-based exploration.
 */
BBResult branch_bound_fifo(
    const BBItem items[],
    int item_count,
    int capacity
);


/*
 * LIFO Branch and Bound
 * Stack-based exploration.
 */
BBResult branch_bound_lifo(
    const BBItem items[],
    int item_count,
    int capacity
);


/*
 * Least-Cost / Best-Bound Branch and Bound.
 */
BBResult branch_bound_least_cost(
    const BBItem items[],
    int item_count,
    int capacity
);

#endif
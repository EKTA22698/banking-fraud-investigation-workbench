#include "branch_bound.h"


typedef struct
{
    int level;

    int cost;
    int value;

    int selected[BB_MAX_ITEMS];

    /*
     * Upper bound on the best value
     * reachable from this node.
     */
    double bound;

} BBNode;


static double calculate_bound(
    const BBItem items[],
    int item_count,
    int capacity,
    const BBNode *node
)
{
    if (node->cost >= capacity)
    {
        return (double)node->value;
    }

    double bound =
        (double)node->value;

    int total_cost =
        node->cost;

    int next =
        node->level + 1;

    /*
     * Add complete remaining items
     * while capacity permits.
     */
    while (
        next < item_count &&
        total_cost + items[next].cost <=
        capacity
    )
    {
        total_cost +=
            items[next].cost;

        bound +=
            items[next].value;

        next++;
    }

    /*
     * Fractional final item gives an
     * optimistic upper bound.
     */
    if (
        next < item_count &&
        items[next].cost > 0
    )
    {
        int remaining =
            capacity - total_cost;

        bound +=
            ((double)remaining /
             items[next].cost) *
            items[next].value;
    }

    return bound;
}


static BBResult empty_result(void)
{
    BBResult result;

    result.maximum_value = 0;
    result.total_cost = 0;
    result.selected_count = 0;
    result.nodes_explored = 0;

    for (int i = 0; i < BB_MAX_ITEMS; i++)
    {
        result.selected_ids[i] = -1;
    }

    return result;
}


static void update_result(
    BBResult *result,
    const BBItem items[],
    int item_count,
    const BBNode *node
)
{
    if (
        node->cost <= result->total_cost &&
        node->value < result->maximum_value
    )
    {
        return;
    }

    if (node->value <= result->maximum_value)
    {
        return;
    }

    result->maximum_value =
        node->value;

    result->total_cost =
        node->cost;

    result->selected_count = 0;

    for (int i = 0; i < item_count; i++)
    {
        if (node->selected[i])
        {
            result->selected_ids[
                result->selected_count
            ] = items[i].id;

            result->selected_count++;
        }
    }
}


/*
 * FIFO BRANCH AND BOUND
 *
 * Uses a queue.
 */
BBResult branch_bound_fifo(
    const BBItem items[],
    int item_count,
    int capacity
)
{
    BBResult result =
        empty_result();

    if (
        items == 0 ||
        item_count <= 0 ||
        item_count > BB_MAX_ITEMS ||
        capacity <= 0
    )
    {
        return result;
    }

    BBNode queue[BB_MAX_NODES];

    int front = 0;
    int rear = 0;

    BBNode root = {0};

    root.level = -1;
    root.cost = 0;
    root.value = 0;

    root.bound =
        calculate_bound(
            items,
            item_count,
            capacity,
            &root
        );

    queue[rear++] = root;

    while (front < rear)
    {
        BBNode current =
            queue[front++];

        result.nodes_explored++;

        if (
            current.bound <=
            result.maximum_value
        )
        {
            continue;
        }

        int next =
            current.level + 1;

        if (next >= item_count)
        {
            continue;
        }


        /*
         * BRANCH 1:
         * Include next item.
         */
        BBNode include =
            current;

        include.level = next;

        include.cost +=
            items[next].cost;

        include.value +=
            items[next].value;

        include.selected[next] = 1;

        if (include.cost <= capacity)
        {
            update_result(
                &result,
                items,
                item_count,
                &include
            );

            include.bound =
                calculate_bound(
                    items,
                    item_count,
                    capacity,
                    &include
                );

            if (
                include.bound >
                result.maximum_value &&
                rear < BB_MAX_NODES
            )
            {
                queue[rear++] =
                    include;
            }
        }


        /*
         * BRANCH 2:
         * Exclude next item.
         */
        BBNode exclude =
            current;

        exclude.level = next;
        exclude.selected[next] = 0;

        exclude.bound =
            calculate_bound(
                items,
                item_count,
                capacity,
                &exclude
            );

        if (
            exclude.bound >
            result.maximum_value &&
            rear < BB_MAX_NODES
        )
        {
            queue[rear++] =
                exclude;
        }
    }

    return result;
}


/*
 * LIFO BRANCH AND BOUND
 *
 * Uses a stack.
 */
BBResult branch_bound_lifo(
    const BBItem items[],
    int item_count,
    int capacity
)
{
    BBResult result =
        empty_result();

    if (
        items == 0 ||
        item_count <= 0 ||
        item_count > BB_MAX_ITEMS ||
        capacity <= 0
    )
    {
        return result;
    }

    BBNode stack[BB_MAX_NODES];

    int top = 0;

    BBNode root = {0};

    root.level = -1;

    root.bound =
        calculate_bound(
            items,
            item_count,
            capacity,
            &root
        );

    stack[top++] = root;

    while (top > 0)
    {
        BBNode current =
            stack[--top];

        result.nodes_explored++;

        if (
            current.bound <=
            result.maximum_value
        )
        {
            continue;
        }

        int next =
            current.level + 1;

        if (next >= item_count)
        {
            continue;
        }


        /*
         * Push EXCLUDE first so INCLUDE
         * is explored first by LIFO.
         */
        BBNode exclude =
            current;

        exclude.level = next;
        exclude.selected[next] = 0;

        exclude.bound =
            calculate_bound(
                items,
                item_count,
                capacity,
                &exclude
            );

        if (
            exclude.bound >
            result.maximum_value &&
            top < BB_MAX_NODES
        )
        {
            stack[top++] =
                exclude;
        }


        BBNode include =
            current;

        include.level = next;

        include.cost +=
            items[next].cost;

        include.value +=
            items[next].value;

        include.selected[next] = 1;

        if (include.cost <= capacity)
        {
            update_result(
                &result,
                items,
                item_count,
                &include
            );

            include.bound =
                calculate_bound(
                    items,
                    item_count,
                    capacity,
                    &include
                );

            if (
                include.bound >
                result.maximum_value &&
                top < BB_MAX_NODES
            )
            {
                stack[top++] =
                    include;
            }
        }
    }

    return result;
}


/*
 * Remove the node having the
 * highest optimistic bound.
 *
 * In a maximization problem this is
 * equivalent to best-bound search.
 */
static BBNode remove_best_node(
    BBNode nodes[],
    int *count
)
{
    int best_index = 0;

    for (int i = 1; i < *count; i++)
    {
        if (
            nodes[i].bound >
            nodes[best_index].bound
        )
        {
            best_index = i;
        }
    }

    BBNode best =
        nodes[best_index];

    for (
        int i = best_index;
        i < *count - 1;
        i++
    )
    {
        nodes[i] =
            nodes[i + 1];
    }

    (*count)--;

    return best;
}


/*
 * LEAST-COST / BEST-BOUND
 * BRANCH AND BOUND
 */
BBResult branch_bound_least_cost(
    const BBItem items[],
    int item_count,
    int capacity
)
{
    BBResult result =
        empty_result();

    if (
        items == 0 ||
        item_count <= 0 ||
        item_count > BB_MAX_ITEMS ||
        capacity <= 0
    )
    {
        return result;
    }

    BBNode active[
        BB_MAX_NODES
    ];

    int active_count = 0;

    BBNode root = {0};

    root.level = -1;

    root.bound =
        calculate_bound(
            items,
            item_count,
            capacity,
            &root
        );

    active[active_count++] =
        root;

    while (active_count > 0)
    {
        BBNode current =
            remove_best_node(
                active,
                &active_count
            );

        result.nodes_explored++;

        if (
            current.bound <=
            result.maximum_value
        )
        {
            continue;
        }

        int next =
            current.level + 1;

        if (next >= item_count)
        {
            continue;
        }


        BBNode include =
            current;

        include.level = next;

        include.cost +=
            items[next].cost;

        include.value +=
            items[next].value;

        include.selected[next] = 1;

        if (include.cost <= capacity)
        {
            update_result(
                &result,
                items,
                item_count,
                &include
            );

            include.bound =
                calculate_bound(
                    items,
                    item_count,
                    capacity,
                    &include
                );

            if (
                include.bound >
                result.maximum_value &&
                active_count <
                BB_MAX_NODES
            )
            {
                active[
                    active_count++
                ] = include;
            }
        }


        BBNode exclude =
            current;

        exclude.level = next;
        exclude.selected[next] = 0;

        exclude.bound =
            calculate_bound(
                items,
                item_count,
                capacity,
                &exclude
            );

        if (
            exclude.bound >
            result.maximum_value &&
            active_count <
            BB_MAX_NODES
        )
        {
            active[
                active_count++
            ] = exclude;
        }
    }

    return result;
}
#include "dynamic_programming.h"

static int tsp_recursive(
    int vertex_count,
    const int graph[TSP_MAX_VERTICES][TSP_MAX_VERTICES],
    int current,
    int visited_mask,
    int all_visited_mask,
    int memo[TSP_MAX_VERTICES][1 << TSP_MAX_VERTICES],
    int next_vertex[TSP_MAX_VERTICES][1 << TSP_MAX_VERTICES]
)
{
    if (visited_mask == all_visited_mask)
    {
        return graph[current][0];
    }

    if (memo[current][visited_mask] != -1)
    {
        return memo[current][visited_mask];
    }

    int minimum_cost = TSP_INF;
    int best_next = -1;

    for (int next = 0; next < vertex_count; next++)
    {
        int bit = 1 << next;

        if ((visited_mask & bit) == 0)
        {
            if (graph[current][next] >= TSP_INF)
            {
                continue;
            }

            int remaining_cost =
                tsp_recursive(
                    vertex_count,
                    graph,
                    next,
                    visited_mask | bit,
                    all_visited_mask,
                    memo,
                    next_vertex
                );

            if (remaining_cost >= TSP_INF)
            {
                continue;
            }

            int total_cost =
                graph[current][next] +
                remaining_cost;

            if (total_cost < minimum_cost)
            {
                minimum_cost = total_cost;
                best_next = next;
            }
        }
    }

    next_vertex[current][visited_mask] =
        best_next;

    memo[current][visited_mask] =
        minimum_cost;

    return minimum_cost;
}


TSPResult solve_bounded_tsp(
    int vertex_count,
    const int graph[TSP_MAX_VERTICES][TSP_MAX_VERTICES]
)
{
    TSPResult result;

    result.minimum_cost = TSP_INF;
    result.path_length = 0;

    if (
        vertex_count <= 1 ||
        vertex_count > TSP_MAX_VERTICES
    )
    {
        return result;
    }

    int memo
        [TSP_MAX_VERTICES]
        [1 << TSP_MAX_VERTICES];

    int next_vertex
        [TSP_MAX_VERTICES]
        [1 << TSP_MAX_VERTICES];

    for (int i = 0; i < TSP_MAX_VERTICES; i++)
    {
        for (
            int mask = 0;
            mask < (1 << TSP_MAX_VERTICES);
            mask++
        )
        {
            memo[i][mask] = -1;
            next_vertex[i][mask] = -1;
        }
    }

    int all_visited_mask =
        (1 << vertex_count) - 1;

    int starting_mask = 1;

    result.minimum_cost =
        tsp_recursive(
            vertex_count,
            graph,
            0,
            starting_mask,
            all_visited_mask,
            memo,
            next_vertex
        );

    if (result.minimum_cost >= TSP_INF)
    {
        return result;
    }

    /*
     * Reconstruct optimal tour.
     */
    int current = 0;
    int mask = starting_mask;

    result.path[result.path_length++] = 0;

    while (mask != all_visited_mask)
    {
        int next =
            next_vertex[current][mask];

        if (next == -1)
        {
            break;
        }

        result.path[result.path_length++] =
            next;

        mask |= 1 << next;
        current = next;
    }

    /*
     * Return to starting location.
     */
    result.path[result.path_length++] = 0;

    return result;
}
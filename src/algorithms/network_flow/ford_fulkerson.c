#include "network_flow.h"


static int find_augmenting_path(
    int vertex_count,
    int residual
        [FLOW_MAX_VERTICES]
        [FLOW_MAX_VERTICES],
    int source,
    int sink,
    int parent[]
)
{
    int visited[FLOW_MAX_VERTICES] = {0};

    int queue[FLOW_MAX_VERTICES];

    int front = 0;
    int rear = 0;

    queue[rear++] = source;
    visited[source] = 1;

    parent[source] = -1;


    /*
     * BFS is used to find an
     * augmenting path.
     *
     * This makes the implementation
     * effectively Edmonds-Karp style.
     */
    while (front < rear)
    {
        int current =
            queue[front++];

        for (
            int next = 0;
            next < vertex_count;
            next++
        )
        {
            if (
                !visited[next] &&
                residual[current][next] > 0
            )
            {
                queue[rear++] =
                    next;

                parent[next] =
                    current;

                visited[next] = 1;

                if (next == sink)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}


int ford_fulkerson(
    int vertex_count,
    const int capacity
        [FLOW_MAX_VERTICES]
        [FLOW_MAX_VERTICES],
    int source,
    int sink
)
{
    int residual
        [FLOW_MAX_VERTICES]
        [FLOW_MAX_VERTICES] = {0};

    int parent[FLOW_MAX_VERTICES];

    int maximum_flow = 0;


    /*
     * Initially residual capacity
     * equals original capacity.
     */
    for (int i = 0;
         i < vertex_count;
         i++)
    {
        for (int j = 0;
             j < vertex_count;
             j++)
        {
            residual[i][j] =
                capacity[i][j];
        }
    }


    /*
     * Repeatedly find an augmenting
     * path from source to sink.
     */
    while (
        find_augmenting_path(
            vertex_count,
            residual,
            source,
            sink,
            parent
        )
    )
    {
        int path_flow =
            2147483647;

        /*
         * Find bottleneck capacity.
         */
        for (
            int vertex = sink;
            vertex != source;
            vertex = parent[vertex]
        )
        {
            int previous =
                parent[vertex];

            if (
                residual[previous][vertex] <
                path_flow
            )
            {
                path_flow =
                    residual[previous][vertex];
            }
        }


        /*
         * Update residual graph.
         */
        for (
            int vertex = sink;
            vertex != source;
            vertex = parent[vertex]
        )
        {
            int previous =
                parent[vertex];

            residual[previous][vertex] -=
                path_flow;

            residual[vertex][previous] +=
                path_flow;
        }


        maximum_flow +=
            path_flow;
    }


    return maximum_flow;
}
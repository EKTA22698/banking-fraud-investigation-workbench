#include "graph_algorithms.h"


int bellman_ford(
    const WeightedGraph *graph,
    int source,
    int distances[],
    int previous[]
)
{
    int i;
    int iteration;
    int u;
    int v;

    for (i = 0; i < graph->vertices; i++)
    {
        distances[i] = GRAPH_INF;
        previous[i] = -1;
    }

    distances[source] = 0;

    /*
     * Relax every edge V - 1 times.
     */
    for (
        iteration = 1;
        iteration < graph->vertices;
        iteration++
    )
    {
        int changed = 0;

        for (u = 0; u < graph->vertices; u++)
        {
            for (v = 0; v < graph->vertices; v++)
            {
                int weight =
                    graph->adjacency[u][v];

                if (
                    weight != GRAPH_INF &&
                    u != v &&
                    distances[u] != GRAPH_INF &&
                    distances[u] + weight <
                    distances[v]
                )
                {
                    distances[v] =
                        distances[u] + weight;

                    previous[v] = u;

                    changed = 1;
                }
            }
        }

        /*
         * Optimization:
         * stop if nothing changed.
         */
        if (!changed)
        {
            break;
        }
    }

    /*
     * One additional pass detects
     * a reachable negative cycle.
     */
    for (u = 0; u < graph->vertices; u++)
    {
        for (v = 0; v < graph->vertices; v++)
        {
            int weight =
                graph->adjacency[u][v];

            if (
                weight != GRAPH_INF &&
                u != v &&
                distances[u] != GRAPH_INF &&
                distances[u] + weight <
                distances[v]
            )
            {
                return 0;
            }
        }
    }

    return 1;
}
#include "graph_algorithms.h"


void floyd_warshall(
    const WeightedGraph *graph,
    int distances
        [GRAPH_MAX_VERTICES]
        [GRAPH_MAX_VERTICES]
)
{
    int i;
    int j;
    int k;

    /*
     * Start with direct-edge distances.
     */
    for (i = 0; i < graph->vertices; i++)
    {
        for (j = 0; j < graph->vertices; j++)
        {
            distances[i][j] =
                graph->adjacency[i][j];
        }
    }

    /*
     * Try every vertex as an
     * intermediate vertex.
     */
    for (k = 0; k < graph->vertices; k++)
    {
        for (i = 0; i < graph->vertices; i++)
        {
            for (j = 0; j < graph->vertices; j++)
            {
                if (
                    distances[i][k] != GRAPH_INF &&
                    distances[k][j] != GRAPH_INF &&
                    distances[i][k] +
                    distances[k][j] <
                    distances[i][j]
                )
                {
                    distances[i][j] =
                        distances[i][k] +
                        distances[k][j];
                }
            }
        }
    }
}
#include "graph_algorithms.h"


int prim_mst(
    const WeightedGraph *graph,
    GraphEdge result[]
)
{
    int selected[GRAPH_MAX_VERTICES] = {0};

    int edge_count = 0;

    selected[0] = 1;

    while (
        edge_count <
        graph->vertices - 1
    )
    {
        int minimum = GRAPH_INF;

        int source = -1;
        int destination = -1;

        int i;
        int j;

        for (i = 0; i < graph->vertices; i++)
        {
            if (!selected[i])
            {
                continue;
            }

            for (j = 0; j < graph->vertices; j++)
            {
                if (
                    selected[j] ||
                    graph->adjacency[i][j] ==
                    GRAPH_INF
                )
                {
                    continue;
                }

                if (
                    graph->adjacency[i][j] <
                    minimum
                )
                {
                    minimum =
                        graph->adjacency[i][j];

                    source = i;
                    destination = j;
                }
            }
        }

        if (source == -1)
        {
            break;
        }

        result[edge_count].source =
            source;

        result[edge_count].destination =
            destination;

        result[edge_count].weight =
            minimum;

        edge_count++;

        selected[destination] = 1;
    }

    return edge_count;
}
#include <stdio.h>

#include "graph_algorithms.h"


void initialize_graph(
    WeightedGraph *graph,
    int vertices
)
{
    int i;
    int j;

    graph->vertices = vertices;

    for (i = 0; i < GRAPH_MAX_VERTICES; i++)
    {
        for (j = 0; j < GRAPH_MAX_VERTICES; j++)
        {
            if (i == j)
            {
                graph->adjacency[i][j] = 0;
            }
            else
            {
                graph->adjacency[i][j] = GRAPH_INF;
            }
        }
    }
}


void add_undirected_edge(
    WeightedGraph *graph,
    int source,
    int destination,
    int weight
)
{
    if (
        source < 0 ||
        destination < 0 ||
        source >= graph->vertices ||
        destination >= graph->vertices
    )
    {
        return;
    }

    graph->adjacency[source][destination] =
        weight;

    graph->adjacency[destination][source] =
        weight;
}


void dijkstra(
    const WeightedGraph *graph,
    int source,
    int distances[],
    int previous[]
)
{
    int visited[GRAPH_MAX_VERTICES] = {0};

    int i;
    int step;

    for (i = 0; i < graph->vertices; i++)
    {
        distances[i] = GRAPH_INF;
        previous[i] = -1;
    }

    distances[source] = 0;

    for (
        step = 0;
        step < graph->vertices;
        step++
    )
    {
        int current = -1;
        int minimum = GRAPH_INF;

        /*
         * Find unvisited vertex
         * with minimum distance.
         */
        for (i = 0; i < graph->vertices; i++)
        {
            if (
                !visited[i] &&
                distances[i] < minimum
            )
            {
                minimum = distances[i];
                current = i;
            }
        }

        if (current == -1)
        {
            break;
        }

        visited[current] = 1;

        /*
         * Relax outgoing edges.
         */
        for (i = 0; i < graph->vertices; i++)
        {
            int weight =
                graph->adjacency[current][i];

            if (
                !visited[i] &&
                weight != GRAPH_INF &&
                distances[current] != GRAPH_INF &&
                distances[current] + weight <
                distances[i]
            )
            {
                distances[i] =
                    distances[current] +
                    weight;

                previous[i] =
                    current;
            }
        }
    }
}


static void print_path_recursive(
    int vertex,
    const int previous[]
)
{
    if (vertex == -1)
    {
        return;
    }

    if (previous[vertex] != -1)
    {
        print_path_recursive(
            previous[vertex],
            previous
        );

        printf(" -> ");
    }

    printf("%d", vertex);
}


void print_shortest_path(
    int source,
    int destination,
    const int previous[]
)
{
    printf(
        "Evidence path: "
    );

    print_path_recursive(
        destination,
        previous
    );

    printf("\n");

    (void)source;
}
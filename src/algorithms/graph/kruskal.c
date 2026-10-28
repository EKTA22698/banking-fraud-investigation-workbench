#include "graph_algorithms.h"


static int find_parent(
    int parent[],
    int vertex
)
{
    if (parent[vertex] != vertex)
    {
        parent[vertex] =
            find_parent(
                parent,
                parent[vertex]
            );
    }

    return parent[vertex];
}


static void union_sets(
    int parent[],
    int rank[],
    int first,
    int second
)
{
    int root_first =
        find_parent(
            parent,
            first
        );

    int root_second =
        find_parent(
            parent,
            second
        );

    if (root_first == root_second)
    {
        return;
    }

    if (
        rank[root_first] <
        rank[root_second]
    )
    {
        parent[root_first] =
            root_second;
    }
    else if (
        rank[root_first] >
        rank[root_second]
    )
    {
        parent[root_second] =
            root_first;
    }
    else
    {
        parent[root_second] =
            root_first;

        rank[root_first]++;
    }
}


static void sort_edges(
    GraphEdge edges[],
    int count
)
{
    int i;
    int j;

    for (i = 1; i < count; i++)
    {
        GraphEdge current =
            edges[i];

        j = i - 1;

        while (
            j >= 0 &&
            edges[j].weight >
            current.weight
        )
        {
            edges[j + 1] =
                edges[j];

            j--;
        }

        edges[j + 1] =
            current;
    }
}


int kruskal_mst(
    const WeightedGraph *graph,
    GraphEdge result[]
)
{
    GraphEdge edges[
        GRAPH_MAX_VERTICES *
        GRAPH_MAX_VERTICES
    ];

    int edge_total = 0;

    int i;
    int j;

    /*
     * Extract each undirected edge once.
     */
    for (i = 0; i < graph->vertices; i++)
    {
        for (
            j = i + 1;
            j < graph->vertices;
            j++
        )
        {
            if (
                graph->adjacency[i][j] !=
                GRAPH_INF
            )
            {
                edges[edge_total].source = i;
                edges[edge_total].destination = j;

                edges[edge_total].weight =
                    graph->adjacency[i][j];

                edge_total++;
            }
        }
    }

    sort_edges(
        edges,
        edge_total
    );

    int parent[GRAPH_MAX_VERTICES];
    int rank[GRAPH_MAX_VERTICES] = {0};

    for (i = 0; i < graph->vertices; i++)
    {
        parent[i] = i;
    }

    int result_count = 0;

    for (
        i = 0;
        i < edge_total &&
        result_count <
        graph->vertices - 1;
        i++
    )
    {
        int root_source =
            find_parent(
                parent,
                edges[i].source
            );

        int root_destination =
            find_parent(
                parent,
                edges[i].destination
            );

        if (
            root_source !=
            root_destination
        )
        {
            result[result_count] =
                edges[i];

            result_count++;

            union_sets(
                parent,
                rank,
                root_source,
                root_destination
            );
        }
    }

    return result_count;
}
#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#define GRAPH_MAX_VERTICES 20
#define GRAPH_INF 1000000000

typedef struct
{
    int vertices;

    int adjacency
        [GRAPH_MAX_VERTICES]
        [GRAPH_MAX_VERTICES];

} WeightedGraph;


typedef struct
{
    int source;
    int destination;
    int weight;

} GraphEdge;


void initialize_graph(
    WeightedGraph *graph,
    int vertices
);


void add_undirected_edge(
    WeightedGraph *graph,
    int source,
    int destination,
    int weight
);


/* Dijkstra */

void dijkstra(
    const WeightedGraph *graph,
    int source,
    int distances[],
    int previous[]
);

void print_shortest_path(
    int source,
    int destination,
    const int previous[]
);


/* Prim */

int prim_mst(
    const WeightedGraph *graph,
    GraphEdge result[]
);


/* Kruskal */

int kruskal_mst(
    const WeightedGraph *graph,
    GraphEdge result[]
);

#endif
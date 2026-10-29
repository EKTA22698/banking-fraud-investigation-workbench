#include <stdio.h>
#include <time.h>

#include "benchmark.h"
#include "graph_algorithms.h"


static double graph_elapsed_ms(
    clock_t start,
    clock_t end
)
{
    return (
        (double)(end - start) /
        CLOCKS_PER_SEC
    ) * 1000.0;
}


static int mst_total_cost(
    const GraphEdge edges[],
    int edge_count
)
{
    int total = 0;

    for (int i = 0; i < edge_count; i++)
    {
        total += edges[i].weight;
    }

    return total;
}


void run_graph_benchmark(void)
{
    WeightedGraph graph;

    /*
     * Same fraud evidence graph used
     * by the investigation workbench.
     */
    initialize_graph(
        &graph,
        6
    );

    add_undirected_edge(&graph, 0, 1, 1);
    add_undirected_edge(&graph, 1, 2, 1);
    add_undirected_edge(&graph, 1, 4, 1);

    add_undirected_edge(&graph, 0, 3, 4);
    add_undirected_edge(&graph, 2, 3, 2);
    add_undirected_edge(&graph, 4, 3, 3);

    add_undirected_edge(&graph, 0, 5, 5);
    add_undirected_edge(&graph, 3, 5, 2);


    printf("\n");
    printf("============================================================\n");
    printf("                   GRAPH BENCHMARK\n");
    printf("============================================================\n");

    /*
     * ------------------------------------------------
     * SHORTEST PATH COMPARISON
     * ------------------------------------------------
     */

    int dijkstra_distance[
        GRAPH_MAX_VERTICES
    ];

    int dijkstra_previous[
        GRAPH_MAX_VERTICES
    ];

    int bellman_distance[
        GRAPH_MAX_VERTICES
    ];

    int bellman_previous[
        GRAPH_MAX_VERTICES
    ];


    clock_t start =
        clock();

    dijkstra(
        &graph,
        0,
        dijkstra_distance,
        dijkstra_previous
    );

    clock_t end =
        clock();

    double dijkstra_ms =
        graph_elapsed_ms(
            start,
            end
        );


    start = clock();

    int bellman_valid =
        bellman_ford(
            &graph,
            0,
            bellman_distance,
            bellman_previous
        );

    end = clock();

    double bellman_ms =
        graph_elapsed_ms(
            start,
            end
        );


    int shortest_correct =
        bellman_valid;

    for (
        int i = 0;
        i < graph.vertices;
        i++
    )
    {
        if (
            dijkstra_distance[i] !=
            bellman_distance[i]
        )
        {
            shortest_correct = 0;
            break;
        }
    }


    printf("\n");
    printf("SHORTEST PATH COMPARISON\n");

    printf(
        "------------------------------------------------------------\n"
    );

    printf(
        "%-20s %-15s %-15s\n",
        "ALGORITHM",
        "TIME (ms)",
        "DIST 0->4"
    );

    printf(
        "%-20s %-15.6f %-15d\n",
        "Dijkstra",
        dijkstra_ms,
        dijkstra_distance[4]
    );

    printf(
        "%-20s %-15.6f %-15d\n",
        "Bellman-Ford",
        bellman_ms,
        bellman_distance[4]
    );

    printf(
        "\nShortest-path correctness: %s\n",
        shortest_correct ?
        "PASS" :
        "FAIL"
    );


    /*
     * ------------------------------------------------
     * MST COMPARISON
     * ------------------------------------------------
     */

    GraphEdge prim_result[
        GRAPH_MAX_VERTICES
    ];

    GraphEdge kruskal_result[
        GRAPH_MAX_VERTICES
    ];


    start = clock();

    int prim_edges =
        prim_mst(
            &graph,
            prim_result
        );

    end = clock();

    double prim_ms =
        graph_elapsed_ms(
            start,
            end
        );


    start = clock();

    int kruskal_edges =
        kruskal_mst(
            &graph,
            kruskal_result
        );

    end = clock();

    double kruskal_ms =
        graph_elapsed_ms(
            start,
            end
        );


    int prim_cost =
        mst_total_cost(
            prim_result,
            prim_edges
        );

    int kruskal_cost =
        mst_total_cost(
            kruskal_result,
            kruskal_edges
        );


    int mst_correct =
        (
            prim_edges ==
            graph.vertices - 1
        ) &&
        (
            kruskal_edges ==
            graph.vertices - 1
        ) &&
        (
            prim_cost ==
            kruskal_cost
        );


    printf("\n");
    printf("MINIMUM SPANNING TREE COMPARISON\n");

    printf(
        "------------------------------------------------------------\n"
    );

    printf(
        "%-20s %-15s %-15s\n",
        "ALGORITHM",
        "TIME (ms)",
        "MST COST"
    );

    printf(
        "%-20s %-15.6f %-15d\n",
        "Prim",
        prim_ms,
        prim_cost
    );

    printf(
        "%-20s %-15.6f %-15d\n",
        "Kruskal",
        kruskal_ms,
        kruskal_cost
    );

    printf(
        "\nMST correctness: %s\n",
        mst_correct ?
        "PASS" :
        "FAIL"
    );


    /*
     * ------------------------------------------------
     * OVERALL
     * ------------------------------------------------
     */

    printf("\n");
    printf("============================================================\n");

    printf(
        "Overall Graph Benchmark: %s\n",
        (
            shortest_correct &&
            mst_correct
        ) ?
        "PASS" :
        "FAIL"
    );

    printf(
        "============================================================\n"
    );


    printf("\nComplexity Summary\n");
    printf("----------------------------------------\n");

    printf(
        "Dijkstra      : O(V^2) "
        "for current matrix implementation\n"
    );

    printf(
        "Bellman-Ford  : O(VE)\n"
    );

    printf(
        "Prim          : O(V^2) "
        "for current implementation\n"
    );

    printf(
        "Kruskal       : dominated by edge sorting; "
        "standard implementation O(E log E)\n"
    );

    printf("\nNotes:\n");

    printf(
        "- Dijkstra and Bellman-Ford are compared "
        "on a non-negative graph.\n"
    );

    printf(
        "- Prim and Kruskal may select different "
        "MST edges when multiple MSTs exist, but "
        "the minimum total cost must match.\n"
    );
}

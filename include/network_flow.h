#ifndef NETWORK_FLOW_H
#define NETWORK_FLOW_H

#define FLOW_MAX_VERTICES 20
#define MATCH_MAX_LEFT 20
#define MATCH_MAX_RIGHT 20


/* Ford-Fulkerson */
int ford_fulkerson(
    int vertex_count,
    const int capacity
        [FLOW_MAX_VERTICES]
        [FLOW_MAX_VERTICES],
    int source,
    int sink
);


/* Maximum Bipartite Matching */
int maximum_bipartite_matching(
    int left_count,
    int right_count,
    const int compatibility
        [MATCH_MAX_LEFT]
        [MATCH_MAX_RIGHT],
    int right_matches[]
);

#endif
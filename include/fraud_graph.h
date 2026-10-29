#ifndef FRAUD_GRAPH_H
#define FRAUD_GRAPH_H

#include <stddef.h>

#include "transaction.h"
#include "graph_algorithms.h"

typedef struct
{
    WeightedGraph graph;

    char labels
        [GRAPH_MAX_VERTICES]
        [ID_LENGTH];

    int transaction_edges;

} FraudInvestigationGraph;


int build_paysim_investigation_graph(
    const Transaction transactions[],
    size_t count,
    int risk_threshold,
    FraudInvestigationGraph *result
);

#endif
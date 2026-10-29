#include <stdio.h>
#include <string.h>

#include "fraud_graph.h"


static int find_vertex(
    const FraudInvestigationGraph *result,
    const char *account_id
)
{
    for (
        int i = 0;
        i < result->graph.vertices;
        i++
    )
    {
        if (
            strcmp(
                result->labels[i],
                account_id
            ) == 0
        )
        {
            return i;
        }
    }

    return -1;
}


static int get_or_add_vertex(
    FraudInvestigationGraph *result,
    const char *account_id
)
{
    int existing =
        find_vertex(
            result,
            account_id
        );

    if (existing >= 0)
    {
        return existing;
    }

    if (
        result->graph.vertices >=
        GRAPH_MAX_VERTICES
    )
    {
        return -1;
    }

    int index =
        result->graph.vertices;

    snprintf(
        result->labels[index],
        ID_LENGTH,
        "%s",
        account_id
    );

    result->graph.vertices++;

    return index;
}


static int evidence_weight(
    const Transaction *transaction
)
{
    /*
     * Graph algorithms interpret smaller
     * weights as stronger/shorter links.
     *
     * Therefore higher fraud risk produces
     * a lower evidence cost.
     */
    int weight =
        101 - transaction->risk_score;

    if (weight < 1)
    {
        weight = 1;
    }

    if (weight > 100)
    {
        weight = 100;
    }

    return weight;
}

int build_paysim_investigation_graph(
    const Transaction transactions[],
    size_t count,
    int risk_threshold,
    FraudInvestigationGraph *result
)
{
    if (
        transactions == NULL ||
        result == NULL ||
        count == 0
    )
    {
        return 0;
    }

    initialize_graph(
        &result->graph,
        0
    );

    result->transaction_edges = 0;

    for (
        int i = 0;
        i < GRAPH_MAX_VERTICES;
        i++
    )
    {
        result->labels[i][0] = '\0';
    }

    /*
     * ------------------------------------------------
     * PHASE 1:
     * Find highest-risk suspicious transaction.
     * ------------------------------------------------
     */
    size_t seed_index = count;
    int highest_risk = -1;

    for (size_t i = 0; i < count; i++)
    {
        if (
            transactions[i].risk_score >=
                risk_threshold &&
            transactions[i].risk_score >
                highest_risk &&
            transactions[i].account_id[0] != '\0' &&
            transactions[i].destination_id[0] != '\0'
        )
        {
            highest_risk =
                transactions[i].risk_score;

            seed_index = i;
        }
    }

    if (seed_index == count)
    {
        return 0;
    }


    /*
     * Add seed relationship.
     */
    const Transaction *seed =
        &transactions[seed_index];

    int seed_source =
        get_or_add_vertex(
            result,
            seed->account_id
        );

    int seed_destination =
        get_or_add_vertex(
            result,
            seed->destination_id
        );

    if (
        seed_source < 0 ||
        seed_destination < 0
    )
    {
        return 0;
    }

    if (seed_source != seed_destination)
    {
        add_undirected_edge(
            &result->graph,
            seed_source,
            seed_destination,
            evidence_weight(seed)
        );

        result->transaction_edges++;
    }


    /*
     * ------------------------------------------------
     * PHASE 2:
     * Grow around currently selected accounts.
     *
     * Repeat passes because adding a new account
     * may reveal further connected transactions.
     * ------------------------------------------------
     */
    int changed = 1;

    while (
        changed &&
        result->graph.vertices <
            GRAPH_MAX_VERTICES
    )
    {
        changed = 0;

        for (
            size_t i = 0;
            i < count &&
            result->graph.vertices <
                GRAPH_MAX_VERTICES;
            i++
        )
        {
            const Transaction *transaction =
                &transactions[i];

            if (
                transaction->risk_score <
                risk_threshold
            )
            {
                continue;
            }

            int source =
                find_vertex(
                    result,
                    transaction->account_id
                );

            int destination =
                find_vertex(
                    result,
                    transaction->destination_id
                );

            /*
             * At least one endpoint must already
             * belong to the investigation cluster.
             */
            if (
                source < 0 &&
                destination < 0
            )
            {
                continue;
            }


            int required_vertices = 0;

            if (source < 0)
            {
                required_vertices++;
            }

            if (
                destination < 0 &&
                strcmp(
                    transaction->account_id,
                    transaction->destination_id
                ) != 0
            )
            {
                required_vertices++;
            }

            if (
                result->graph.vertices +
                required_vertices >
                GRAPH_MAX_VERTICES
            )
            {
                continue;
            }


            int old_vertex_count =
                result->graph.vertices;

            source =
                get_or_add_vertex(
                    result,
                    transaction->account_id
                );

            destination =
                get_or_add_vertex(
                    result,
                    transaction->destination_id
                );

            if (
                source < 0 ||
                destination < 0 ||
                source == destination
            )
            {
                continue;
            }


            int weight =
                evidence_weight(
                    transaction
                );

            if (
                result->graph
                    .adjacency[source][destination]
                    == GRAPH_INF ||
                weight <
                result->graph
                    .adjacency[source][destination]
            )
            {
                add_undirected_edge(
                    &result->graph,
                    source,
                    destination,
                    weight
                );

                result->transaction_edges++;
            }

            if (
                result->graph.vertices >
                old_vertex_count
            )
            {
                changed = 1;
            }
        }
    }


    /*
     * ------------------------------------------------
     * PHASE 3:
     * If the connected component is naturally
     * smaller than 20 vertices, add additional
     * suspicious relationships for context.
     * ------------------------------------------------
     */
    if (
        result->graph.vertices <
        GRAPH_MAX_VERTICES
    )
    {
        for (
            size_t i = 0;
            i < count &&
            result->graph.vertices <
                GRAPH_MAX_VERTICES;
            i++
        )
        {
            const Transaction *transaction =
                &transactions[i];

            if (
                transaction->risk_score <
                risk_threshold
            )
            {
                continue;
            }

            int source =
                find_vertex(
                    result,
                    transaction->account_id
                );

            int destination =
                find_vertex(
                    result,
                    transaction->destination_id
                );

            int required_vertices = 0;

            if (source < 0)
            {
                required_vertices++;
            }

            if (
                destination < 0 &&
                strcmp(
                    transaction->account_id,
                    transaction->destination_id
                ) != 0
            )
            {
                required_vertices++;
            }

            if (
                result->graph.vertices +
                required_vertices >
                GRAPH_MAX_VERTICES
            )
            {
                continue;
            }

            source =
                get_or_add_vertex(
                    result,
                    transaction->account_id
                );

            destination =
                get_or_add_vertex(
                    result,
                    transaction->destination_id
                );

            if (
                source < 0 ||
                destination < 0 ||
                source == destination
            )
            {
                continue;
            }

            int weight =
                evidence_weight(
                    transaction
                );

            if (
                result->graph
                    .adjacency[source][destination]
                    == GRAPH_INF ||
                weight <
                result->graph
                    .adjacency[source][destination]
            )
            {
                add_undirected_edge(
                    &result->graph,
                    source,
                    destination,
                    weight
                );

                result->transaction_edges++;
            }
        }
    }


    return
        result->graph.vertices >= 2;
}

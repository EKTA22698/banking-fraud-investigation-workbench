#include "network_flow.h"


static int try_match(
    int case_index,
    int right_count,
    const int compatibility
        [MATCH_MAX_LEFT]
        [MATCH_MAX_RIGHT],
    int visited[],
    int right_matches[]
)
{
    for (
        int investigator = 0;
        investigator < right_count;
        investigator++
    )
    {
        /*
         * No compatibility edge.
         */
        if (
            !compatibility
                [case_index]
                [investigator]
        )
        {
            continue;
        }

        if (visited[investigator])
        {
            continue;
        }

        visited[investigator] = 1;


        /*
         * Investigator is free,
         * OR their current case can
         * be moved to another analyst.
         */
        if (
            right_matches[investigator] == -1 ||
            try_match(
                right_matches[investigator],
                right_count,
                compatibility,
                visited,
                right_matches
            )
        )
        {
            right_matches[investigator] =
                case_index;

            return 1;
        }
    }

    return 0;
}


int maximum_bipartite_matching(
    int left_count,
    int right_count,
    const int compatibility
        [MATCH_MAX_LEFT]
        [MATCH_MAX_RIGHT],
    int right_matches[]
)
{
    int match_count = 0;


    for (
        int investigator = 0;
        investigator < right_count;
        investigator++
    )
    {
        right_matches[investigator] =
            -1;
    }


    for (
        int case_index = 0;
        case_index < left_count;
        case_index++
    )
    {
        int visited[
            MATCH_MAX_RIGHT
        ] = {0};

        if (
            try_match(
                case_index,
                right_count,
                compatibility,
                visited,
                right_matches
            )
        )
        {
            match_count++;
        }
    }


    return match_count;
}
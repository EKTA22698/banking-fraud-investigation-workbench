#include <string.h>

#include "string_matching.h"


MatchResult naive_pattern_search(
    const char *text,
    const char *pattern
)
{
    MatchResult result;

    result.count = 0;

    if (
        text == NULL ||
        pattern == NULL
    )
    {
        return result;
    }

    int text_length =
        (int)strlen(text);

    int pattern_length =
        (int)strlen(pattern);

    if (
        pattern_length == 0 ||
        pattern_length > text_length
    )
    {
        return result;
    }


    for (
        int i = 0;
        i <= text_length - pattern_length;
        i++
    )
    {
        int matched = 1;

        for (
            int j = 0;
            j < pattern_length;
            j++
        )
        {
            if (
                text[i + j] !=
                pattern[j]
            )
            {
                matched = 0;
                break;
            }
        }


        if (
            matched &&
            result.count < MAX_MATCHES
        )
        {
            result.positions[
                result.count++
            ] = i;
        }
    }


    return result;
}


int match_results_equal(
    const MatchResult *first,
    const MatchResult *second
)
{
    if (
        first == NULL ||
        second == NULL
    )
    {
        return 0;
    }

    if (
        first->count !=
        second->count
    )
    {
        return 0;
    }

    for (
        int i = 0;
        i < first->count;
        i++
    )
    {
        if (
            first->positions[i] !=
            second->positions[i]
        )
        {
            return 0;
        }
    }

    return 1;
}
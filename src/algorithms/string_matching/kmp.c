#include <string.h>

#include "string_matching.h"


static void build_lps(
    const char *pattern,
    int pattern_length,
    int lps[]
)
{
    int length = 0;

    lps[0] = 0;

    int i = 1;

    while (i < pattern_length)
    {
        if (
            pattern[i] ==
            pattern[length]
        )
        {
            length++;

            lps[i] =
                length;

            i++;
        }
        else
        {
            if (length != 0)
            {
                length =
                    lps[length - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}


MatchResult kmp_search(
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


    int n = (int)strlen(text);
    int m = (int)strlen(pattern);

    if (
        m == 0 ||
        m > n ||
        m > PATTERN_MAX_LENGTH
    )
    {
        return result;
    }


    int lps[PATTERN_MAX_LENGTH];

    build_lps(
        pattern,
        m,
        lps
    );


    int i = 0;
    int j = 0;


    while (i < n)
    {
        if (
            text[i] ==
            pattern[j]
        )
        {
            i++;
            j++;
        }


        if (j == m)
        {
            if (
                result.count <
                MAX_MATCHES
            )
            {
                result.positions[
                    result.count++
                ] = i - j;
            }

            j =
                lps[j - 1];
        }

        else if (
            i < n &&
            text[i] != pattern[j]
        )
        {
            if (j != 0)
            {
                j =
                    lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }


    return result;
}
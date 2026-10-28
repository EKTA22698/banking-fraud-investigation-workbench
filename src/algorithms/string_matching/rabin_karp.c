#include <string.h>

#include "string_matching.h"

#define RK_BASE 256
#define RK_PRIME 101


MatchResult rabin_karp_search(
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
        m > n
    )
    {
        return result;
    }


    int pattern_hash = 0;
    int window_hash = 0;
    int highest_power = 1;


    /*
     * RK_BASE^(m-1) mod RK_PRIME
     */
    for (int i = 0; i < m - 1; i++)
    {
        highest_power =
            (highest_power * RK_BASE)
            % RK_PRIME;
    }


    /*
     * Initial hashes.
     */
    for (int i = 0; i < m; i++)
    {
        pattern_hash =
            (
                RK_BASE * pattern_hash +
                (unsigned char)pattern[i]
            ) % RK_PRIME;

        window_hash =
            (
                RK_BASE * window_hash +
                (unsigned char)text[i]
            ) % RK_PRIME;
    }


    for (
        int i = 0;
        i <= n - m;
        i++
    )
    {
        /*
         * Hash match must still be
         * verified because collisions
         * are possible.
         */
        if (
            pattern_hash ==
            window_hash
        )
        {
            int matched = 1;

            for (int j = 0; j < m; j++)
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
                result.count <
                MAX_MATCHES
            )
            {
                result.positions[
                    result.count++
                ] = i;
            }
        }


        /*
         * Rolling hash.
         */
        if (i < n - m)
        {
            window_hash =
                (
                    RK_BASE *
                    (
                        window_hash -
                        (unsigned char)text[i] *
                        highest_power
                    ) +
                    (unsigned char)text[i + m]
                ) % RK_PRIME;

            if (window_hash < 0)
            {
                window_hash +=
                    RK_PRIME;
            }
        }
    }


    return result;
}
#include <string.h>

#include "string_matching.h"

#define FA_ALPHABET_SIZE 256


static int get_next_state(
    const char *pattern,
    int pattern_length,
    int state,
    unsigned char character
)
{
    /*
     * Direct next-character match.
     */
    if (
        state < pattern_length &&
        character ==
        (unsigned char)pattern[state]
    )
    {
        return state + 1;
    }


    /*
     * Find the longest prefix of
     * pattern that is also suffix
     * after reading this character.
     */
    for (
        int next_state = state;
        next_state > 0;
        next_state--
    )
    {
        if (
            (unsigned char)
            pattern[next_state - 1] !=
            character
        )
        {
            continue;
        }

        int matched = 1;

        for (
            int i = 0;
            i < next_state - 1;
            i++
        )
        {
            int text_index =
                state -
                next_state +
                1 +
                i;

            if (
                text_index < 0 ||
                pattern[i] !=
                pattern[text_index]
            )
            {
                matched = 0;
                break;
            }
        }

        if (matched)
        {
            return next_state;
        }
    }


    return 0;
}


static void build_transition_table(
    const char *pattern,
    int pattern_length,
    int transition
        [PATTERN_MAX_LENGTH + 1]
        [FA_ALPHABET_SIZE]
)
{
    for (
        int state = 0;
        state <= pattern_length;
        state++
    )
    {
        for (
            int character = 0;
            character < FA_ALPHABET_SIZE;
            character++
        )
        {
            transition[state][character] =
                get_next_state(
                    pattern,
                    pattern_length,
                    state,
                    (unsigned char)character
                );
        }
    }
}


MatchResult finite_automaton_search(
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


    int transition
        [PATTERN_MAX_LENGTH + 1]
        [FA_ALPHABET_SIZE];


    build_transition_table(
        pattern,
        m,
        transition
    );


    int state = 0;


    for (int i = 0; i < n; i++)
    {
        state =
            transition
                [state]
                [(unsigned char)text[i]];


        if (state == m)
        {
            if (
                result.count <
                MAX_MATCHES
            )
            {
                result.positions[
                    result.count++
                ] =
                    i - m + 1;
            }
        }
    }


    return result;
}
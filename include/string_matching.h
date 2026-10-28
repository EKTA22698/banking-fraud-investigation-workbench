#ifndef STRING_MATCHING_H
#define STRING_MATCHING_H

#define STRING_MAX_LENGTH 1000
#define PATTERN_MAX_LENGTH 100
#define MAX_MATCHES 100

typedef struct
{
    int positions[MAX_MATCHES];
    int count;
} MatchResult;


/* Naive Pattern Matching */
MatchResult naive_pattern_search(
    const char *text,
    const char *pattern
);


/* Rabin-Karp */
MatchResult rabin_karp_search(
    const char *text,
    const char *pattern
);


/* Finite Automaton */
MatchResult finite_automaton_search(
    const char *text,
    const char *pattern
);


/* Knuth-Morris-Pratt */
MatchResult kmp_search(
    const char *text,
    const char *pattern
);


/* Utility */
int match_results_equal(
    const MatchResult *first,
    const MatchResult *second
);

#endif
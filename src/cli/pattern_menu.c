#include <stdio.h>

#include "pattern_menu.h"
#include "string_matching.h"


static void remove_trailing_newline(
    char text[]
)
{
    if (text == NULL)
    {
        return;
    }

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (
            text[i] == '\n' ||
            text[i] == '\r'
        )
        {
            text[i] = '\0';
            break;
        }
    }
}


static void clear_input_line(void)
{
    int ch;

    while (
        (ch = getchar()) != '\n' &&
        ch != EOF
    )
    {
        /* Clear remaining input */
    }
}


static void print_match_result(
    const MatchResult *result
)
{
    if (result == NULL)
    {
        return;
    }

    if (result->count == 0)
    {
        printf(
            "Pattern not found.\n"
        );

        return;
    }

    printf(
        "Matches found: %d\n",
        result->count
    );

    printf(
        "Match positions: "
    );

    for (
        int i = 0;
        i < result->count;
        i++
    )
    {
        printf(
            "%d ",
            result->positions[i]
        );
    }

    printf("\n");
}


static void print_comparison(
    const char *text,
    const char *pattern
)
{
    MatchResult naive =
        naive_pattern_search(
            text,
            pattern
        );

    MatchResult rabin =
        rabin_karp_search(
            text,
            pattern
        );

    MatchResult automaton =
        finite_automaton_search(
            text,
            pattern
        );

    MatchResult kmp =
        kmp_search(
            text,
            pattern
        );


    printf("\n");
    printf("============================================================\n");
    printf("             STRING MATCHING COMPARISON\n");
    printf("============================================================\n");


    printf("Naive            : ");

    for (
        int i = 0;
        i < naive.count;
        i++
    )
    {
        printf(
            "%d ",
            naive.positions[i]
        );
    }

    printf("\n");


    printf("Rabin-Karp       : ");

    for (
        int i = 0;
        i < rabin.count;
        i++
    )
    {
        printf(
            "%d ",
            rabin.positions[i]
        );
    }

    printf("\n");


    printf("Finite Automaton : ");

    for (
        int i = 0;
        i < automaton.count;
        i++
    )
    {
        printf(
            "%d ",
            automaton.positions[i]
        );
    }

    printf("\n");


    printf("KMP              : ");

    for (
        int i = 0;
        i < kmp.count;
        i++
    )
    {
        printf(
            "%d ",
            kmp.positions[i]
        );
    }

    printf("\n");


    int correct =
        match_results_equal(
            &naive,
            &rabin
        ) &&
        match_results_equal(
            &naive,
            &automaton
        ) &&
        match_results_equal(
            &naive,
            &kmp
        );


    printf(
        "\nCorrectness Check: %s\n",
        correct ? "PASS" : "FAIL"
    );


    if (correct)
    {
        printf(
            "All four algorithms found "
            "identical match positions.\n"
        );
    }


    printf("\nComplexity Summary\n");
    printf("----------------------------------------\n");

    printf(
        "Naive            : O(n*m) worst case\n"
    );

    printf(
        "Rabin-Karp       : O(n+m) average, "
        "O(n*m) worst case\n"
    );

    printf(
        "Finite Automaton : O(n) search "
        "after preprocessing\n"
    );

    printf(
        "KMP              : O(n+m)\n"
    );
}


void run_pattern_menu(void)
{
    char text[
        STRING_MAX_LENGTH + 1
    ];

    char pattern[
        PATTERN_MAX_LENGTH + 1
    ];

    int pattern_choice;


    printf("\n");
    printf("============================================================\n");
    printf("                 FRAUD PATTERN SEARCH\n");
    printf("============================================================\n");


    /*
     * Remove newline left behind by the
     * main-menu scanf().
     */
    clear_input_line();


    printf(
        "Enter transaction/event text:\n"
    );


    if (
        fgets(
            text,
            sizeof(text),
            stdin
        ) == NULL
    )
    {
        printf(
            "Unable to read text.\n"
        );

        return;
    }


    remove_trailing_newline(
        text
    );


    printf(
        "Enter suspicious pattern: "
    );


    if (
        fgets(
            pattern,
            sizeof(pattern),
            stdin
        ) == NULL
    )
    {
        printf(
            "Unable to read pattern.\n"
        );

        return;
    }


    remove_trailing_newline(
        pattern
    );


    if (
        text[0] == '\0' ||
        pattern[0] == '\0'
    )
    {
        printf(
            "Text and pattern cannot be empty.\n"
        );

        return;
    }


    printf("\n");
    printf("1. Naive Pattern Matching\n");
    printf("2. Rabin-Karp\n");
    printf("3. Finite Automaton\n");
    printf("4. KMP\n");
    printf("5. Compare All Algorithms\n");
    printf("0. Back\n");

    printf(
        "Select pattern algorithm: "
    );


    if (
        scanf(
            "%d",
            &pattern_choice
        ) != 1
    )
    {
        printf(
            "Invalid input.\n"
        );

        clear_input_line();

        return;
    }


    MatchResult result;


    if (pattern_choice == 1)
    {
        result =
            naive_pattern_search(
                text,
                pattern
            );

        printf(
            "\nAlgorithm: "
            "Naive Pattern Matching\n"
        );

        print_match_result(
            &result
        );
    }


    else if (pattern_choice == 2)
    {
        result =
            rabin_karp_search(
                text,
                pattern
            );

        printf(
            "\nAlgorithm: Rabin-Karp\n"
        );

        print_match_result(
            &result
        );
    }


    else if (pattern_choice == 3)
    {
        result =
            finite_automaton_search(
                text,
                pattern
            );

        printf(
            "\nAlgorithm: Finite Automaton\n"
        );

        print_match_result(
            &result
        );
    }


    else if (pattern_choice == 4)
    {
        result =
            kmp_search(
                text,
                pattern
            );

        printf(
            "\nAlgorithm: KMP\n"
        );

        print_match_result(
            &result
        );
    }


    else if (pattern_choice == 5)
    {
        print_comparison(
            text,
            pattern
        );
    }


    else if (pattern_choice == 0)
    {
        return;
    }


    else
    {
        printf(
            "Invalid pattern algorithm.\n"
        );
    }
}
#include <stdio.h>

#include "planning_menu.h"
#include "dynamic_programming.h"


void run_planning_menu(void)
{
    InvestigationCase cases[] = {
        {1, 95, 4},
        {2, 60, 2},
        {3, 80, 3},
        {4, 30, 1},
        {5, 90, 5}
    };


    int case_count =
        sizeof(cases) /
        sizeof(cases[0]);


    int available_hours;


    printf("\n");
    printf("============================================================\n");
    printf("              INVESTIGATION PLANNING\n");
    printf("============================================================\n");


    printf(
        "%-10s %-15s %-20s\n",
        "CASE",
        "RISK VALUE",
        "TIME REQUIRED"
    );


    printf(
        "------------------------------------------------------------\n"
    );


    for (
        int i = 0;
        i < case_count;
        i++
    )
    {
        printf(
            "F%-9d %-15d %-5d hours\n",
            cases[i].id,
            cases[i].risk_value,
            cases[i].investigation_time
        );
    }


    printf(
        "------------------------------------------------------------\n"
    );


    printf(
        "Enter available investigation hours: "
    );


    if (
        scanf(
            "%d",
            &available_hours
        ) != 1
    )
    {
        printf(
            "Invalid input.\n"
        );

        while (getchar() != '\n')
        {
            /* Clear invalid input */
        }

        return;
    }


    if (
        available_hours <= 0 ||
        available_hours > MAX_CAPACITY
    )
    {
        printf(
            "Available hours must be between "
            "1 and %d.\n",
            MAX_CAPACITY
        );

        return;
    }


    KnapsackResult result =
        solve_zero_one_knapsack(
            cases,
            case_count,
            available_hours
        );


    printf("\n");
    printf("============================================================\n");
    printf("             OPTIMAL INVESTIGATION PLAN\n");
    printf("============================================================\n");


    int total_time = 0;


    /*
     * Backtracking stores selected
     * indices in reverse order.
     */
    for (
        int i =
            result.selected_count - 1;
        i >= 0;
        i--
    )
    {
        int index =
            result.selected_indices[i];


        printf(
            "Case F%d  | Risk = %d | "
            "Time = %d hours\n",
            cases[index].id,
            cases[index].risk_value,
            cases[index].investigation_time
        );


        total_time +=
            cases[index]
                .investigation_time;
    }


    printf(
        "------------------------------------------------------------\n"
    );


    printf(
        "Available Hours   : %d\n",
        available_hours
    );


    printf(
        "Hours Used        : %d\n",
        total_time
    );


    printf(
        "Maximum Risk Value: %d\n",
        result.maximum_risk
    );


    printf(
        "Cases Selected    : %d\n",
        result.selected_count
    );


    printf(
        "============================================================\n"
    );
}
#ifndef DYNAMIC_PROGRAMMING_H
#define DYNAMIC_PROGRAMMING_H

#define MAX_CASES 50
#define MAX_CAPACITY 100

typedef struct
{
    int id;
    int risk_value;
    int investigation_time;
} InvestigationCase;

typedef struct
{
    int maximum_risk;
    int selected_count;
    int selected_indices[MAX_CASES];
} KnapsackResult;


KnapsackResult solve_zero_one_knapsack(
    const InvestigationCase cases[],
    int case_count,
    int available_hours
);

#endif
#ifndef GREEDY_H
#define GREEDY_H

#define MAX_ACTIVITIES 50
#define MAX_HUFFMAN_CHARS 256
#define MAX_FRACTIONAL_ITEMS 50

typedef struct
{
    int id;
    double risk_value;
    double investigation_time;
} FractionalItem;

typedef struct
{
    int id;
    double fraction;
    double time_used;
    double risk_obtained;
} FractionalSelection;

typedef struct
{
    FractionalSelection selected[
        MAX_FRACTIONAL_ITEMS
    ];

    int selected_count;

    double total_time;
    double maximum_risk;
} FractionalKnapsackResult;

typedef struct
{
    int id;
    int start;
    int finish;
} Activity;

typedef struct
{
    int activity_id;
    int resource_id;
} IntervalAssignment;


/* Activity Selection */
int activity_selection(
    Activity activities[],
    int count,
    Activity selected[]
);


/* Interval Partitioning */
int interval_partitioning(
    Activity activities[],
    int count,
    IntervalAssignment assignments[]
);


/* Huffman Coding */
void run_huffman_demo(
    const char *text
);
/* Fractional Knapsack */
FractionalKnapsackResult
fractional_knapsack(
    const FractionalItem items[],
    int count,
    double capacity
);
#endif
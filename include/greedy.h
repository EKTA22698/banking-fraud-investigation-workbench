#ifndef GREEDY_H
#define GREEDY_H

#define MAX_ACTIVITIES 50
#define MAX_HUFFMAN_CHARS 256

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

#endif
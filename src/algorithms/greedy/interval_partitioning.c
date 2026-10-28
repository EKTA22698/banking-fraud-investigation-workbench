#include "greedy.h"

typedef struct
{
    int finish_time;
    int resource_id;
} ResourceHeapNode;


static void swap_activity_interval(
    Activity *first,
    Activity *second
)
{
    Activity temp = *first;
    *first = *second;
    *second = temp;
}


static void sort_by_start_time(
    Activity activities[],
    int count
)
{
    int i;
    int j;

    for (i = 1; i < count; i++)
    {
        j = i;

        while (
            j > 0 &&
            activities[j - 1].start >
            activities[j].start
        )
        {
            swap_activity_interval(
                &activities[j - 1],
                &activities[j]
            );

            j--;
        }
    }
}


static void swap_heap_nodes(
    ResourceHeapNode *first,
    ResourceHeapNode *second
)
{
    ResourceHeapNode temp = *first;
    *first = *second;
    *second = temp;
}


static void heapify_up(
    ResourceHeapNode heap[],
    int index
)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;

        if (
            heap[parent].finish_time <=
            heap[index].finish_time
        )
        {
            break;
        }

        swap_heap_nodes(
            &heap[parent],
            &heap[index]
        );

        index = parent;
    }
}


static void heapify_down(
    ResourceHeapNode heap[],
    int size,
    int index
)
{
    while (1)
    {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (
            left < size &&
            heap[left].finish_time <
            heap[smallest].finish_time
        )
        {
            smallest = left;
        }

        if (
            right < size &&
            heap[right].finish_time <
            heap[smallest].finish_time
        )
        {
            smallest = right;
        }

        if (smallest == index)
        {
            break;
        }

        swap_heap_nodes(
            &heap[index],
            &heap[smallest]
        );

        index = smallest;
    }
}


static void heap_push(
    ResourceHeapNode heap[],
    int *size,
    ResourceHeapNode node
)
{
    heap[*size] = node;

    heapify_up(
        heap,
        *size
    );

    (*size)++;
}


int interval_partitioning(
    Activity activities[],
    int count,
    IntervalAssignment assignments[]
)
{
    ResourceHeapNode heap[MAX_ACTIVITIES];

    int heap_size = 0;
    int resource_count = 0;
    int i;

    if (count <= 0)
    {
        return 0;
    }

    sort_by_start_time(
        activities,
        count
    );

    for (i = 0; i < count; i++)
    {
        /*
         * The root is the investigator
         * becoming available earliest.
         */
        if (
            heap_size > 0 &&
            heap[0].finish_time <=
            activities[i].start
        )
        {
            int resource_id =
                heap[0].resource_id;

            assignments[i].activity_id =
                activities[i].id;

            assignments[i].resource_id =
                resource_id;

            /*
             * Same investigator receives
             * the new case and therefore
             * gets a new finish time.
             */
            heap[0].finish_time =
                activities[i].finish;

            heapify_down(
                heap,
                heap_size,
                0
            );
        }
        else
        {
            /*
             * Everyone is busy.
             * Create another investigator.
             */
            resource_count++;

            assignments[i].activity_id =
                activities[i].id;

            assignments[i].resource_id =
                resource_count;

            ResourceHeapNode node;

            node.finish_time =
                activities[i].finish;

            node.resource_id =
                resource_count;

            heap_push(
                heap,
                &heap_size,
                node
            );
        }
    }

    return resource_count;
}
#include "divide_conquer.h"

int find_celebrity(
    const int matrix[][10],
    int count
)
{
    if (count <= 0 || count > 10)
    {
        return -1;
    }

    int candidate = 0;

    /*
     * Elimination phase.
     */
    for (int person = 1; person < count; person++)
    {
        if (matrix[candidate][person] == 1)
        {
            candidate = person;
        }
    }

    /*
     * Verification phase.
     */
    for (int person = 0; person < count; person++)
    {
        if (person == candidate)
        {
            continue;
        }

        if (matrix[candidate][person] == 1 ||
            matrix[person][candidate] == 0)
        {
            return -1;
        }
    }

    return candidate;
}
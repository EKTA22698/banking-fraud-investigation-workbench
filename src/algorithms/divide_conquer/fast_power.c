#include "divide_conquer.h"

long long fast_power(
    long long base,
    unsigned int exponent
)
{
    if (exponent == 0)
    {
        return 1;
    }

    long long half = fast_power(
        base,
        exponent / 2
    );

    if (exponent % 2 == 0)
    {
        return half * half;
    }

    return base * half * half;
}
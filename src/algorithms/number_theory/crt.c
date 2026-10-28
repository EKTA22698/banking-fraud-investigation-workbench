#include "number_theory.h"


static long long gcd(
    long long first,
    long long second
)
{
    while (second != 0)
    {
        long long temporary =
            first % second;

        first = second;
        second = temporary;
    }

    return first;
}


static long long extended_gcd(
    long long a,
    long long b,
    long long *x,
    long long *y
)
{
    if (b == 0)
    {
        *x = 1;
        *y = 0;

        return a;
    }

    long long x1;
    long long y1;

    long long divisor =
        extended_gcd(
            b,
            a % b,
            &x1,
            &y1
        );

    *x = y1;

    *y =
        x1 -
        (a / b) * y1;

    return divisor;
}


static long long modular_inverse(
    long long value,
    long long modulus
)
{
    long long x;
    long long y;

    long long divisor =
        extended_gcd(
            value,
            modulus,
            &x,
            &y
        );

    if (divisor != 1)
    {
        return -1;
    }

    return (
        (x % modulus) +
        modulus
    ) % modulus;
}


CRTResult chinese_remainder_theorem(
    const long long remainders[],
    const long long moduli[],
    int count
)
{
    CRTResult result;

    result.solution = 0;
    result.modulus_product = 0;
    result.valid = 0;

    if (
        remainders == 0 ||
        moduli == 0 ||
        count <= 0 ||
        count > CRT_MAX_EQUATIONS
    )
    {
        return result;
    }

    /*
     * This implementation assumes
     * pairwise coprime moduli.
     */
    for (int i = 0; i < count; i++)
    {
        if (moduli[i] <= 1)
        {
            return result;
        }

        for (
            int j = i + 1;
            j < count;
            j++
        )
        {
            if (
                gcd(
                    moduli[i],
                    moduli[j]
                ) != 1
            )
            {
                return result;
            }
        }
    }


    long long product = 1;

    for (int i = 0; i < count; i++)
    {
        product *=
            moduli[i];
    }


    long long solution = 0;

    for (int i = 0; i < count; i++)
    {
        long long partial_product =
            product / moduli[i];

        long long inverse =
            modular_inverse(
                partial_product %
                moduli[i],
                moduli[i]
            );

        if (inverse == -1)
        {
            return result;
        }

        solution +=
            remainders[i] *
            partial_product *
            inverse;
    }


    solution =
        ((solution % product) + product)
        % product;


    result.solution =
        solution;

    result.modulus_product =
        product;

    result.valid = 1;

    return result;
}
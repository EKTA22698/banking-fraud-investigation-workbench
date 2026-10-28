#ifndef NUMBER_THEORY_H
#define NUMBER_THEORY_H

#define CRT_MAX_EQUATIONS 20

typedef struct
{
    long long solution;
    long long modulus_product;
    int valid;
} CRTResult;

CRTResult chinese_remainder_theorem(
    const long long remainders[],
    const long long moduli[],
    int count
);

#endif
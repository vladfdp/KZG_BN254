#include <stdint.h>
#include "int256.h"

#ifndef FR_H
#define FR_H

typedef struct Fr{
    int256 num;
}Fr;

const static int256 R = {0x30644E72E131A029,0xB85045B68181585D,0x2833E84879B97091,0x43E1F593F0000001};

Fr Fr_from_int(uint64_t n);

Fr Fr_from_4_int(uint64_t n1, uint64_t n2, uint64_t n3, uint64_t n4);

Fr get_rand_Fr();

Fr Fr_zero();

Fr Fr_one();

int Fr_equal(Fr a, Fr b);

Fr Fr_add(Fr a, Fr b);

Fr Fr_mul(Fr a, Fr b);

Fr Fr_mul_daa(Fr a, Fr b);

Fr Fr_mul_mq(Fr a, Fr b);

Fr Fr_mul_mq2(Fr a, Fr b);

Fr Fr_mul_original(Fr a, Fr b);

Fr Fr_sub(Fr a, Fr b);

Fr Fr_opp(Fr x);

Fr Fr_exp(Fr base, int256 exponent);

void print_Fr(Fr x);

Fr Fr_inv(Fr x);

Fr Fr_div(Fr a,Fr b);

#endif
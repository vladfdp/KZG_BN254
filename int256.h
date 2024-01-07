#include <stdint.h>

#ifndef INT_256_H
#define INT_256_H

typedef struct int256{
    uint64_t u3;
    uint64_t u2;
    uint64_t u1;
    uint64_t u0;
}int256;

int256 add_256(int256 a, int256 b);

int cmp_256(int256 a, int256 b);

int256 sub_256(int256 a, int256 b);

int256 shift_right_256(int256 x);

int256 zero_256();

uint64_t get_32_slice(int256 x, int i);

void print_256(int256 x);



#endif
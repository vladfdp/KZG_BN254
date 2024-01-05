#include <stdint.h>
#include "int256.h"

#ifndef INT_512_H
#define INT_512_H

typedef struct int512{
    uint64_t u7;
    uint64_t u6;
    uint64_t u5;
    uint64_t u4;
    uint64_t u3;
    uint64_t u2;
    uint64_t u1;
    uint64_t u0;
}int512;


int512 add_512(int512 a, int512 b);

int cmp_512(int512 a, int512 b);

int512 sub_512(int512 a, int512 b);

int512 mul_from_256(int256 a, int256 b);

#endif
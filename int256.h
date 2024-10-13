#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifndef INT_256_H
#define INT_256_H

typedef struct int256{
    uint64_t u3;
    uint64_t u2;
    uint64_t u1;
    uint64_t u0;
}int256;

typedef struct QR{
    int256 quotient;
    int256 rest;
}QR;

int256 rand_256();


int256 add_256(int256 a, int256 b);

int cmp_256(int256 a, int256 b);

int256 sub_256(int256 a, int256 b);

int256 shift_right_256(int256 x);

int256 shift_left_256(int256 x);

int256 zero_256();

uint64_t get_32_slice(int256 x, int i);

void print_256(int256 x);

QR euclidean_div_256(int256 a ,int256 b);



#endif


#ifdef __cplusplus
}
#endif
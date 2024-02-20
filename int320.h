#include <stdint.h>
#include "int256.h"

#ifndef INT_320_H
#define INT_320_H

typedef struct int320{
    uint64_t u4;
    uint64_t u3;
    uint64_t u2;
    uint64_t u1;
    uint64_t u0;
}int320;


int320 add_320(int320 a, int320 b);

int320 sub_320(int320 a, int320 b);

int cmp_320(int320 a, int320 b);

int320 mul_by_32_320( int256 x, uint64_t slice);

int320 mul_by_64_320( int256 x, uint64_t slice);

int320 shift_right_320(int320 x);

int320 shift_left_320(int320 x);

int320 shift_left_by_32_320(int320 x);

int320 shift_left_320_by_n(int320 x, int n);

int320 zero_320();

//uint64_t get_32_slice(int320 x, int i);

void print_320(int320 x);


int256 modulo_320(int320 x, int256 mod);

int256 modulo_33(int320 x, int320 mod_shifted);




#endif
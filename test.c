#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Fp.h"
#include "int256.h"
#include "int512.h"







int main(){

    uint64_t f = 0xFFFFFFFFFFFFFFFF;
    Fp A1 = {{0,0,0,24}};
    Fp B1 = {{10,10,10,1}};
    Fp C1 = Fp_add(A1,B1);

    print_Fp(A1);
    print_Fp(B1);
    print_Fp(C1);
    

   
    return 0;
}
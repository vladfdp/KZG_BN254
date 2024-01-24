#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "Fr.h"
#include "int256.h"
#include "int512.h"
#include "EC.h"
#include "TwistedG2.h"

TwistedG2 G2_twist(G2 P){

    Fp12 omega_squared_inv = Fp12_zero();
    Fp12 omega_cubed_inv = Fp12_zero();

    omega_squared_inv.x0.x2.x0 = {0x2e9f1362305ea3ab,0x50ca36acb4f65e7f,0xa1928902b8ea8194,0x8e3855034733bbd1};
    omega_squared_inv.x0.x2.x0 = {0x20753adca9c6bfb8,0x1499be5e509e8f8f,0xf21b7c8d3cb039cf,0x1ef69c66bce9b020};

    omega_cubed_inv.x1.x1.x0 = {0x2e9f1362305ea3ab,0x50ca36acb4f65e7f,0xa1928902b8ea8194,0x8e3855034733bbd1};
    omega_cubed_inv.x1.x1.x1 = {0x20753adca9c6bfb8,0x1499be5e509e8f8f,0xf21b7c8d3cb039cf,0x1ef69c66bce9b020};

    TwistedG2 ans;

    ans.x = Fp12_mul(P.x, omega_squared_inv).x0.x0;
    ans.y = Fp12_mul(P.y, omega_cubed_inv).x0.x0;

    return ans;
}

G2 G2_untwist(TwistedG2 P){

    Fp12 omega_squared = Fp12_zero();
    Fp12 omega_cubed = Fp12_zero();

    omega_squared.x0.x1 = Fp2_one();
    omega_cubed.x1.x1 = Fp2_one();
    
    G2 ans;
    ans.x = Fp12_mul_by_Fp2(omega_squared, P.x);
    ans.y = Fp12_mul_by_Fp2(omega_cubed, P.y);

    return ans;

}
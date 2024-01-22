#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "int256.h"
#include "int512.h"
#include "Fr.h"
#include "EC.h"

const unsigned int MAX_DEGREE = 100;

int main(){

    Fr alpha = Fr_from_int(54870987);//rendre ca random

    Fp G_x = {0x187CC1E6F77C59DD,0x29AC8214D5733697,0xB33601F06D087C26,0xC1D8F343FA92FFC2};
    Fp G_y = {0x197C3E3702A874C3,0x424634A83761F37A,0xD8E8E8E4BE86082B,0xC8D9C9E6FE14275E};

    FILE *srs_g1;
    srs_g1 = fopen("SRS_G1.bin","wb");
    FILE *srs_g2;
    srs_g2 = fopen("SRS_G2.bin","wb");


    G2 H = {Fp12_one(), Fp12_zero()}; //trouver un H dans G2
    fwrite(&H, sizeof(G2), 1, srs_g2); 
    G2 alpha_H = G2_mul_scal(H,alpha);
    fwrite(&alpha_H, sizeof(G2), 1, srs_g2); 


    G1 G = {G_x, G_y};
    fwrite(&G, sizeof(G1), 1, srs_g1);

    for(unsigned int i = 0; i < MAX_DEGREE; i++)
    {
    G = G1_mul_scal(G, alpha);
    fwrite(&G, sizeof(G1), 1, srs_g1); 
    }

    fclose(srs_g1);
    fclose(srs_g2); 
  
    return 0;

}
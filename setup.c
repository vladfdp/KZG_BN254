#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "int256.h"
#include "int512.h"
#include "Fr.h"
#include "EC.h"
#include "TwistedG2.h"


const unsigned int MAX_DEGREE = 1000;





int main(){

    clock_t start, end;
    double setup_time;
    start = clock();

    Fr alpha = get_rand_Fr();

    Fp G_x = {0x187CC1E6F77C59DD,0x29AC8214D5733697,0xB33601F06D087C26,0xC1D8F343FA92FFC2};
    Fp G_y = {0x197C3E3702A874C3,0x424634A83761F37A,0xD8E8E8E4BE86082B,0xC8D9C9E6FE14275E};

    Fp6 H_x;
    Fp12 H_y;

    Fp x_a = {0x2351a862f99a2e05,0x202db891d078a76e,0x4316b508b69c17de,0x69b71bdceea9943f};
    Fp x_b = {0x1b09333d8ffaf56,0x702d0cdb0c731dc1,0xe806c87eac937733,0xc82bd78d428f66ce};

    Fp y_c = {0x2c6977d27d199ba8,0xbb2a4ffc86e57425,0x4b88246b19977d4,0xc52c2436273f7df1};
    Fp y_d = {0x2d5991dc9820b9cb,0xeab5aa224869a316,0x859c7b603a8eff71,0x6670a2dca426b521};


    H_x.x0 = Fp2_zero();
    H_x.x2 = Fp2_zero();
    H_x.x1.x0 = x_a;
    H_x.x1.x1 = x_b;

    H_y.x0 = Fp6_zero();
    H_y.x1.x0 = Fp2_zero();
    H_y.x1.x2 = Fp2_zero();

    H_y.x1.x1.x0 = y_c;
    H_y.x1.x1.x1 = y_d;



    FILE *srs_g1;
    srs_g1 = fopen("SRS_G1.bin","wb");
    FILE *srs_g2;
    srs_g2 = fopen("SRS_G2.bin","wb");


    G2 H = {H_x, H_y};
    fwrite(&H, sizeof(G2), 1, srs_g2); 
    G2 alpha_H = G2_mul_by_int_twist(H, alpha.num);
    fwrite(&alpha_H, sizeof(G2), 1, srs_g2); 


    G1 G = {G_x, G_y};
    fwrite(&G, sizeof(G1), 1, srs_g1);

    for(unsigned int i = 0; i < MAX_DEGREE; i++)
    {
    G = G1_mul_by_int(G, alpha.num);
    fwrite(&G, sizeof(G1), 1, srs_g1); 
    }

    fclose(srs_g1);
    fclose(srs_g2);


    end = clock();
    setup_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("le setup pour un degré max d = %d prend %f secondes\n", MAX_DEGREE, setup_time);
  
    return 0;

}
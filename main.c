#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "Fr.h"
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "Poly.h"
#include "int256.h"
#include "int512.h"
#include "EC.h"
#include "Pairing.h"
#include "KZG.h"
#include "TwistedG2.h"

void protocol(){

    clock_t start, end;

    for (int size = 10; size < 200 + 1 ; size += 10) // on teste le protocole pour des poly de differents degrées
    {
    
    

        Poly poly = Poly_init(size);

        for (int i = 0; i < size + 1; i++)
        {
            poly.coeffs[i] = get_rand_Fr();         //on crée un polynome de degrée size avec des coefficients au hasard
        }
        

        double commit_time;

        start = clock();

        G1 comm = commit(poly);
        
        end = clock();
        commit_time = ((double) (end - start)) / CLOCKS_PER_SEC;



        Fr index = Fr_from_int(668);
        Fr eval = Poly_eval(poly, index);       //on evalue le polynome a index
        Fr eval2 = Fr_add(eval, Fr_from_int(1));// fausse evaluation

        
        double prove_time;

        start = clock();

        G1 proof = create_witness(poly, index, eval);    //on crée une preuve
        G1 proof2 = create_witness(poly, index, eval2);  //et une fausse

        end = clock();
        prove_time = ((double) (end - start)) / CLOCKS_PER_SEC;
        
        

        printf("pour des polynome de taille %d:\n",size);
        
        double verify_time;
        
        start = clock();

        printf("verifier une preuve valable donne: %d\n",verify(comm, proof, index, eval));        //on verifie la preuve
        printf("verifier une preuve non valable donne: %d\n",verify(comm, proof2, index, eval2));  //et la fausse preuve

        end = clock();
        verify_time = ((double) (end - start)) / CLOCKS_PER_SEC;


        printf("\nTemps de mise en gage: %f sec \n", commit_time);
        printf("Temps de preuve: %f sec \n", prove_time/2);
        printf("Temps de verification: %f sec \n\n\n", verify_time/2);

        free_Poly(poly);

    }
}

void benchmark(){

    clock_t start, end;

    FILE *srs_g2;

    if ((srs_g2 = fopen("SRS_G2.bin","rb")) == NULL){
       printf("Missing SRS, run setup using 'make setup'");

       exit(1);
    }

    FILE *srs_g1;

    if ((srs_g1 = fopen("SRS_G1.bin","rb")) == NULL){
       printf("Missing SRS, run setup using 'make setup'");

       exit(1);
    }

    G2 H;
    fread(&H, sizeof(G2), 1, srs_g2);

    G1 G;
    fread(&G, sizeof(G1), 1, srs_g1);
    
    double Pairing_time = 0;
    double G1_mul_time = 0;
    double G2_mul_time = 0;
    double G2_mul_twist_time = 0;
    double final_exp_time = 0;

    int sample_size = 100;

    for (int i = 0; i < sample_size; i++)
    {
        Fr rand = get_rand_Fr();

        start = clock();
        G1 P = G1_mul_by_int(G, rand.num);              //mult dans G1
        end = clock();
        G1_mul_time += ((double) (end - start)) / CLOCKS_PER_SEC;


        start = clock();
        G2 Q = G2_mul_by_int(H, rand.num);              //mult dans G2
        end = clock();
        G2_mul_time += ((double) (end - start)) / CLOCKS_PER_SEC;

        start = clock();
        G2 Q2 = G2_mul_by_int_twist(H, rand.num);              //mult dans G2 avec twist
        end = clock();
        G2_mul_twist_time += ((double) (end - start)) / CLOCKS_PER_SEC;

        if (!G2_equal(Q, Q2))
        {
            printf("erreur");
        }
        

        start = clock();
        Fp12 pairing = Tate_pairing(P,Q);
        end = clock();
        Pairing_time += ((double) (end - start)) / CLOCKS_PER_SEC;


        start = clock();
        final_exp(pairing);
        end = clock();
        final_exp_time += ((double) (end - start)) / CLOCKS_PER_SEC;
    }
    
    printf("\nTemps de multiplication moyen dans G1: %f sec \n", G1_mul_time/sample_size);
    printf("Temps de multiplication moyen dans G2: %f sec \n", G2_mul_time/sample_size);
    printf("Temps de multiplication moyen dans G2 avec twist: %f sec \n", G2_mul_twist_time/sample_size);
    printf("Temps moyen de calcul du Pairing de Tate: %f sec \n", Pairing_time/sample_size);
    printf("Dont exponentiation finale: %f sec \n", final_exp_time/sample_size);
}




int main(){

    protocol();

    //benchmark();

    return 0;
}
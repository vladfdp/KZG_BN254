#include "int512.h"


int cmp_512(int512 a, int512 b){ // verifie si a est plus grand ou egal a b
    if (a.u7 == b.u7){
        if (a.u6 == b.u6){
            if (a.u5 == b.u5){
                if (a.u4 == b.u4){
                    if (a.u3 == b.u3){
                        if (a.u2 == b.u2){
                            if (a.u1 == b.u1){
                                return a.u0 >= b.u0;
                            }
                            return a.u1 > b.u1;
                        }
                        return a.u2 > b.u2;
                    }
                    return a.u3 > b.u3;
                }
                return a.u4 > b.u4;
            }
            return a.u5 > b.u5;
        }
        return a.u6 > b.u6;
    }
    return a.u7 > b.u7;
}

int512 add_512(int512 a, int512 b){
    
    int512 ans = {a.u7 + b.u7,
    a.u6 + b.u6,
    a.u5 + b.u5,
    a.u4 + b.u4,
    a.u3 + b.u3,
    a.u2 + b.u2,
    a.u1 + b.u1,
    a.u0 + b.u0,
    };
    
    ans.u1 += (ans.u0 < a.u0) ? 1 : 0;
    ans.u2 += (ans.u1 < a.u1) || (ans.u1 < b.u1) ? 1 : 0;
    ans.u3 += (ans.u2 < a.u2) || (ans.u2 < b.u2) ? 1 : 0;
    ans.u4 += (ans.u3 < a.u3) || (ans.u3 < b.u3) ? 1 : 0;
    ans.u5 += (ans.u4 < a.u4) || (ans.u4 < b.u4) ? 1 : 0;
    ans.u6 += (ans.u5 < a.u5) || (ans.u5 < b.u5) ? 1 : 0;
    ans.u7 += (ans.u6 < a.u6) || (ans.u6 < b.u6) ? 1 : 0;


    return ans;  
}

int512 sub_512(int512 a, int512 b){       //on assume que a > b

    int512 ans = {a.u3 - b.u3,
    a.u2 - b.u2,
    a.u1 - b.u1,
    a.u0 - b.u0,
    };
    ans.u1 -= (ans.u0 > a.u0) ? 1 : 0; //effectue la retenue inverse
    ans.u2 -= (ans.u1 > a.u1) || (ans.u1 > b.u1) ? 1 : 0;
    ans.u3 -= (ans.u2 > a.u2) || (ans.u2 > b.u2) ? 1 : 0;
    ans.u4 -= (ans.u3 > a.u3) || (ans.u3 > b.u3) ? 1 : 0;
    ans.u5 -= (ans.u4 > a.u4) || (ans.u4 > b.u4) ? 1 : 0;
    ans.u6 -= (ans.u5 > a.u5) || (ans.u5 > b.u5) ? 1 : 0;
    ans.u7 -= (ans.u6 > a.u6) || (ans.u6 > b.u6) ? 1 : 0;

    return ans;

}

int512 zero(){
    return {0,0,0,0,0,0,0,0};
}



int512 mul_from_256(int256 a, int256 b){



    for (int i = 0; i < 8; i++)
    {
        int slice = get_32_slice(b,i);
        sum = add(sum,mul_by_32());
    }
    





}





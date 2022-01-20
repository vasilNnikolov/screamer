#include "utilities.h"

unsigned int getRandomInteger(unsigned int* seed){
    unsigned int a = 16807;
    unsigned int m = 257;
    *seed = (a * (*seed)) % m;
    return (unsigned int)(*seed);
}

void beep(){
    
}
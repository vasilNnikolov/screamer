#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "utilities.h"
#include "projectConstants.h"

unsigned int getRandomInteger(unsigned int* seed){
    unsigned int a = 1687;
    unsigned int m = 257;
    *seed = (a * (*seed)) % m;
    return (unsigned int)(*seed);
}

void beep(){
    short n_beeps = getRandomInteger(&seed) % 5 + 3;
    for(short i = 0; i < 2*n_beeps; i++){
        PORTB ^= (1 << BEEP_PIN_1) | (1 << BEEP_PIN_2);
        _delay_ms(500);
    }    
}
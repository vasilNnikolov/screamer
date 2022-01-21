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
    for(short i = 0; i < 30; i++){
        PORTB ^= (1 << LED_PIN);
        _delay_ms(200);
    }    
}
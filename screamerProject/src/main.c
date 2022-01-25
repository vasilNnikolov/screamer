#include "utilities.h"
#include "projectConstants.h"


int main(){
    _delay_ms(2000); // to debounce power supply

    //flash the led to indicate the circuit has started working
    DDRB |= (1 << BEEP_PIN_1) | (1 << BEEP_PIN_2);
    PORTB ^= (1 << BEEP_PIN_1) | (1 << BEEP_PIN_2);
    _delay_ms(4000);
    PORTB ^= (1 << BEEP_PIN_1) | (1 << BEEP_PIN_2);

    setupInterrupt();
    while(1){
        goToSleep();
    }
}

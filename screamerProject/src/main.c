#include "utilities.h"
#include "projectConstants.h"


int main(){
    _delay_ms(2000); // to debounce power supply
    //beep to indicate the circuit has started working
    DDRB |= (1 << BEEP_PIN_1) | (1 << BEEP_PIN_2);
    PORTB ^= (1 << BEEP_PIN_1) | (1 << BEEP_PIN_2);
    _delay_ms(4000);
    PORTB ^= (1 << BEEP_PIN_1) | (1 << BEEP_PIN_2);

    setupInterrupt();
    unsigned int periodsLeft = (3600*INITIAL_QUIET_PERIOD_H)/(TIME_INTERVAL_S);
    while(1){
        goToSleep();

        //disable interrupts 
        cli();

        _delay_ms(100); // to see the periods ticking
        dischargeCapacitor();
        if(periodsLeft <= 0){
            beep();
            //pick new periods left
            periodsLeft = getRandomInteger(&seed)*MAX_TIME_BETWEEN_BEEPS_M*60/(255*TIME_INTERVAL_S) + 1; 
        }
        periodsLeft--;

        // enable pcint
        setupInterrupt();
    }
}

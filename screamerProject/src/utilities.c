#include "utilities.h"
#include "projectConstants.h"

void setupInterrupt(){
    SREG |= (1 << SREG_I); 
    GIMSK |= (1 << PCIE);
    PCMSK |= (1 << INTERRUPT_PIN);
}

void goToSleep(){
    MCUCR |= (1 << SE); //sleep enable
    MCUCR |= (1 << SM1); // selecting power down
    sleep_cpu();
}

void dischargeCapacitor(){
    //disable pcint
    GIMSK &= ~(1 << PCIE);

    DDRB |= (1 << NPN_TRANSISTOR_BASE_PIN);
    PORTB &= ~(1 << NPN_TRANSISTOR_BASE_PIN);

    DDRB |= (1 << INTERRUPT_PIN); // make interrupt pin output
    PORTB &= ~(1 << INTERRUPT_PIN); // set interrupt pin off

    _delay_ms(CAP_DISCHARGE_TIME_MS);
    
    DDRB &= ~(1 << INTERRUPT_PIN); //make interrupt pin input
    PORTB &= ~(1 << INTERRUPT_PIN); //disables pullup resistor on interrupt pin

    DDRB &= ~(1 << NPN_TRANSISTOR_BASE_PIN);
    PORTB &= ~(1 << NPN_TRANSISTOR_BASE_PIN);

    // enable pcint
    setupInterrupt();
}

void beep(){
    short n_beeps = 5;
    while(n_beeps > 0){
        PORTB |= (1 << BEEP_PIN_1) | (1 << BEEP_PIN_2);
        _delay_ms(BEEP_TIME_ON);
        PORTB &= ~((1 << BEEP_PIN_1) | (1 << BEEP_PIN_2));
        _delay_ms(BEEP_TIME_OFF);
        n_beeps--;
    }
}

ISR(PCINT0_vect){
    dischargeCapacitor();
    beep();
    goToSleep();
}
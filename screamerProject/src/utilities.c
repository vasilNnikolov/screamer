#include "utilities.h"
#include "projectConstants.h"

void setupInterrupt(){
    sei();
    GIMSK |= (1 << PCIE);
    PCMSK |= (1 << INTERRUPT_PIN);
}

void goToSleep(){
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_cpu();
}

void dischargeCapacitor(){
    DDRB |= (1 << NPN_TRANSISTOR_BASE_PIN);
    PORTB &= ~(1 << NPN_TRANSISTOR_BASE_PIN);

    DDRB |= (1 << INTERRUPT_PIN); // make interrupt pin output
    PORTB &= ~(1 << INTERRUPT_PIN); // set interrupt pin off

    _delay_ms(CAP_DISCHARGE_TIME_MS);
    
    DDRB &= ~(1 << INTERRUPT_PIN); //make interrupt pin input
    PORTB &= ~(1 << INTERRUPT_PIN); //disables pullup resistor on interrupt pin

    DDRB &= ~(1 << NPN_TRANSISTOR_BASE_PIN);
    PORTB &= ~(1 << NPN_TRANSISTOR_BASE_PIN);
}

void beep(){
    short n_beeps = 3;
    while(n_beeps > 0){
        PORTB |= (1 << BEEP_PIN_1) | (1 << BEEP_PIN_2);
        _delay_ms(BEEP_TIME_ON);
        PORTB &= ~((1 << BEEP_PIN_1) | (1 << BEEP_PIN_2));
        _delay_ms(BEEP_TIME_OFF);
        n_beeps--;
    }
}

ISR(PCINT0_vect){
    //disable interrupts 
    cli();

    _delay_ms(500); // TODO remove after testing is complete
    dischargeCapacitor();

    beep();

    // enable pcint
    setupInterrupt();
}
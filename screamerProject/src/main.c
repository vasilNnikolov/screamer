#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "utilities.h"
#include "projectConstants.h"

void setPCINT(){
    //setup PCINT on INTERRUPT_PIN
    DDRB &= ~(1 << INTERRUPT_PIN); // sets interrupt_pin as input
    PORTB &= ~(1 << INTERRUPT_PIN); //removes pullup resistor from the interrupt pin
    GIMSK |= (1 << PCIE);
    PCMSK |= (1 << INTERRUPT_PIN);

    DDRB &= ~(1 << NPN_TRANSISTOR_BASE_PIN); //set npn base pin to input
    PORTB &= ~(1 << NPN_TRANSISTOR_BASE_PIN); //removes pullup resistor from the npn base pin
    sei(); //enables interrupts globally
}

void dischargeCapacitor(){
    cli(); // disables interrupts globally, so when the cap is discharged there is no interrupt
    
    GIMSK &= ~(1 << PCIE);
    PCMSK &= ~(1 << INTERRUPT_PIN);//totally removes pcint settings, otherwise another interrupt fires after discharge

    DDRB |= 1 << NPN_TRANSISTOR_BASE_PIN; //turn base pin to output
    PORTB &= ~(1 << NPN_TRANSISTOR_BASE_PIN); //turn off base pin to turn off npn transistor
    
    DDRB |= 1 << INTERRUPT_PIN; //turn interrupt pin to output
    PORTB &= ~(1 << INTERRUPT_PIN); //turn interrupt pin off, to discharge the capacitor
    _delay_ms(1000); //discharge capacitor during this time

    setPCINT();
}

void enterSleep(){  
    MCUCR |= (1 << SM1); // sets powerdown mode
    MCUCR |= (1 << SE); // enables sleep

    wdt_disable(); //disables the watchdog timer

    //disable other useless peripherals

    /* -------TURN OFF ADC---------*/
    ADCSRB &= ~(1 << ADEN); //disables the ADC
    PRR |= 1 << PRADC; //shuts down adc

    /*--------TURN OF USI??? idk what that is-----------*/
    PRR |= 1 << PRUSI; //shuts down USI 

    /*--------TURN OFF POWER REDUCTION TIMER 0 AND 1 ---------*/

    PRR |= (1 << PRTIM0) | (1 << PRTIM0); //shuts down timers 


    //perhaps disable port pins???

    //disable BOD
    MCUCR |= (1 << BODSE) | (1 << BODS);
    MCUCR &= ~(1 << BODSE);
    sleep_cpu();
}

ISR(PCINT0_vect) {
    if(periods_left == 0){
        beep();
        // pick next time to beep
        periods_left = 60*getRandomInteger(&seed)*AVERAGE_TIME_BETWEEN_BEEPS_M/(255*TIME_INTERVAL);
    }
    else{
        periods_left--;
    }
    dischargeCapacitor();
    enterSleep();
}


int main(){
    _delay_ms(2000); // to debounce power supply
    seed = 6969;

    //flash the led to indicate the circuit has started working
    DDRB |= (1 << BEEP_PIN_1) | (1 << BEEP_PIN_2);
    PORTB ^= (1 << BEEP_PIN_1) | (1 << BEEP_PIN_2);
    _delay_ms(4000);
    PORTB ^= (1 << BEEP_PIN_1) | (1 << BEEP_PIN_2);

    periods_left = (unsigned int)(INITIAL_QUIET_PERIOD_DAYS*24*3600/TIME_INTERVAL) + 1;
    setPCINT();    
    enterSleep();
    while(1){
    }
}

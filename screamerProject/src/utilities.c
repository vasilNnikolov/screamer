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
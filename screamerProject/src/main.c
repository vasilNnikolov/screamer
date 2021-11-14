#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#define LED_PIN 0 //pb0
#define INTERRUPT_PIN 2// pb2, interrupt pin

void setPCINT(){
    //setup PCINT on INTERRUPT_PIN
    DDRB &= ~(1 << INTERRUPT_PIN); // sets interrupt_pin as input
    PORTB &= ~(1 << INTERRUPT_PIN); //removes pullup resistor from the interrupt pin
    GIMSK |= (1 << PCIE);
    PCMSK |= (1 << INTERRUPT_PIN);
    sei(); //enables interrupts globally
}

void dischargeCapacitor(){
    cli(); // disables interrupts globally, so when the cap is discharged there is no interrupt
    
    GIMSK &= ~(1 << PCIE);
    PCMSK &= ~(1 << INTERRUPT_PIN);//totally removes pcint settings, otherwise another interrupt fires after discharge
    
    DDRB |= 1 << INTERRUPT_PIN; //turn interrupt pin to output
    PORTB &= ~(1 << INTERRUPT_PIN); //turn interrupt pin off, to discharge the capacitor
    _delay_ms(1000);

    setPCINT();
}

void enterSleep(){  
    MCUCR |= (1 << SM1); // sets powerdown mode
    MCUCR |= (1 << SE); // enables sleep
    sleep_cpu();
}

ISR(PCINT0_vect) {
    for(unsigned char j=0; j < 20; j++){
        PORTB ^= (1 << LED_PIN);
        _delay_ms(300);
    }
    dischargeCapacitor();
    enterSleep();
}


/*
void wakeUp(){

}
*/

int main(){
    _delay_ms(2000); // to debounce power supply
    DDRB |= 1 << LED_PIN;
    PORTB ^= (1 << LED_PIN);
    _delay_ms(500);
    PORTB ^= (1 << LED_PIN);

    setPCINT();    
    enterSleep();
    while(1){
    }
}

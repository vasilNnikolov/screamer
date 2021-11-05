#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#define LED_PIN 0 //pb0
#define INTERRUPT_PIN 2// pb2, interrupt pin

void setupInterrupt(){
    GIMSK |= (1 << INT0);
    MCUCR |= (1 << ISC01) | (1 << ISC00); //enable interrupt on rising edge
    sei();
}

void dischargeCapacitor(){
    DDRB |= 1 << INTERRUPT_PIN; //turn interrupt pin to output
    //an interrupt shouldn't be generated since it is configured for rising edge only
    PORTB &= ~(1 << INTERRUPT_PIN); //turn interrupt pin off, to discharge the capacitor
    _delay_ms(1000);
    DDRB &= ~(1 << INTERRUPT_PIN);
    PORTB &= ~(1 << INTERRUPT_PIN); //removes pullup resistor from the interrupt pin
}


ISR(INT0_vect) {
    for(unsigned char j=0; j < 6; j++){
        PORTB ^= (1 << LED_PIN);
        _delay_ms(100);
    }
    dischargeCapacitor();
}

int main(){
    _delay_ms(2000); // to debounce power supply
    DDRB |= 1 << LED_PIN;
    PORTB ^= (1 << LED_PIN);
    _delay_ms(500);
    PORTB ^= (1 << LED_PIN);

    setupInterrupt();    
    while(1){
    }
}

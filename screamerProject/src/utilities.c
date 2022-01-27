#include "utilities.h"
#include "projectConstants.h"
int seed = 69;

unsigned int getRandomInteger(int* seed){
    unsigned int a = 1687;
    unsigned int m = 257;
    *seed = (a * (*seed)) % m;
    return *seed;
}
void setupInterrupt(){
    // sei();
    GIMSK |= (1 << PCIE);
    PCMSK |= (1 << INTERRUPT_PIN);
}

void goToSleep(){
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    // disable ADC
    ADCSRA &= ~(1 << ADEN); //disable adc
    PRR |= (1 << PRADC); // stops power to adc

    // disable watchdog timer
    wdt_disable();

    // disable unused port pins
    for(short i = 0; i < sizeof(unusedPins)/sizeof(unusedPins[0]); i++){
        DDRB &= ~(1 << unusedPins[i]); // sets it as input
        PORTB |= (1 << unusedPins[i]); // set pullup resistor to define voltage level, to reduce power consumption
    }

    // disable BOD and go to sleep
    sleep_enable();
    sleep_bod_disable();
    sei();
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
    //short n_beeps = 1;
    short n_beeps = getRandomInteger(&seed) % 5 + 3;
    while(n_beeps > 0){
        PORTB ^= (1 << BEEP_PIN_1) | (1 << BEEP_PIN_2);
        _delay_ms(BEEP_TIME_ON);
        PORTB ^= ((1 << BEEP_PIN_1) | (1 << BEEP_PIN_2));
        _delay_ms(BEEP_TIME_OFF);
        n_beeps--;
    }
}

ISR(PCINT0_vect){

}
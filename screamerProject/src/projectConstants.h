#ifndef PROJECT_CONSTANTS_H
#define PROJECT_CONSTANTS_H

// physical pin settings
#define BEEP_PIN_1 0 //pb0
#define BEEP_PIN_2 4 //pb4
#define NPN_TRANSISTOR_BASE_PIN 1// pb1
#define INTERRUPT_PIN 2// pb2, interrupt pin

// timing settings
#define TIME_INTERVAL 15 // the time interval of the external clock in seconds 
#define AVERAGE_TIME_BETWEEN_BEEPS_M 2 //average time between the beeps in minutes 
#define INITIAL_QUIET_PERIOD_DAYS 0
#define BEEP_TIME_ON 50 //time of one beep in ms
#define BEEP_TIME_OFF 500 //time between beeps in ms

#endif
#ifndef PROJECT_CONSTANTS_H
#define PROJECT_CONSTANTS_H

// physical pin settings
#define BEEP_PIN_1 0 //pb0
#define BEEP_PIN_2 4 //pb4
#define NPN_TRANSISTOR_BASE_PIN 1// pb1
#define INTERRUPT_PIN 2// pb2, interrupt pin
#define CAP_DISCHARGE_TIME_MS 500 //how much time does the capacitor discharge, in ms

// timing settings
#define TIME_INTERVAL_S 22 // the time interval of the external clock in seconds 
#define MAX_TIME_BETWEEN_BEEPS_M 2 // max time between the beeps in minutes, average is half that
#define INITIAL_QUIET_PERIOD_H 0
#define BEEP_TIME_ON 50 //time of one beep in ms
#define BEEP_TIME_OFF 200 //time between beeps in ms

#endif
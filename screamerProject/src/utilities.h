#ifndef UTILITIES_H
#define UTILITIES_H

<<<<<<< HEAD
extern volatile unsigned int seed, periods_left;
unsigned int getRandomInteger(unsigned int* seed);
=======
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>

void setupInterrupt();

void goToSleep();

void dischargeCapacitor();
>>>>>>> startingOver

void beep();
#endif
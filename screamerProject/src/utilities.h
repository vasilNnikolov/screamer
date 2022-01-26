#ifndef UTILITIES_H
#define UTILITIES_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>

extern int seed;
unsigned int getRandomInteger(int* seed);

void setupInterrupt();

void goToSleep();

void dischargeCapacitor();

void beep();
#endif
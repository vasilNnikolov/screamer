#ifndef UTILITIES_H
#define UTILITIES_H


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>

extern volatile unsigned int seed, periods_left;
unsigned int getRandomInteger(unsigned int* seed);

void beep();
#endif
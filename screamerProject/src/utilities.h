#ifndef UTILITIES_H
#define UTILITIES_H

volatile unsigned int seed, periods_left;

unsigned int getRandomInteger(unsigned int* seed);

void beep();
#endif
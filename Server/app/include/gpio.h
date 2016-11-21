#ifndef _GPIO_H
#define _GPIO_H

int pinMode(int pin, int mode);
int digitalWrite(int pin, int value);
int digitalRead(int pin);
int blink(int pin, double freq, double duration);
void delay(double dly);
int unexportPin(int pin);

#endif 
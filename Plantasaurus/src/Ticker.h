/*
Writen by Orlando Diaz
*/
#ifndef TICKER_H
#define TICKER_H

#include "mbed.h"
#include "Conf.h"

extern Ticker To1; 
extern volatile bool SampleFlag; 
extern DigitalOut led; 
 
void TickerISRHandler(void);

void TickerInit(void);

#endif
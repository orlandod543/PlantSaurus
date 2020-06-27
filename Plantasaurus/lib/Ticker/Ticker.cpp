#include <Ticker.h>

Ticker To1; 
volatile bool SampleFlag = false; 
DigitalOut led(LED1); 


void TickerISRHandler(void){
    SampleFlag = true;
    led = !led; 
    }

void TickerInit(void){
    To1.attach(&TickerISRHandler,SAMPLINGTIME);
    }
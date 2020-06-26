/*
Writen by Orlando Diaz
*/
#ifndef MOISTURESENSOR_H
#define MOISTURESENSOR_H

#include "mbed.h"

class MoistureSensor{
private:
    AnalogIn ain;    
    PinName Pin;
    uint16_t DryCal,WetCal;
    
public:
    MoistureSensor(PinName _Pin, uint16_t _DryCal, uint16_t _WetCal);
    /*
    Returns the analog value normalized between 0 and 65535
    */            
    uint16_t ReadRaw(void);
    /*
    Returns the analog value normalized beteen 0.0 - 1.0
    */    
    float ReadFloat(void);
    /*
    Returns Value of soil moisture in percentage.
    */ 
    float getMoisture(void);
    /*
    Returns the Pin used
    */     
    PinName getpin(void){return Pin;}
};

#endif
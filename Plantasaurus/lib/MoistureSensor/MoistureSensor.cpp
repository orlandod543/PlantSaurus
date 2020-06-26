/*
Writen by Orlando Diaz
*/
#include <MoistureSensor.h>

MoistureSensor::MoistureSensor(PinName _Pin, uint16_t _DryCal = 7864, uint16_t _WetCal =43908):ain(_Pin){
    Pin = _Pin;
    DryCal = _DryCal;
    WetCal = _WetCal;
    }
    
uint16_t MoistureSensor::ReadRaw(void){
    return ain.read_u16();
    }
    
float MoistureSensor::ReadFloat(void){
    return ain.read();
    }
    
float MoistureSensor::getMoisture(void){
    
    return 1.0f-MoistureSensor::ReadFloat();
    }
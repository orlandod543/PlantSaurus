#include "mbed.h"

#include <Conf.h>
#include <MoistureSensor.h>
#include <DS1820.h>

/*
Program that reads moisture data, temperature, timestamp it and in a future expansion send it through WIFI
*/
/*Initializing peripherals and sensors*/
Serial pc(USBTX, USBRX);

/* Ticker related functions*/
/*The ticker is controller by SAMPLINGTIME which is defined in seconds*/
Ticker To1; 
char data[50];
volatile bool SampleFlag= false; 
DigitalOut led(LED1); 

void TickerISRHandler(void){
    SampleFlag = true;
    led = !led; 
    }

void TickerInit(void){
    To1.attach(&TickerISRHandler,SAMPLINGTIME);
    }
/* END OF Ticker related functions*/     

    
//Initiializing objects
MoistureSensor Sensor(MOISTUREPIN, DRYCAL, WETCAL);
DS1820  probe(TEMPERATUREPIN); 

float  value,temperature;    

int main() {
    
    /*Configure serial port and ticker*/
    pc.baud(SERIALBAUD);
    TickerInit();

    /*check DS1820 available*/
        probe.begin();
    if(!probe.isPresent()){
        pc.printf("No DS1820 found\r\n");
    }
    else{
        pc.printf("A DS1820 found\r\n");
        }

    /*Start endless loop*/
    while(1){
        if(SampleFlag== true){  
            SampleFlag = false;
            probe.startConversion();
            //check is there are received data from ESP
            
            /*Timestamp values and create message*/
                    
            value = Sensor.getMoisture();    
            temperature = probe.read();
            pc.printf("%1.2f %1.2f\r\n", value,temperature);
             
        }
    }
        
}



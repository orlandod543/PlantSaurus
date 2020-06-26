#include "mbed.h"

#include <Conf.h>
#include <MoistureSensor.h>
#include <DS1820.h>
#include <ds1307.h>
#include <string>
/*
Program that reads moisture data, temperature, timestamp it and in a future expansion send it through WIFI
*/
/*Initializing peripherals and sensors*/
Serial pc(USBTX, USBRX);

/* Start of Ticker related functions*/  
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
/* End of Ticker related functions*/     

    
//Initiializing objects
MoistureSensor Sensor(MOISTUREPIN, DRYCAL, WETCAL); //moisture sensor object
DS1820  probe(TEMPERATUREPIN); //Temperature sensor using onewire
DS1307 rtc(SDAPIN,SLCPIN); // create a clock object

/*Start of RTC related functions */
/*
Fills a char array with the current date in the current format:
yyyy-mm-dd-hh:mm:ss
Returns 0 if rtc is found
Returns 1 if fails
*/
char datestr[20];
int getdatestr(char *datestr){
    int sec,mins,hour,day,date,month,year; //integer array to hold the date: sec,min,hour,day,date,month,year);
    if(!rtc.gettime(&sec,&mins,&hour,&day,&date,&month,&year)){
        sprintf(datestr,"%d-%d-%d-%02d:%02d:%02d",year,month,date,hour,mins,sec);
        return 0;
    }
    else{
        return 1;
    }
}    
/*END of RTC related functions */

float  value,temperature;    

int main() {
    
    /*Configure serial port and ticker*/
    pc.baud(SERIALBAUD);
    TickerInit();
/*configure the date from RTC*/
#ifdef SETRTC
    int sec,mins,hour,day,date,month,year; //integer array to hold the date: sec,min,hour,day,date,month,year);
    if(SETRTC == true){
        pc.printf("Setting date to \r\n");
        sec  = 20;
        mins = 48;
        hour = 22;
        day = 1;
        date = 26;
        month = 05;
        year = 19;
        pc.printf("%d-",sec);
        pc.printf("%d-",mins);
        pc.printf("%d-",hour);
        pc.printf("%d-",day);  
        pc.printf("%d-",date);
        pc.printf("%d-",month); 
        pc.printf("%d\r\n",year); 
     if(!rtc.settime(sec,mins,hour,day,date,month,year)){
        pc.printf("Date changed successfully\r\n");
        pc.printf(getdatestr());        
        }
        else{
            pc.printf("Unable to initialize RTC\r\n");
        } 
    }
#endif  

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
            getdatestr(datestr);
            pc.printf("%s %1.2f %1.2f\r\n", datestr, value, temperature);
             
        }
    }
        
}



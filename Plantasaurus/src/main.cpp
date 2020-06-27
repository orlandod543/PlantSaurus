/*
Program that reads moisture data, temperature, timestamp it and in a future expansion send it through WIFI
*/

#include "mbed.h"
#include <Conf.h>
#include <MoistureSensor.h>
#include <DS1820.h>
#include <RTClock.h>
#include <Ticker.h>
#include "ESP8266Interface.h"
#include "UDPSocket.h"

/*Initializing peripherals and sensors*/
Serial pc(USBTX, USBRX);


/* End of Ticker related functions*/  

float  value,temperature;    
char datestr[20];
const int payloadsize = 64;
char payload[payloadsize];

int main()
{
    /*Configure serial port and ticker*/
    pc.baud(SERIALBAUD);
    TickerInit();

    /*configure the date from RTC*/
    #ifdef SETRTC
        clk.SetRTClock;
    #endif  

    //Initiializing objects
    MoistureSensor Sensor(MOISTUREPIN, DRYCAL, WETCAL); //moisture sensor object
    DS1820  probe(TEMPERATUREPIN); //Temperature sensor using onewire
    RTClock clk(SDAPIN,SLCPIN); // create a clock object
    ESP8266Interface esp(ESP8266_TX, ESP8266_RX); //create a wifi connection
    WiFiInterface *wifi = &esp;

    /*Attemps to connect to the network*/
    pc.printf("Attempting to connect to %s:\r\n", SSIDName);
    nsapi_error_t status = wifi->connect(SSIDName, SSIDPassword, SSIDSecurity);
    if(status!=NSAPI_ERROR_OK){
        pc.printf("Connection failed with status %i. Stop", status);
        return 0;
        }
    //if everything is ok then print the ip address. 
    pc.printf("Connection successful\r\n");
    const char *ip = wifi->get_ip_address();
    const char *mac = wifi->get_mac_address();
    pc.printf("IP address is: %s\r\n", ip ? ip : "No IP");
    pc.printf("MAC address is: %s\r\n", mac ? mac : "No MAC");   

    /*create a upd socket*/
    UDPSocket socket;
    socket.open(wifi);

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
        /*Waits until SampleFlag from ticker is set to acquire date*/
        if(SampleFlag== true){  
            SampleFlag = false;
            
            //check is there are received data from ESP
            
           /*Get sensors data*/
            probe.startConversion();
            value = Sensor.getMoisture();    
            temperature = probe.read();

            /*Get date in string*/
            if(!clk.ReadDate()){
              clk.GetDatestr(datestr);
            }
            else{
              pc.printf("RTC clock disconnected\r\n");
            }

            //assemble data into a payload
            sprintf(payload,"%s %1.2f %1.2f\r\n", datestr, value, temperature);

            /*Send data to terminal*/
            pc.printf(payload);

            /*send data to the UDP port*/
            socket.sendto(TARDISIP, TARDISPORT,&payload, payloadsize);

             
        }
    }
        
}



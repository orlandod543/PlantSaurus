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
#include "Buzzer.h"

/*Initializing peripherals and sensors*/
Serial pc(USBTX, USBRX);


/* End of Ticker related functions*/  

float  moisture,temperature;    
char datestr[20];
const int payloadsize = 32;
char payload[payloadsize];
bool WIFIConnected = false; //boolean that indicates if the connection to the wifi network is succesful.  
int main()
{
    /*Configure serial port and ticker*/
    pc.baud(SERIALBAUD);
    TickerInit();

    //Initializing objects
    MoistureSensor Sensor(MOISTUREPIN, DRYCAL, WETCAL); //moisture sensor object
    DS1820  probe(TEMPERATUREPIN); //Temperature sensor using onewire
    RTClock clk(SDAPIN,SLCPIN); // create a clock object
    Buzzer alarm(BuzzerPIN);
    ESP8266Interface esp(ESP8266_TX, ESP8266_RX); //create a wifi connection
    WiFiInterface *wifi = &esp; //create a wifi interface with the ESP8266
    UDPSocket socket;   

    
    alarm.beep(392,0.3); //send a tone to show its alive

    /*Establishing network connection*/
    pc.printf("Attempting to connect to %s:\r\n", SSIDName);
    nsapi_error_t status = wifi->connect(SSIDName, SSIDPassword, SSIDSecurity);

    if(status!=NSAPI_ERROR_OK){
        pc.printf("Connection failed with status %i. Disable WIFI", status);
        WIFIConnected = false;
        //two same tones indicates no conection. 
        alarm.beep(392,0.3); //send a tone to indicate connection
        wait(0.5);
        alarm.beep(392,0.3); //send a tone to indicate connectio
    }else{
        //if everything is ok then print the ip address and create udp socket.
        pc.printf("Connection successful\r\n");
        const char *ip = wifi->get_ip_address();
        const char *mac = wifi->get_mac_address();
        pc.printf("IP address is: %s\r\n", ip ? ip : "No IP");
        pc.printf("MAC address is: %s\r\n", mac ? mac : "No MAC");
        WIFIConnected = true;
        socket.open(wifi); 
        // two different tones indicate connection
        alarm.beep(392,0.3); //send a tone to indicate connection
        wait(0.5);
        alarm.beep(783.99,0.3); //send a tone to indicate connectio
           
    }

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
            
           /*Get sensors data*/
            probe.startConversion();
            moisture = Sensor.getMoisture();    
            temperature = probe.read();

            /*Get date in string*/
            if(!clk.ReadDate()){
              clk.GetDatestr(datestr);
            }
            else{
              pc.printf("RTC clock disconnected\r\n");
            }

            //assemble data into a payload
            sprintf(payload,"%s %1.2f %1.2f\n", datestr, moisture, temperature);

            /*Send data to terminal*/
            pc.printf(payload);

            /*send data to the UDP port*/
            if(WIFIConnected)
                socket.sendto(TARDISIP, TARDISPORT,&payload, payloadsize);

            /*Alarm section*/
            //if soil is below certain moisture value, send a tone to ask for water
            if(moisture<DRYALARM){
                alarm.beep(880,0.3); //send a tone to indicate connection
                wait(0.5);
                alarm.beep(880,0.3); //send a tone to indicate connectio
                wait(0.5);
                alarm.beep(880,0.3); //send a tone to indicate connectio             
            }
             
        }
    }
        
}



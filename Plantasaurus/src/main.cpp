<<<<<<< HEAD
/*
Program that reads moisture data, temperature, timestamp it and in a future expansion send it through WIFI
*/

#include "mbed.h"
#include <Conf.h>
#include <MoistureSensor.h>
#include <DS1820.h>
#include <RTClock.h>
#include <string>
#include "ESP8266Interface.h"
#include "UDPSocket.h"

/*Initializing peripherals and sensors*/
=======
/* NetworkSocketAPI Example Program
 * Copyright (c) 2015 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 //https://os.mbed.com/teams/NetworkSocketAPI/wiki/Getting-Started
#include "mbed.h"
#include "ESP8266Interface.h"
#include "TCPSocket.h"
#include "Conf.h"
ESP8266Interface wifi(ESP8266_TX, ESP8266_RX);
>>>>>>> wifi
Serial pc(USBTX, USBRX);

int main()
{
    pc.baud(SERIALBAUD);
    pc.printf("NetworkSocketAPI Example\r\n");
 
    wifi.connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA2);
    const char *ip = wifi.get_ip_address();
    const char *mac = wifi.get_mac_address();
    pc.printf("IP address is: %s\r\n", ip ? ip : "No IP");
    pc.printf("MAC address is: %s\r\n", mac ? mac : "No MAC");
    
<<<<<<< HEAD
//Initiializing objects
MoistureSensor Sensor(MOISTUREPIN, DRYCAL, WETCAL); //moisture sensor object
DS1820  probe(TEMPERATUREPIN); //Temperature sensor using onewire
RTClock clk(SDAPIN,SLCPIN); // create a clock object
ESP8266Interface esp(ESP8266_TX, ESP8266_RX); //create a wifi connection
WiFiInterface *wifi = &esp;

float  value,temperature;    
char datestr[20];
int main() {

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

    /*Configure serial port and ticker*/
    pc.baud(SERIALBAUD);
    TickerInit();
/*configure the date from RTC*/
#ifdef SETRTC
    clk.SetRTClock;
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

            /*Send data to terminal*/
            pc.printf("%s %1.2f %1.2f\r\n", datestr, value, temperature);
             
        }
    }
        
}


=======
    SocketAddress addr(&wifi, "192.168.178.19");
    pc.printf("mbed.org resolved to: %s\r\n", addr.get_ip_address());
  
    TCPSocket socket(&wifi);
    socket.connect("arm.com", 80);
    char buffer[64];
    sprintf(buffer,"GET / HTTP/1.0\r\n\r\n");
    socket.send(buffer, 64);
    char buf[100];
    socket.recv(buf, 100);
    //int count = socket.recv(buffer, sizeof buffer);
    pc.printf(buf);
   
    //socket.close();
    //wifi.disconnect();
 
    pc.printf("Done\r\n");
}
>>>>>>> wifi

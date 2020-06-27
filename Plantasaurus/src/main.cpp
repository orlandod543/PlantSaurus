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
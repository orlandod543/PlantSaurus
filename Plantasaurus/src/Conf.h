#ifndef CONF_H
#define CONF_H

#define SSIDName "Koraalstraat28A"
#define SSIDPassword "Nami_488"
#define SSIDSecurity NSAPI_SECURITY_WPA2

#define TARDISIP "192.168.178.19"
#define TARDISPORT 1111

#define MOISTUREPIN A0
#define DRYCAL 7864
#define WETCAL 43908

#define TEMPERATUREPIN A1

#define SAMPLINGTIME 1

#define SERIALBAUD 115200
/*RTC configuration  */
#define SDAPIN D2
#define SLCPIN D8

/*ESP8266 configuration*/
#define ESP8266_TX D14
#define ESP8266_RX D15
#define ESP8266_BAUD 115200

//#define SETRTC true

#define MBED_CONF_APP_WIFI_SSID SSIDName
#define MBED_CONF_APP_WIFI_PASSWORD SSIDPasswd
#define MBED_CONF_ESP8266_TX D14
#define MBED_CONF_ESP8266_RX D15
#endif
#ifndef CONF_H
#define CONF_H

#define SSIDName "Ziggo5320622"
#define SSIDPasswd "yf5MmsfbB9fv"

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

#define MBED_CONF_APP_WIFI_SSID "Koraalstraat28A"
#define MBED_CONF_APP_WIFI_PASSWORD "Nami_488"
#define MBED_CONF_ESP8266_TX D14
#define MBED_CONF_ESP8266_RX D15
#endif
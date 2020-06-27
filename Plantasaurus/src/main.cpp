/*******************************************************************************
 * Copyright (c) 2014, 2015 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Ian Craggs - initial API and implementation and/or initial documentation
 *    Ian Craggs - make sure QoS2 processing works, and add device headers
 *******************************************************************************/
 
 /**
  This is a sample program to illustrate the use of the MQTT Client library
  on the mbed platform.  The Client class requires two classes which mediate
  access to system interfaces for networking and timing.  As long as these two
  classes provide the required public programming interfaces, it does not matter
  what facilities they use underneath. In this program, they use the mbed
  system libraries.
 
 */
 
 // change this to 1 to output messages to LCD instead of serial
 
#define MQTTCLIENT_QOS2 1
 
#include "MQTTNetwork.h"
#include "MQTTmbed.h"
#include "MQTTClient.h"
#include "Conf.h"
#include "ESP8266Interface.h"
#include "TCPSocket.h"

int arrivedcount = 0;
 
Serial pc(USBTX, USBRX);
 
void messageArrived(MQTT::MessageData& md)
{
    MQTT::Message &message = md.message;
    pc.printf("Message arrived: qos %d, retained %d, dup %d, packetid %d\r\n", message.qos, message.retained, message.dup, message.id);
    pc.printf("Payload: %.*s\r\n", message.payloadlen, (char*)message.payload);
    ++arrivedcount;
}
 
ESP8266Interface esp(ESP8266_TX, ESP8266_RX); //create a wifi connection
WiFiInterface *wifi = &esp; //create a wifi interface with the ESP8266


    

int main(int argc, char* argv[])
{
    pc.baud(SERIALBAUD);
    /*Connect to wifi before handing the interface to MQTT*/ 
    pc.printf("Attempting to connect to %s:\r\n", SSIDName);
    nsapi_error_t status = wifi->connect(SSIDName, SSIDPassword, SSIDSecurity);
    pc.printf("%i", status);
    if (status){
        pc.printf("Connection failed. Stop");
        return -1;
    }else{
        pc.printf("connection succesful. IP %s\n", wifi -> get_ip_address());
    }

    float version = 0.6;
    char* topic = "mbed-sample";
 
    pc.printf("HelloMQTT: version is %.2f\r\n", version);
 
    // I am not sure if this part is needed. 
    NetworkInterface* network = wifi;
    if (!network) {
        return -1;
    }
 
    MQTTNetwork mqttNetwork(network);
 
    MQTT::Client<MQTTNetwork, Countdown> client(mqttNetwork);
 
    //creates a TCP connection with the server. TCPSocket is wrapped on mqttNetwork
    const char* hostname = "broker.hivemq.com";
    int port = 1883;
    pc.printf("Connecting to %s:%d\r\n", hostname, port);
    int rc = mqttNetwork.connect(hostname, port);
    if (rc != 0)
        pc.printf("rc from TCP connect is %d\r\n", rc);
    else{
        pc.printf("Connection to %s:%d successful\r\n",hostname,port);
    }

    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = 3;
    data.clientID.cstring = "mbed-sample";
    data.username.cstring = "testuser";
    data.password.cstring = "testpassword";
    if ((rc = client.connect(data)) != 0)
        pc.printf("rc from MQTT connect is %d\r\n", rc);
    else{
        pc.printf("Connected to MQTT broker\r\n");
    }
 
    if ((rc = client.subscribe(topic, MQTT::QOS2, messageArrived)) != 0)
        pc.printf("rc from MQTT subscribe is %d\r\n", rc);
    else{
        pc.printf("Subscribed to topic %s\r\n", topic);
    }
    MQTT::Message message;
 
    // QoS 0
    char buf[100];
    sprintf(buf, "Hello World!  QoS 0 message from app version %f\r\n", version);
    message.qos = MQTT::QOS0;
    message.retained = false;
    message.dup = false;
    message.payload = (void*)buf;
    message.payloadlen = strlen(buf)+1;
    rc = client.publish(topic, message);
    pc.printf("%i", arrivedcount);
    while (arrivedcount < 1)
        client.yield(10);

    // QoS 1
    sprintf(buf, "Hello World!  QoS 1 message from app version %f\r\n", version);
    message.qos = MQTT::QOS1;
    message.payloadlen = strlen(buf)+1;
    rc = client.publish(topic, message);
    while (arrivedcount < 2)
        client.yield(100);
 
    // QoS 2
    sprintf(buf, "Hello World!  QoS 2 message from app version %f\r\n", version);
    message.qos = MQTT::QOS2;
    message.payloadlen = strlen(buf)+1;
    rc = client.publish(topic, message);
    while (arrivedcount < 3)
        client.yield(100);
 
    if ((rc = client.unsubscribe(topic)) != 0)
        pc.printf("rc from unsubscribe was %d\r\n", rc);
 
    if ((rc = client.disconnect()) != 0)
        pc.printf("rc from disconnect was %d\r\n", rc);
 
    mqttNetwork.disconnect();
 
    pc.printf("Version %.2f: finish %d msgs\r\n", version, arrivedcount);
 
    return 0;
}
 
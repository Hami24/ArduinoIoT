#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <ESP8266WiFi.h>

char ssid[] = ""; // SSID of WiFi AP
char pass[] = ""; // Password of WiFi AP 

WiFiClient client;

//MQTT configuration
//Add your custom settings
Adafruit_MQTT_Client mqtt(&client, "MQTTBROKER","PORT","userName","password");
Adafruit_MQTT_Publish connectionNotification = Adafruit_MQTT_Publish(&mqtt,"Test/1",0,1);
Adafruit_MQTT_Publish statusNotification = Adafruit_MQTT_Publish(&mqtt,"Test/2",0,1);
Adafruit_MQTT_Subscribe control = Adafruit_MQTT_Subscribe(&mqtt,"Test/3");

void MQTT_connect();

void setup()
{
  //Serial communication with Arduino Uno
  Serial.begin(9600);
  delay(10);

  connectWifi();
  statusWifi();

  // Notify the MQTT broker when ESP8266 loses connection
  mqtt.will("Test/1","OFF",0,1);

  //Subscribe to MQTT topic(receive messages from MQTT broker)
  mqtt.subscribe(&control);
  MQTT_connect();
  
}
void loop()
{
  // Receive messages from MQTT broker
  // Send messages over Serial connection
  // Notify client about changes
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(10000))) {
    if (subscription == &control) {
 
      if(strcmp((char*)control.lastread,"LEDON")==0)
        {
          Serial.print("1");
          statusNotification.publish("LEDON");
        }
        else if(strcmp((char*)control.lastread,"LEDOFF")==0)
        {
          Serial.print("0");
          statusNotification.publish("LEDOFF");
        }
        delay(100);
    }
  
  }
  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  MQTT_connect();

}
// Remove comments on Serial.print... for debugging
// (only when ESP8266 is not connected with Arduino Uno)
void connectWifi(){
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  //Serial.println();
}

void statusWifi()
{
  // SSID 
  //Serial.print("SSID: ");
  //Serial.print(WiFi.SSID());
 
  // Module IP
  IPAddress ip = WiFi.localIP();
  //Serial.print("IP");
  //Serial.print(ip);

  // Signal strength
  long rssi = WiFi.RSSI();
  //Serial.print("Signal strength (RSSI):");
  //Serial.print(rssi);
  //Serial.print(" dBm");
}

void MQTT_connect() {
  int8_t ret;

  // Check if client is connected to MQTT broker
  if (mqtt.connected()) {
    return;
  }
 
  //Serial.print("Connecting to MQTT broker...");
  delay(1000);

  while ((ret = mqtt.connect()) != 0) { 
       switch (ret) {
          case 1: /*Serial.print("Wrong protocol!");*/ break;
          case 2: /*Serial.print("Wrong ID"); */break;
          case 3: /*Serial.print("Server is not available!"); */break;
          case 4: /*Serial.print("Bad userName and password!"); */break;
          case 5: /*Serial.print("Not authenticated!");*/ break;
          case 6: /*Serial.print("Failed to subscribe!");*/ break;
          default: /*Serial.print("Connection failed, code: "); 
                   /*Serial.print(ret); */
                   break;
       }
       //Serial.print("Trying to connect to MQTT broker...");
       if(ret >= 0) {          
         mqtt.disconnect();     
       }
       delay(5000);  // wait 5 seconds and try again
  }
  //Notify the client when the module connects
  connectionNotification.publish("ON");
  //Serial.print("Connected to MQTT broker!");
}


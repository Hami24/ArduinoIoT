#Introduction
This is an example of how to control devices (in this case a simple LED) over the Internet using Arduino Uno,ESP8266 ESP-01 and MQTT protocol. ESP8266 ESP-01 is used as a WiFi module(I know that you can use it without the Arduino Uno to control devices, but I've seen a lot of people request an example where you can control devices over the Internet with an Arduino development board).

##Requirements
-Arduino Uno
-ESP8266 ESP-01
-Power supply for Arduino Uno
-3.3 V power supply for ESP8266 ESP-01
-PAHO MQTT JavaScript library
-LED
-220 ohm resistor

##How it works
ESP8266 ESP-01 connects to a WiFi AP, and handles the MQTT communication. After the user sends a message to the MQTT broker, the MQTT broker sends that same message to the ESP8266 ESP-01 WiFi module. After that, the ESP8266 ESP-01 WiFi module sends a character(which depends on the message it received from the MQTT broker) to the Arduino Uno over a serial connection. The Arduino Uno development board turns on/off the LED depending on the character it received. In this example, the user is notified if the WiFi module connects or loses connection to the MQTT broker, and when the LED changes its status.

##Demo
Centrifugal pump and RGB LED strip control based on this concept
[Demo](img/demo.gif)

##ToDoList
- Add fritzing schematic
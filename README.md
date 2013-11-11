# MQTT Arduino Template
A base sketch for building networked Arduino projects with MQTT

## Tested on:
* [Arduino Uno](http://arduino.cc/en/Main/ArduinoBoardUno)
* [Sparkfun WiFly Shield](https://www.sparkfun.com/products/9954)

## Requirements
* [Arduino 1.0.x IDE](http://arduino.cc/en/Main/Software)
* [Knolleary's Arduino Client for MQTT (aka PubSubClient)](http://knolleary.net/arduino-client-for-mqtt/)
* [dpslwk's WiFly Shield Library](https://github.com/dpslwk/WiFly)

## Known Issues
* To extend the Keep Alive time, you have to edit the MQTT KEEPALIVE Variable in PubSubClient.h in the PubSubClient Library Folder
* MQTT Payloads must not be longer than 128 bytes

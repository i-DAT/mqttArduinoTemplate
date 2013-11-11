#include "SPI.h"
#include "WiFly.h"
#include "PubSubClient.h"

//broker settings
byte server[] = { 0, 0, 0, 0 }; // replace with the IP address of your broker - swap . for ,

int port = 1883; //default port is 1883. To help get around network restrictions,you may need broker set as port 80

char subscribedChannel[] = "outTopic";
char deviceName[] = "uniqueClientName"; // set a unique name for each device connected to the broker

//used to decode the message payload
String payloadString;
void convertPayload(byte array[], byte len){
  payloadString = "";
  for (byte i = 0; i < len;){
    char c = array[i++];
    if (c < 0x20 || c > 0x7e){
     Serial.print('.');
     payloadString += '.';
    }
    else {
      payloadString += char(c);
    }
  }
  
}

//triggered when a message is recieved on a subscribed channel
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Message Recieved");
  
  // handle message
  
  //check the topic - use this is you want to sunbscribe to more than one channel
  if (String(topic) == String(subscribedChannel)){
    Serial.println(topic);
    
    //convert the payload to a string, then print it out
    convertPayload(payload, length);
    Serial.println(payloadString);
  }
  
}

WiFlyClient wifiClient;
PubSubClient client(server, port, callback, wifiClient);

void connectToBroker(){
  //connect to the broker
    if (client.connect(deviceName)) {
      Serial.println("Connecting");
      //send a test message
      client.publish("outTopic","hello world");
      //subscribe to a channel
      client.subscribe(subscribedChannel);
      Serial.println("Connected");
    } else{
      Serial.println("Connection Error");
    }
  
}

void setup() {
  
  Serial.begin(115200);
  Serial.println("setup");

  //connect to network
  WiFly.begin();
  if (!WiFly.join("ssid", "pass")) { //use if network has passphrase
  //if (!WiFly.join("ssid")) { // use id it doesn't
    Serial.println("Association failed.");
    while (1) {
      // Hang on failure.
    }
  }else{
    Serial.println("Joining");
    Serial.println(WiFly.ip());
  }
  
}

void loop() {
  //check and maintain the connection to the broker
  if(!client.connected()){
     Serial.println("Disconnected");
     connectToBroker();
  }else{
    client.loop();  
  }
  //Do Stuff!

}


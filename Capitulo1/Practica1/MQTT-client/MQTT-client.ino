/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <WiFi.h>
#include <PubSubClient.h>
//#include <Wire.h>

#define CHANNELS 1
// Replace the next variables with your SSID/Password combination
//const char* ssid = "SSID";
const char* ssid = "BBT";
//const char* password = "PASSWORD";
const char* password = "@@TheBigBangTheory@@";

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;

void setup() {
  Serial.begin(115200);
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  setup_wifi();
  client.setServer("192.168.49.111", 1883);
  client.setCallback(callback);
  
/*  for (uint8_t i=0; i<CHANNELS; i++)
  {
    pinMode(pines[i], OUTPUT);
    digitalWrite(pines[i], HIGH);
    client.publish(topics[i].c_str(), "off");
  }*/
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (String(topic) == "sensor/actuator") {
    Serial.print("String actuator");
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // Cliente00001 is an ID, it will be unique
    if (client.connect("Cliente00001", "test", "test001")) {
      Serial.println("connected");
      client.subscribe("sensor/actuator");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

/*void loop() {
}*/

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    
    // Temperature in Celsius
    int temperature = 20;   
    
    // Convert the value to a char array
    char tempString[11];
    dtostrf(temperature, 5, 2, tempString);
    Serial.print("Temperature: ");
    Serial.println(tempString);
    client.publish("sensor/temperature", tempString);
    Serial.println("send ");
  }
}

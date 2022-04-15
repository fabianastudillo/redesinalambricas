/*********
  @author: Fabian Astudillo <fabian.astudillos@ucuenca.edu.ec>
  @title: Tutorial to connect to wifi network
*********/

#include <WiFi.h>

WiFiClient espClient;

// Replace the next variables with your SSID/Password combination
const char* ssid = "SSID";
const char* password = "PASSWORD";

void setup() {
  Serial.begin(115200);

  setup_wifi();

  
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


void loop() {
  // put your main code here, to run repeatedly:

}

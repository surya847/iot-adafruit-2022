#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid     = "XXXXXXXXX"; // Your ssid
const char* password = "XXXXXXXXX"; // Your Password 

const char* mqtt_server = "m2m.eclipse.org";

WiFiClient espClient;
PubSubClient client(espClient);
 
void setup_wifi() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");}
  Serial.println("");
  Serial.println("WiFi connected");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
      if (client.connect("esp8266")) {
      Serial.println("connected");
      }else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);}}}
void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);}

void loop() {
 if (!client.connected()) {
    reconnect(   );}
  client.loop();
  client.publish( "BEC/IOT/2019", "hello from ...");
  delay(1000);
}

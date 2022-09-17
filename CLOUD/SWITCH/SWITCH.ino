#include <ESP8266WiFi.h>
#include <String.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define LED 5

/////////////////////////////////////////

#define WLAN_SSID       "XXXXXXXXXXXXXX"              //WIFI NAME
#define WLAN_PASS       "XXXXXXXXXXXXXX"              //WIFI PASSWORD

////////////////////////////////////////

#define AIO_SERVER      "io.adafruit.com"             //SERVER NAME
#define AIO_SERVERPORT  1883                          //MQTT PORT
    
/////////////////////////////////////////////

#define IO_USERNAME  "XXXXXXXXXXX"
#define IO_KEY       "XXXXXXXXXXX"

/////////////////////////////////////////


WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, IO_USERNAME, IO_KEY);

////////////////////////////////////
Adafruit_MQTT_Subscribe Switch = Adafruit_MQTT_Subscribe(&mqtt, IO_USERNAME "/feeds/switch");
void MQTT_connect();
void setup()
{

  Serial.begin(9600);
  delay(10);
  pinMode(LED, OUTPUT);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  mqtt.subscribe(&Switch);
}

void loop()
{
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    // Check if its the onoff button feed
    if (subscription == &Switch) {
      Serial.print(F("On-Off button: "));
      Serial.println((char *)Switch.lastread);

      if (strcmp((char *)Switch.lastread, "ON") == 0) {
        digitalWrite(LED, 1);
      }
      if (strcmp((char *)Switch.lastread, "OFF") == 0) {
        digitalWrite(LED, 0);
      }
}
  }

}



void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}

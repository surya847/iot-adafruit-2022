#include <ESP8266WiFi.h>

#include <String.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define R_LED  5
#define G_LED 4
#define B_LED  0

/////////////////////////////////////////

#define WLAN_SSID       "XXXXXXXXXX"
#define WLAN_PASS       "XXXXXXXXXX"

//////////////////////////////////////////

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   

/////////////////////////////////////////

#define IO_USERNAME  "XXXXXXXXXXXXXXXXXXX"
#define IO_KEY       "XXXXXXXXXXXXXXXXXXX"

/////////////////////////////////////////

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, IO_USERNAME, IO_KEY);
////////////////////////////////////

Adafruit_MQTT_Subscribe REDLED = Adafruit_MQTT_Subscribe(&mqtt, IO_USERNAME "/feeds/REDLED");
Adafruit_MQTT_Subscribe GREENLED = Adafruit_MQTT_Subscribe(&mqtt, IO_USERNAME "/feeds/GREENLED");
Adafruit_MQTT_Subscribe BLUELED = Adafruit_MQTT_Subscribe(&mqtt, IO_USERNAME "/feeds/BLUELED");


void MQTT_connect();
void setup()
{
  Serial.begin(9600);
  delay(10);
  pinMode(R_LED , OUTPUT);
  pinMode(G_LED , OUTPUT);
  pinMode(B_LED , OUTPUT);
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
  mqtt.subscribe(&REDLED);
  mqtt.subscribe(&GREENLED);
  mqtt.subscribe(&BLUELED);
}



void loop()
{
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(6000))) {
    // Check if its the onoff button feed
    if (subscription == &REDLED) {
      Serial.print(F("Fading Red LED: "));
      Serial.println((char *)REDLED.lastread);
      int intensity = atoi((char *)REDLED.lastread);
      Serial.println(intensity);
      analogWrite(R_LED,intensity);   
    }

    else if (subscription == &GREENLED) {
      Serial.print(F("Fading GREEn LED: "));
      Serial.println((char *)GREENLED.lastread);
      int intensity = atoi((char *)GREENLED.lastread);
      Serial.println(intensity);
      analogWrite(G_LED,intensity);
     }
    else  {
      Serial.print(F("Fading Blue LED: "));
      Serial.println((char *)BLUELED.lastread);
      int intensity = atoi((char *)BLUELED.lastread);
      Serial.println(intensity);
      analogWrite(B_LED,intensity);        
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


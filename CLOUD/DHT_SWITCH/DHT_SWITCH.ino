#include <ESP8266WiFi.h>
#include <String.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "DHT.h"

#define SWITCH 5
#define DHTPIN 4    // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11
////////////////////////////////////////

#define WLAN_SSID       "XXXXXXXXXXXX"      //mention SSID 
#define WLAN_PASS       "XXXXXXXXXXXX"      //mention Password

//////////////////////////////////////////

#define AIO_SERVER      "io.adafruit.com" // server name
#define AIO_SERVERPORT  1883     

////////////////////////////////////////////              

#define IO_USERNAME  "XXXXXXXXXXXX"
#define IO_KEY       "XXXXXXXXXXXXX"

/////////////////////////////////////////
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, IO_USERNAME, IO_KEY);
////////////////////////////////////
Adafruit_MQTT_Publish TEMP = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/TEMP");
Adafruit_MQTT_Publish HUM = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/HUM");
Adafruit_MQTT_Subscribe Switch = Adafruit_MQTT_Subscribe(&mqtt, IO_USERNAME "/feeds/switch");

void MQTT_connect();
DHT dht(DHTPIN, DHTTYPE);
//////////////////////////////////////////
void setup()
{

  Serial.begin(9600);
  dht.begin();
   pinMode(SWITCH, OUTPUT);
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
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
   mqtt.subscribe(&Switch);
}

void loop()
{
  MQTT_connect();
   // Read temperature as Celsius (the default)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  else
  {
  Serial.println("Sending DATA");
  Serial.println("Temperature:");
  Serial.println(t);
  Serial.println("Humidity:");
  Serial.println(h);
  //TEMP.publish(t);
  HUM.publish(h);
  }

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    // Check if its the onoff button feed
    if (subscription == &Switch) {
      Serial.print(F("On-Off button: "));
      Serial.println((char *)Switch.lastread);

      if (strcmp((char *)Switch.lastread, "ON") == 0) {
        digitalWrite(SWITCH, 1);
      }
      if (strcmp((char *)Switch.lastread, "OFF") == 0) {
        digitalWrite(SWITCH, 0);
      }
   }
  }
  
  delay(2000);

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

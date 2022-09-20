#include <ESP8266WiFi.h>
#include <String.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "DHTesp.h"

#define DHTPIN 5
DHTesp dht;
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
void MQTT_connect();
//////////////////////////////////////////
void setup()
{

  Serial.begin(9600);
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
   dht.setup(DHTPIN, DHTesp::DHT11); 
  
}

void loop()
{
  MQTT_connect();
   delay(dht.getMinimumSamplingPeriod());
   // Read temperature as Celsius (the default)
  float h = dht.getHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.getTemperature();
  Serial.println("Sending DATA");
  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print("Temperature: ");
  Serial.print( t);
  Serial.print("\t");
  Serial.print("Humidity: ");
  Serial.println(h);
  TEMP.publish(t);
  HUM.publish(h);
  
  delay(5000);

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

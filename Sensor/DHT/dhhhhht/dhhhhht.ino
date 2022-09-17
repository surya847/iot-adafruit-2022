#include <DHT.h>

#define DHTPIN 5                            //Pin D1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  Serial.println("Collecting temperature data.");
  float h = dht.readHumidity();                       // Reading humidity

  float t = dht.readTemperature();                    // Read temperature as Celsius

  if (isnan(h) || isnan(t))                           // Check if any reads failed and exit early (to try again).
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.println("Temperature :");
  Serial.println(t);

  Serial.println("Humidity :");
  Serial.println(h);

  delay(1000);
}

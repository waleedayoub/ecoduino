#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define MOISTURE_PIN A2 // soil Moisture sensor
#define DHT11_PIN 9     // DHT11

DHT dht(DHT11_PIN, DHT11); // Initialize DHT sensor

float airHumidity;    // environment humidity
float airTemperature; // environment temperature
int soilMoisture;     // soil moisture

void setup()
{
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  delay(2000); // Wait for 2 seconds between measurements

  airHumidity = dht.readHumidity();
  airTemperature = dht.readTemperature();
  soilMoisture = analogRead(MOISTURE_PIN);

  // Check if any reads failed and exit early (to try again).
  if (isnan(airHumidity) || isnan(airTemperature) || isnan(soilMoisture))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Air Humidity: ");
  Serial.print(airHumidity);
  Serial.print("%,\t");
  Serial.print("Air Temperature: ");
  Serial.print(airTemperature);
  Serial.print("°C,\t");
  Serial.print("Soil Humidity: ");
  Serial.println(soilMoisture);

  delay(1000);
}

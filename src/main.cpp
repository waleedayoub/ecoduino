#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <unity.h> // Include the Unity testing framework

#define MOISTURE_PIN A2 // soil Moisture sensor
#define DHT11_PIN 9     // DHT11

DHT dht(DHT11_PIN, DHT11); // Initialize DHT sensor

float airHumidity;    // environment humidity
float airTemperature; // environment temperature
int soilMoisture;     // soil moisture

// Define the pump control pins
#define PUMP_PIN1 5
#define PUMP_PIN2 6

// Define the soil moisture threshold below which the pump turns on
#define SOIL_MOISTURE_THRESHOLD 20

// Define the pump on and off times (in milliseconds)
#define PUMP_ON_TIME 10000
#define PUMP_OFF_TIME 60000

void setup()
{
  Serial.begin(9600);
  dht.begin();

  pinMode(PUMP_PIN1, OUTPUT);
  pinMode(PUMP_PIN2, OUTPUT);

  digitalWrite(PUMP_PIN1, LOW);
  digitalWrite(PUMP_PIN2, LOW);
}

void pump_on()
{
  digitalWrite(PUMP_PIN1, HIGH);
  digitalWrite(PUMP_PIN2, HIGH);

  // Print the variables while the pump is on
  Serial.print("Air Humidity: ");
  Serial.print(airHumidity);
  Serial.print("%,\t");
  Serial.print("Air Temperature: ");
  Serial.print(airTemperature);
  Serial.print("°C,\t");
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoisture);

  delay(PUMP_ON_TIME);
}

// Declare the test functions
void test_pump_on();
void test_pump_off();

int main(int argc, char **argv)
{
  UNITY_BEGIN();
  RUN_TEST(test_pump_on);
  RUN_TEST(test_pump_off);
  UNITY_END();

  return 0;
}

void pump_off()
{
  digitalWrite(PUMP_PIN1, LOW);
  digitalWrite(PUMP_PIN2, LOW);
  // Print the variables while the pump is off
  Serial.print("Air Humidity: ");
  Serial.print(airHumidity);
  Serial.print("%,\t");
  Serial.print("Air Temperature: ");
  Serial.print(airTemperature);
  Serial.print("°C,\t");
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoisture);
  delay(PUMP_OFF_TIME);
}

void loop()
{
  delay(2000); // Wait for 2 seconds between measurements

  airHumidity = dht.readHumidity();
  airTemperature = dht.readTemperature();
  soilMoisture = map(analogRead(MOISTURE_PIN), 0, 1023, 0, 100);

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
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoisture);

  // Check if the soil moisture is below the threshold
  if (soilMoisture < SOIL_MOISTURE_THRESHOLD)
  {
    // Turn on the pump
    pump_on();
  }
  else
  {
    // Turn off the pump
    pump_off();
  }

  delay(1000);
}
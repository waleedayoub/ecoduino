#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
// #include <unity.h> // Include the Unity testing framework

#define MOISTURE_PIN A2 // soil Moisture sensor
#define DHT11_PIN 9     // DHT11

// Define the pump control pins
#define PUMP_PIN1 5
#define PUMP_PIN2 6

float airHumidity;    // environment humidity
float airTemperature; // environment temperature
int soilMoisture;     // soil moisture

// Define the soil moisture threshold between 0-100 below which the pump turns on
#define SOIL_MOISTURE_THRESHOLD 70

// Define the pump on and off times (in milliseconds)
#define PUMP_ON_TIME 1000
#define PUMP_OFF_TIME 10000

DHT dht(DHT11_PIN, DHT11); // Initialize DHT sensor

void setup()
{
  Serial.begin(9600);
  dht.begin(); // Initialize the DHT sensor to read data

  // Initialize the pump control pins to send data
  pinMode(PUMP_PIN1, OUTPUT);
  pinMode(PUMP_PIN2, OUTPUT);

  digitalWrite(PUMP_PIN1, LOW);
  digitalWrite(PUMP_PIN2, LOW);
}

void printSensorData()
{
  Serial.print("Air Humidity: ");
  Serial.print(airHumidity);
  Serial.print("%, Air Temperature: ");
  Serial.print(airTemperature);
  Serial.print("°C, Soil Moisture: ");
  Serial.print(soilMoisture);
  Serial.println("%, ");
  Serial.print("Soil Moisture Threshold: ");
  Serial.print(SOIL_MOISTURE_THRESHOLD);
  Serial.print("%, Pump 1: ");
  Serial.print(digitalRead(PUMP_PIN1));
  Serial.print(", Pump 2: ");
  Serial.println(digitalRead(PUMP_PIN2));
}

void pump_on()
{
  digitalWrite(PUMP_PIN1, HIGH);
  digitalWrite(PUMP_PIN2, HIGH);

  // Print the variables while the pump is on
  printSensorData();

  delay(PUMP_ON_TIME);
}

void pump_off()
{
  digitalWrite(PUMP_PIN1, LOW);
  digitalWrite(PUMP_PIN2, LOW);
  // Print the variables while the pump is off
  printSensorData();

  delay(PUMP_OFF_TIME);
}

/*
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

*/

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

  printSensorData();

  // Check if the soil moisture is below the threshold
  while (soilMoisture < SOIL_MOISTURE_THRESHOLD)
  {
    // Turn on the pump for PUMP_ON_TIME seconds
    pump_on();

    // Wait for 2 seconds
    // delay(PUMP_DELAY_TIME);

    // Turn off the pump for PUMP_OFF_TIME seconds
    pump_off();

    // Update the soil moisture reading
    soilMoisture = map(analogRead(MOISTURE_PIN), 0, 1023, 0, 100);
    printSensorData();
  }

  delay(1000);
}

#include <dht.h>

dht DHT;

#define MOISTURE_PIN    A2  // set the soil moisture pin
#define DHT11_PIN       9   // set the humidity pin

int airHumidity;          //environment humidity
int airTemperature;       //environment temperature
int soilMoisture;         //soil moisture

int thresholdMoisture = 25;

void setup()
{
  // Instantiate all the DHT sensor information
  Serial.begin(115200);
  Serial.println("Reading Sensors: ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C), \tSoil Moisture ()");

  // Instantiate the pump settings
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

void loop()
{
  // Read data from the DHT pin
  Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  switch (chk) {
    case DHTLIB_OK:
      Serial.print("OK,\t");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("Checksum error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.print("Time out error,\t");
      break;
    case DHTLIB_ERROR_CONNECT:
      Serial.print("Connect error,\t");
      break;
    case DHTLIB_ERROR_ACK_L:
      Serial.print("Ack Low error,\t");
      break;
    case DHTLIB_ERROR_ACK_H:
      Serial.print("Ack High error,\t");
      break;
    default:
      Serial.print("Unknown error,\t");
      break;
  }

  // Assign all the sensor data to variables
  airHumidity = DHT.humidity;
  airTemperature = DHT.temperature;
  soilMoisture = map(analogRead(MOISTURE_PIN), 0, 1023, 0, 100);
  
  // Write all the sensor data to serial
  Serial.print("airHumidity: ");
  Serial.print(airHumidity, 1);
  Serial.print(" ,\t");
  Serial.print("airTemperature: ");
  Serial.print(airTemperature, 1);
  Serial.print(" ,\t");
  Serial.print("soilMoisture: ");
  Serial.print(soilMoisture, 1);
  Serial.print(" ,\t");
  Serial.println();
  
  delay(1000);

  // Cycle the pump on and off routine
  if (soilMoisture < thresholdMoisture) {
    pumpOn();
    delay(5000);
    pumpOff();
  } else {
    pumpOff();
  }
  
  Serial.print("Pump value is set to: ");
  Serial.print(" ,\t");
  Serial.print(digitalRead(5), 1);
  Serial.print(digitalRead(6), 1);
  Serial.println();
  delay(1000);
  
}

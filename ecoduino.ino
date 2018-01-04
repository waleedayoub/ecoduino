#define BLYNK_PRINT Serial1

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <BlynkSimpleStream.h>

// Auth token from the Blynk app
char auth[] = "4007f543dc2849aca91e94cd4b98c774";

#define MOISTURE_PIN    A2  // set the soil moisture pin
#define DHTPIN       9   // set the humidity pin

// Uncomment the type of sensor in use:
#define DHTTYPE           DHT11     // DHT 11 
//#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

DHT_Unified dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

float airHumidity;          //environment humidity
float airTemperature;       //environment temperature
int soilMoisture;         //soil moisture

int thresholdMoisture = 25;

void setup()
{
  // Blynk will work through Serial
  // Do not read or write this serial manually in the sketch
  Serial.begin(9600);
  Blynk.begin(Serial, auth);

  dht.begin();

  // Set up a function to be called every second
  timer.setInterval(1000L, sendSensor);

  // Debug console, write temperature and sensor information here
  Serial1.begin(9600);
}

void loop()
{
  Blynk.run();
  timer.run(); 
}

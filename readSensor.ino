
/*
 * #include <dht.h>

dht DHT;

#define MOISTURE_PIN  A2  //soil moisture sensor
#define DHT11_PIN     9   //DHT11 sensor

int airHumidity;          //environment humidity
int airTemperature;       //environment temperature
int soilMoisture;         //soil moisture

void setup() {
  Serial.begin(9600);
}

void loop() {
  int chk;
  chk = DHT.read(DHT11_PIN);    //read data from humidity sensor
  switch (chk){
    case DHTLIB_OK:
      Serial.print("OK,\t");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("CHECKSUM ERROR,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.print("TIMEOUT ERROR,\t");
      break;
    default:
      Serial.print("UNKNOWN ERROR,\t");
      break;
  }

  airHumidity = DHT.humidity;
  airTemperature = DHT.temperature;
  soilMoisture = analogRead(MOISTURE_PIN);

  Serial.print("airHumidity: ");
  Serial.print(airHumidity);
  Serial.print(" ,\t");
  Serial.print("airTemperature: ");
  Serial.print(airTemperature);
  Serial.print(" ,\t");
  Serial.print("soilMoisture: ");
  Serial.print(soilMoisture);
  Serial.print(" ,\t");
  }
}
*/

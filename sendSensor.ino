void sendSensor()
{
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  airTemperature = event.temperature;
  dht.humidity().getEvent(&event);
  airHumidity = event.relative_humidity;

  if (isnan(airHumidity) || isnan(airTemperature)) {
    Serial1.println("Failed to read from DHT sensor!");
    return;
  }

  // map the soil moisture pin
  soilMoisture = map(analogRead(MOISTURE_PIN), 0, 1023, 0, 100);
  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, airHumidity);
  Blynk.virtualWrite(V6, airTemperature);
  Blynk.virtualWrite(V4, soilMoisture);
}

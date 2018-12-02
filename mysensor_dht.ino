// SPDX-License-Identifier: GPL-2.0
/*
* Mysensor board for monitoring Temperature and Humidity with DHT22
*
* Copyright (C) 2018 Kent Gustavsson <kent@minoris.se>
*
*/ 

#define MY_RADIO_NRF24
 
#include <SPI.h>
#include <MySensors.h>  
#include <DHT.h>

// Set this to the pin you connected the DHT's data pin to
#define DHT_DATA_PIN 15

// Set this offset if the sensor has a permanent small offset to the real temperatures.
// Dependent in metric settings
#define SENSOR_TEMP_OFFSET 0

// Atleast 2000, else the DHT library will repeat last value
static const uint64_t UPDATE_INTERVAL = 60000;

#define CHILD_ID_HUM 0
#define CHILD_ID_TEMP 1

bool metric = true;

MyMessage msgHum(CHILD_ID_HUM, V_HUM);
MyMessage msgTemp(CHILD_ID_TEMP, V_TEMP);
DHT dht(DHT_DATA_PIN, DHT22);


void presentation()  
{ 
  // Send the sketch version information to the gateway
  sendSketchInfo("TemperatureAndHumidity", "1.2");
  
  // Register all sensors to gw (they will be created as child devices)
  present(CHILD_ID_HUM, S_HUM);
  present(CHILD_ID_TEMP, S_TEMP);
  
  metric = getControllerConfig().isMetric;
}


void setup()
{
  dht.begin();
}


void loop()      
{  
  // Get temperature from DHT library
  float temperature = dht.readTemperature(!metric, false);
  if (isnan(temperature)) {
    // Failed reading temperature from DHT
  } else {
    // apply the offset
    temperature += SENSOR_TEMP_OFFSET;

    send(msgTemp.set(temperature, 1));
  } 

  // Get humidity from DHT library
  float humidity = dht.readHumidity();
  if (isnan(humidity)) {
    // Failed reading humidity from DHT
  } else {
    send(msgHum.set(humidity, 1));
  } 

  // Sleep for a while to save energy
  sleep(UPDATE_INTERVAL); 
}

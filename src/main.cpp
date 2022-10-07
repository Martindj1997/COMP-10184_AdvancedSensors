// ******************************************************************
// I, Martin De Jesus Gonzalez Santos; 000790179 certify that this is my orginal work.
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program
// COMP-10184
// Mohawk College

// library for Arduino framework
#include <Arduino.h>
// 1-Wire sensor communication libary
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>

// Pin that the  DS18B20 is connected to
const int oneWireBus = D3;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);

void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);

  // Start the DS18B20 sensor
  DS18B20.begin();

  DeviceAddress address;

  Serial.println("*** Temperature Application ***");

  if (DS18B20.getAddress(address, 0))
  {
    Serial.println("*** Temperature sensor Connected ***");
    Serial.print("Temperature sensor DS18B20 with address fetched of: ");
  }else{
    Serial.println("*** No DS18B20 Temperature sensors are installed ***");
    return;
  }

  for (int i = 0; i < 8; i++)
  {
    Serial.printf("%02X ", address[i]);
  }

  Serial.println("");

}

void loop()
{
  float fTemp;

  // ask DS18B20 for the current temperature
  DS18B20.requestTemperatures();

  // fetch the temperature.  We only have 1 sensor, so the index is 0.
  fTemp = DS18B20.getTempCByIndex(0);

  String feeling = "";

  if(fTemp < 10){
    feeling = "Cold!";
  }
  else if (fTemp == 10 || fTemp < 15)
  {
    feeling = "Cool";
  }
  else if (fTemp == 15 || fTemp < 25)
  {
    feeling = "Perfect";
  }
  else if (fTemp == 25 || fTemp < 30)
  {
    feeling = "Warm";
  }
  else if (fTemp == 30 || fTemp < 35)
  {
    feeling = "Hot";
  }else{
    feeling = "Too Hot!";
  }
  // print the temp to the USB serial monitor
  Serial.println("Current temperature is: " + String(fTemp) + " C or " + feeling);

  // wait 5s (5000ms) before doing this again
  delay(5000);
}
/*
######################| Summary |######################
Sketch for following Hardware:
Microcontrollerboard:   Arduino MKRWAN1300
Environmental Sensor:   Bosch BME680 (with breakoutboard)

Measure temperature, humidity, pressure, gas-resistance and voltage every 60s for 15 Minutes
Calculate average of all 15 values for each measurement and send average to your favorite LoRa-Network.

Testet with https://chirpstack.io installed on RasperryPi 4b with Ubuntu Server 20.X but should also work with https://thethingsnetwork.org

Dependent on including licensing:
- LoRa Payload Library by https://github.com/Technickfreak/LoRa-payload-BKU
- BME680 Sensor Library by https://github.com/adafruit/Adafruit_BME680

######################| License |######################
MIT License

Copyright (c) 2021 Dario Ludwig

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

######################| Code |######################
*/

#include <Wire.h>
#include <SPI.h>
#include <construct_TYPE.h>
#include <LoRa_payload_BKU.h>
#include "secrets.h"
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

// #define BME_SCK 13
// #define BME_MISO 12
// #define BME_MOSI 11
// #define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme; // I2C
//Adafruit_BME680 bme(BME_CS); // hardware SPI
//Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);

_lora_band frequency = EU868;

bool bmestatus;
double temperature, humidity, pressure, gas, vdd;
double messwerte[15][5];
int analogPin = A1;
int messungsNr = 0;
int i, j, connectiontry=1;                                   //Zählvariablen
int intervalle[] = {60000, 900000, 900000}; //60000=1s Messwerte aufnehmen; 900000=15min Mittelwert bilden; 900000=15min LoRa-Payload erstellen und senden
unsigned long lastTime[3];                  //Hilfsvariable zu intervalle; Speichert letzte Aktivierung
Bku::PayloadLoraBku iamalive[1] = {{Bku::TYPE_sign_of_life, 1}};

void setup()
{  
  //Serial.begin(115200);
  bme.begin();

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

  do
  {
    Serial.print("Try to connect to LoRa-Network... Attenmpt no.: ");
    Serial.println(connectiontry);
    connectiontry++;
    delay(1000);
  } while (!Bku::SetupLoraBku(appEui, appKey, frequency));
  
  Bku::SendPayloadLoraBku(iamalive);
}

void loop()
{
  messwertMethode();
  mittelwertMethode();

  if (messungsNr == 15 && zeitAbfrage(2))
  {
    Serial.println("Start packing payload... ");
    Bku::PayloadLoraBku testpayload2[] = {
        {Bku::TYPE_TEMP32, temperature},
        {Bku::TYPE_HUMIDITY32, humidity},
        {Bku::TYPE_PRESSURE, pressure},
        {Bku::TYPE_GAS_KOHMS, gas},
        {Bku::TYPE_VDD, vdd},
    };
    Serial.println("Send Payload... ");
    Bku::SendPayloadLoraBku(testpayload2);
  }
}

void messwertMethode() // Methode nimmt Sekündlich Messwete auf
{
  bme.performReading();
  analogReadResolution(12);
  if (zeitAbfrage(0)) //0 weil 60000ms; für andere Zeiten siehe globales Array
  {
    messungsNr++;
    Serial.println("Messerte aufnehmen... ");
    if (messungsNr <= 15)
    {
      Serial.print("Messungs Nr. Einstieg: ");
      Serial.print(messungsNr);
      Serial.println();

      for (i = 0; i < 5; i++)
      {
        switch (i)
        {
        case 0:
          messwerte[messungsNr-1][i] = bme.temperature;
          Serial.print("Temperatur Messwert: ");
          Serial.print(bme.temperature);
          Serial.print(" | Arraywert: ");
          Serial.println(messwerte[messungsNr - 1][i]);
          break;

        case 1:
          messwerte[messungsNr-1][i] = bme.humidity;
          Serial.print("Feuchtigkeit Messwert: ");
          Serial.print(bme.humidity);
          Serial.print(" | Arraywert: ");
          Serial.println(messwerte[messungsNr - 1][i]);
          break;

        case 2:
          messwerte[messungsNr-1][i] = bme.pressure / 100.0;
          Serial.print("Pressure Messwert: ");
          Serial.print(bme.pressure / 100.0);
          Serial.print(" | Arraywert: ");
          Serial.println(messwerte[messungsNr - 1][i]);
          break;

        case 3:
          messwerte[messungsNr-1][i] = bme.gas_resistance / 1000.0;
          Serial.print("Gas Messwert: ");
          Serial.print(bme.gas_resistance / 1000.0);
          Serial.print(" | Arraywert: ");
          Serial.println(messwerte[messungsNr - 1][i]);
          break;

        case 4:
          messwerte[messungsNr-1][i] = (3300.0 / 4095) * analogRead(analogPin);
          Serial.print("VDD Messwert: ");
          Serial.print((3300.0 / 4095) * analogRead(analogPin));
          Serial.print(" | Arraywert: ");
          Serial.println(messwerte[messungsNr - 1][i]);
          break;
        }
      }
    }
    else
    {
      messungsNr = 0;
    }
    Serial.print("Messungs Nr. Ausstieg: ");
    Serial.println(messungsNr);
    Serial.println();
  }
}

void mittelwertMethode() //Methode um Mittelwert zu bilden
{
  i = 0;
  if (messungsNr == 15 && zeitAbfrage(1))
  {
    Serial.println("Mittelwerte bilden... ");
    Serial.print("Messungs Nr: ");
    Serial.println(messungsNr);
    temperature = 0;
    humidity = 0;
    pressure = 0;
    gas = 0;
    vdd = 0;
    for (i; i < messungsNr; i++)
    {
      for (j = 0; j < 5; j++)
      {
        switch (j)
        {
        case 0:
          temperature = temperature + messwerte[i][j];
          Serial.print(temperature);
          Serial.print("C | ");
          break;

        case 1:
          humidity = humidity + messwerte[i][j];
          Serial.print(humidity);
          Serial.print("% | ");
          break;

        case 2:
          pressure = pressure + messwerte[i][j];
          Serial.print(pressure);
          Serial.print("psi | ");
          break;

        case 3:
          gas = gas + messwerte[i][j];
          Serial.print(gas);
          Serial.print("Ohm | ");
          break;

        case 4:
          vdd = vdd + messwerte[i][j];
          Serial.print(vdd);
          Serial.println("mV");
          break;
        }
      }
    }
    temperature = temperature / messungsNr;
    humidity = humidity / messungsNr;
    pressure = pressure / messungsNr;
    gas = gas / messungsNr;
    vdd = vdd / messungsNr;
    //serialoutput();
  }
  return;
}

bool zeitAbfrage(int interval) //Methode-universalis um ein Zeitinterval abzufragen. Benötigt ein globales Array mit zu erwartenden intervallen, gibt true zurück wenn Zeit abgelaufen ist.
{
  if (lastTime[interval] + intervalle[interval] <= millis())
  {
    lastTime[interval] = millis();
    return true;
  }
  else
  {
    return false;
  }
}

void serialoutput()
{
  Serial.println("Mittelwerte:");
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Gas = ");
  Serial.print(gas);
  Serial.println(" KOhms");

  Serial.print("Versorgungsspannung = ");
  Serial.print(vdd);
  Serial.println(" mV");

  Serial.println();
}

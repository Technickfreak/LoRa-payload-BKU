#pragma once

#ifdef _LoRa_payload_BKU_h
#warning es wurden mehrere Bords Geladen.
//#endif
//#ifndef _LoRa_payload_BKU_h
#else
#define _LoRa_payload_BKU_h



#include "arduino.h"

#include "construct_TYPE.h"















#include <ESP32_LoRaWAN.h>
#include "Arduino.h"
#include "sensor/HDC1080.h"
#include "esp32-hal-adc.h"

/*license for Heltec ESP32 LoRaWan, quary your ChipID relevant license: http://resource.heltec.cn/search */
uint32_t  license[4] = {0xD5397DF0, 0x8573F814, 0x7A38C73D, 0x48E68607};

/* OTAA para*/
uint8_t DevEui[] = { 0x22, 0x32, 0x33, 0x00, 0x00, 0x88, 0x88, 0x02 };
uint8_t AppEui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t AppKey[] = { 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x66, 0x01 };

/* ABP para*/
uint8_t NwkSKey[] = { 0x15, 0xb1, 0xd0, 0xef, 0xa4, 0x63, 0xdf, 0xbe, 0x3d, 0x11, 0x18, 0x1e, 0x1e, 0xc7, 0xda,0x85 };
uint8_t AppSKey[] = { 0xd7, 0x2c, 0x78, 0x75, 0x8c, 0xdc, 0xca, 0xbf, 0x55, 0xee, 0x4a, 0x77, 0x8d, 0x16, 0xef,0x67 };
uint32_t DevAddr =  ( uint32_t )0x007e6ae1;

/*LoraWan channelsmask, default channels 0-7*/ 
uint16_t userChannelsMask[6]={ 0x00FF,0x0000,0x0000,0x0000,0x0000,0x0000 };

/*LoraWan Class, Class A and Class C are supported*/
DeviceClass_t  loraWanClass = CLASS_A;

/*the application data transmission duty cycle.  value in [ms].*/
uint32_t appTxDutyCycle = 15000;

/*OTAA or ABP*/
bool overTheAirActivation = true;

/*ADR enable*/
bool loraWanAdr = true;

/* Indicates if the node is sending confirmed or unconfirmed messages */
bool isTxConfirmed = true;

/* Application port */
uint8_t appPort = 2;

/*!
* Number of trials to transmit the frame, if the LoRaMAC layer did not
* receive an acknowledgment. The MAC performs a datarate adaptation,
* according to the LoRaWAN Specification V1.0.2, chapter 18.4, according
* to the following table:
*
* Transmission nb | Data Rate
* ----------------|-----------
* 1 (first)       | DR
* 2               | DR
* 3               | max(DR-1,0)
* 4               | max(DR-1,0)
* 5               | max(DR-2,0)
* 6               | max(DR-2,0)
* 7               | max(DR-3,0)
* 8               | max(DR-3,0)
*
* Note, that if NbTrials is set to 1 or 2, the MAC will not decrease
* the datarate, in case the LoRaMAC layer did not receive an acknowledgment
*/
uint8_t confirmedNbTrials = 8;

/*LoraWan debug level, select in arduino IDE tools.
* None : print basic info.
* Freq : print Tx and Rx freq, DR info.
* Freq && DIO : print Tx and Rx freq, DR, DIO0 interrupt and DIO1 interrupt info.
* Freq && DIO && PW: print Tx and Rx freq, DR, DIO0 interrupt, DIO1 interrupt and MCU deepsleep info.
*/
uint8_t debugLevel = LoRaWAN_DEBUG_LEVEL;

/*LoraWan region, select in arduino IDE tools*/
LoRaMacRegion_t loraWanRegion = ACTIVE_REGION;

HDC1080 hdc1080;
static void prepareTxFrame( uint8_t port )
{
    /*appData size is LORAWAN_APP_DATA_MAX_SIZE which is defined in "commissioning.h".
  *appDataSize max value is LORAWAN_APP_DATA_MAX_SIZE.
  *if enabled AT, don't modify LORAWAN_APP_DATA_MAX_SIZE, it may cause system hanging or failure.
  *if disabled AT, LORAWAN_APP_DATA_MAX_SIZE can be modified, the max value is reference to lorawan region and SF.
  *for example, if use REGION_CN470, 
  *the max value for different DR can be found in MaxPayloadOfDatarateCN470 refer to DataratesCN470 and BandwidthsCN470 in "RegionCN470.h".
  */
    pinMode(Vext,OUTPUT);
    digitalWrite(Vext,LOW);
    uint16_t batteryVoltage = analogRead(37)*3.046;
    hdc1080.begin(0x40);
    float temperature = (float)(hdc1080.readTemperature());
    float humidity = (float)(hdc1080.readHumidity());
    hdc1080.end();
    digitalWrite(Vext,HIGH);
    unsigned char *puc;

    puc = (unsigned char *)(&temperature);
    appDataSize = 10;
    appData[0] = puc[0];
    appData[1] = puc[1];
    appData[2] = puc[2];
    appData[3] = puc[3];

    puc = (unsigned char *)(&humidity);
    appData[4] = puc[0];
    appData[5] = puc[1];
    appData[6] = puc[2];
    appData[7] = puc[3];

    appData[8] = (uint8_t)(batteryVoltage>>8);
    appData[9] = (uint8_t)batteryVoltage;

    Serial.print("T=");
    Serial.print(temperature);
    Serial.print("C, RH=");
    Serial.print(humidity);
    Serial.print("%,");
    Serial.print("BatteryVoltage:");
    Serial.println(batteryVoltage);
}

// Add your initialization code here
void setup()
{
  Serial.begin(115200);
  while (!Serial);
  SPI.begin(SCK,MISO,MOSI,SS);
  Mcu.init(SS,RST_LoRa,DIO0,DIO1,license);

  adcAttachPin(37);
  analogSetClockDiv(255); // 1338mS
  
  deviceState = DEVICE_STATE_INIT;
}

// The loop function is called in an endless loop
void loop()
{
  switch( deviceState )
  {
    case DEVICE_STATE_INIT:
    {
      LoRaWAN.init(loraWanClass,loraWanRegion);
      break;
    }
    case DEVICE_STATE_JOIN:
    {
      LoRaWAN.join();
      break;
    }
    case DEVICE_STATE_SEND:
    {
      prepareTxFrame( appPort );
      LoRaWAN.send(loraWanClass);
      deviceState = DEVICE_STATE_CYCLE;
      break;
    }
    case DEVICE_STATE_CYCLE:
    {
      // Schedule next packet transmission
      txDutyCycleTime = appTxDutyCycle + randr( -APP_TX_DUTYCYCLE_RND, APP_TX_DUTYCYCLE_RND );
      LoRaWAN.cycle(txDutyCycleTime);
      deviceState = DEVICE_STATE_SLEEP;
      break;
    }
    case DEVICE_STATE_SLEEP:
    {
      LoRaWAN.sleep(loraWanClass,debugLevel);
      break;
    }
    default:
    {
      deviceState = DEVICE_STATE_INIT;
      break;
    }
  }
}


















namespace Bku
{

    namespace debugStatusLoraBku
    {

        String appEui;
        String appKey;
        _lora_band frequency = EU868;

        bool modemBeginState = false; //debug for LoRa-Modem-Start
        bool OTAAState = false;       //debug state for OTAA (Over-The-Air-Authentication)
        bool loopCheck = false;       //debug state for Loop

        void connectToTTN() //Method to connect to TTN
        {
            //start LoRa modem in specified band
            modemBeginState = modem.begin(frequency);
            //debugStatusLoraBku::modemBeginState = modem.begin(testEU868);

            //request Over-The-Air-Authentication from TTN-Network
            OTAAState = modem.joinOTAA(appEui, appKey);
        }

        bool connectionOK() //Method to connect to TTN
        {
            return (modemBeginState && OTAAState);
        }

    } // namespace debugStatusLoraBku

    bool SetupLoraBku(String appEui_, String appKey_, _lora_band frequency_ = EU868)
    {
        debugStatusLoraBku::appEui = appEui_;
        debugStatusLoraBku::appKey = appKey_;
        debugStatusLoraBku::frequency = frequency_;

        if (!modem.begin(debugStatusLoraBku::frequency))
        {
            Serial.println("Failed to start module");
            return false;
        };

        int connected = modem.joinOTAA(debugStatusLoraBku::appEui, debugStatusLoraBku::appKey);
        if (!connected)
        {
            Serial.println("Something went wrong; are you indoor? Move near a window and retry");
            return false;
        }
        return true;
    }

    bool SendDataLoraBku(uint8_t *MSG, size_t size = 1)
    {
        bool msgSend = false;
        if (!debugStatusLoraBku::connectionOK()) //Check if LoRa-Modem start & OTAA was correct last time, if not, try again
        {
            debugStatusLoraBku::connectToTTN();
        }

        if (debugStatusLoraBku::connectionOK()) //if connection to TTN was successful at least once, send message
        {
            //payload testpayload;
            modem.beginPacket();
            modem.write(MSG, size);
            //Serial.println(testpayload.getPayload()[0]+" "+testpayload.getPayload()[1]+" "+testpayload.getPayload()[2]);
            //Serial.println(MSG);
            //modem.write(testpayload.getPayload(), testpayload.getLength());
            msgSend = modem.endPacket(true); //endPacket finishes all messages and sends it to TTN
        }
        return (msgSend); //folse: "Error sending message :("
    }

    bool SendPayloadLoraBku(PayloadLoraBku *mypayload)
    {
        //printData(payloadconverter(mypayload), payloadlength(mypayload));
        return SendDataLoraBku(PayloadconverterLoraBku(mypayload), PayloadlengthLoraBku(mypayload));
    }

    void PrintMSGLoraBku(uint8_t *MSG, size_t size)
    {
        for (size_t i = 0; i < size; i++)
        {
            if (MSG[i] < 0x10)
            {
                Serial.print("0");
            }
            Serial.print(MSG[i], HEX);
            Serial.print(" ");
        }
        Serial.println("");
    }

    void PrintMSGLoraBku(uint8_t *MSG)
    {
        if (MSG[0] > 0)
        {
            Serial.print("MSG size: ");
            Serial.println(MSG[0]);
            for (int i = 1; i <= MSG[0]; i++)
            {
                if (MSG[i] < 0x10)
                {
                    Serial.print("0");
                }
                Serial.print(MSG[i], HEX);
                Serial.print(" ");
            }
            Serial.println("");
        }
    }

    uint8_t *ReceiveDataLoraBku()
    {
        static uint8_t MSG[64];
        if (!modem.available())
        {
            //Serial.println("No downlink message received at this time.");
            MSG[0] = 0;
            return MSG;
        }
        else
        {
            int i = 1;
            while (modem.available())
            {
                MSG[i++] = (uint8_t)modem.read();
            }
            MSG[0] = i - 1; //Array Position 0 ist für die lange des Array
            return MSG;
        }
    }

} // namespace PayloadLoraBku

#endif
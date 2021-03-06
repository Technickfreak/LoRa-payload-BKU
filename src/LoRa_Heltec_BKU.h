#pragma once

#ifdef _LoRa_payload_BKU_h
#warning es wurden mehrere Bords Geladen.
//#endif
//#ifndef _LoRa_payload_BKU_h
#else
#define _LoRa_payload_BKU_h



#include "arduino.h"

#include "construct_TYPE.h"


#include <TTN_esp32.h>
#include "TTN_CayenneLPP.h"
#include "heltec.h"





//TTN Keys
const char* devEui = "CHANGE_ME"; // Change to TTN Device EUI
const char* appEui = "CHANGE_ME"; // Change to TTN Application EUI
const char* appKey = "CHANGE_ME"; // Chaneg to TTN Application Key



#define USER_PIN true


namespace Bku
{

    namespace debugStatusLoraBku
    {        
        String devEui;
        String appEui;
        String appKey;
        _lora_band frequency = EU868;

        void connectToTTN() //Method to connect to TTN
        {
            //start LoRa modem in specified band
            ttn.begin();

            ttn.onMessage(message);

            //request Over-The-Air-Authentication from TTN-Network
            ttn.join(devEui, appEui, appKey);
        }

        bool connectionOK() //Method to connect to TTN
        {
            //return (modemBeginState && OTAAState);
            return (ttn.isjoin() && ttn.isrunning());
        }

        void message(const uint8_t* payload, size_t size, int rssi)
        {
            Serial.println("-- MESSAGE");
            Serial.print("Received " + String(size) + " bytes RSSI=" + String(rssi) + "db");
            for (int i = 0; i < size; i++)
            {
                Serial.print(" " + String(payload[i]));
                // Serial.write(payload[i]);
            }
            Serial.println();
        }

    } // namespace debugStatusLoraBku

    ///
    /// @param devEui_  == "AUTO" or your devEui
    ///
    bool SetupLoraBku(String devEui_, String appEui_, String appKey_, _lora_band frequency_ = EU868)        //devEui füllen
    {
        if (devEui_ == "AUTO"){
            debugStatusLoraBku::devEui = ttn.getdevEui(true);
        }else{
            debugStatusLoraBku::devEui = devEui_;
        }
        
        debugStatusLoraBku::appEui = appEui_;
        debugStatusLoraBku::appKey = appKey_;
        debugStatusLoraBku::frequency = frequency_;

        TTN_esp32 ttn;
        TTN_CayenneLPP lpp;


        ttn.begin();
        // if (!ttn.begin())
        // {
        //     Serial.println("Failed to start module");
        //     return false;
        // };
        ttn.onMessage(message); // declare callback function when is downlink from server
        //ttn.personalize(devAddr, nwkSKey, appSKey);
        ttn.join(debugStatusLoraBku::devEui, debugStatusLoraBku::appEui, debugStatusLoraBku::appKey);

        while (!ttn.isJoined())
        {
            Serial.print(".");
            delay(500);
        }
        Serial.println("\njoined !");
        ttn.showStatus();

        // int connected = modem.joinOTAA(debugStatusLoraBku::appEui, debugStatusLoraBku::appKey);
        // if (!connected)
        // {
        //     Serial.println("Something went wrong; are you indoor? Move near a window and retry");
        //     return false;
        // }

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
            ttn.sendBytes(MSG, size);
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
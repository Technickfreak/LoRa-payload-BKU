#pragma once

#ifndef _LoRa-payload-BKU_h
#define _LoRa-payload-BKU_h

	#include "arduino.h"
    
	#include <MKRWAN.h>
	LoRaModem modem;


    #include "Encoder_TYPE.h"


    namespace debugStatusMKRWAN {

            String appEui;
            String appKey;
            _lora_band frequency = EU868;

        bool modemBeginState = false;					//debug for LoRa-Modem-Start
        bool OTAAState = false;							//debug state for OTAA (Over-The-Air-Authentication)
        bool loopCheck = false;							//debug state for Loop

        void connectToTTN()		//Method to connect to TTN
        {
            //start LoRa modem in specified band
            modemBeginState = modem.begin(frequency);
            //debugStatusMKRWAN::modemBeginState = modem.begin(testEU868);

            //request Over-The-Air-Authentication from TTN-Network
            OTAAState = modem.joinOTAA(appEui, appKey);
        }

        bool connectionOK()		//Method to connect to TTN
        {
            return (modemBeginState && OTAAState);
        }

    }


    bool setupLorawan(String appEui_, String appKey_, _lora_band frequency_ = EU868){
        debugStatusMKRWAN::appEui = appEui_;
        debugStatusMKRWAN::appKey = appKey_;
        debugStatusMKRWAN::frequency = frequency_;

        if (!modem.begin(debugStatusMKRWAN::frequency)) {
            Serial.println("Failed to start module");
            return false;
        };

        int connected = modem.joinOTAA(debugStatusMKRWAN::appEui, debugStatusMKRWAN::appKey);
        if (!connected) {
            Serial.println("Something went wrong; are you indoor? Move near a window and retry");
            return false;
        }
        return true;
    }




    //bool sendData(uint8_t MSG)		//Method to check LoRa state and send data to TTN
    bool sendData(uint8_t *MSG, size_t size = 1)
    {
        bool msgSend = false;
        if (!debugStatusMKRWAN::connectionOK())	//Check if LoRa-Modem start & OTAA was correct last time, if not, try again
        {
            debugStatusMKRWAN::connectToTTN();
        }

        if (debugStatusMKRWAN::connectionOK())	    //if connection to TTN was successful at least once, send message
        {
            //payload testpayload;
            modem.beginPacket();
            modem.write(MSG, size);
            //Serial.println(testpayload.getPayload()[0]+" "+testpayload.getPayload()[1]+" "+testpayload.getPayload()[2]);
            //Serial.println(MSG);
            //modem.write(testpayload.getPayload(), testpayload.getLength());
            msgSend = modem.endPacket(true);					//endPacket finishes all messages and sends it to TTN
        }
        return (msgSend); //folse: "Error sending message :("
    }
    
    bool sendPayload(payload *mypayload)
    {
        //printData(payloadconverter(mypayload), payloadlength(mypayload));
        return sendData(payloadconverter(mypayload), payloadlength(mypayload));
        
    }

    void printMSG(uint8_t *MSG, size_t size)
    {	
        for (size_t i = 0; i < size; i++)
        {
            if (MSG[i]<0x10) {Serial.print("0");}
            Serial.print(MSG[i],HEX);
            Serial.print(" ");
        }
        Serial.println("");
    }

    void printMSG(uint8_t *MSG)
    {
        if (MSG[0] > 0)
        {
            Serial.print("MSG size: ");
            Serial.println(MSG[0]);
            for (int i = 1; i <= MSG[0]; i++)
            {
                if (MSG[i]<0x10) {Serial.print("0");}
                Serial.print(MSG[i],HEX);
                Serial.print(" ");
            }
            Serial.println("");
        }
    }





    uint8_t *receiveData()
    {
        static uint8_t MSG[64];
        if (!modem.available()) {
            //Serial.println("No downlink message received at this time.");
            MSG[0] = 0;
            return MSG;
        }else{
            int i = 1;
            while (modem.available()) {
                MSG[i++] = (uint8_t)modem.read();
            }
            MSG[0] = i-1;         //Array Position 0 ist für die lange des Array
            return MSG;
        }
    }

    

    void testreceiveData()
    {
        if (!modem.available()) {
            //Serial.println("No downlink message received at this time.");
            return ;
        }

        uint8_t MSG[64];
        int i = 0;
        while (modem.available()) {
            MSG[i++] = (uint8_t)modem.read();
        }
        
        for (int k = 0; k < i; k++)
        {
            if (MSG[k]<0x10) {Serial.print("0");}
            Serial.print(MSG[k],HEX);
            Serial.print(" ");
        }
        Serial.println("");
    }

#endif
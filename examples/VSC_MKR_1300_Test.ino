
//#include "LoRa-payload-BKU.h"
#include <LoRa-payload-BKU.h>
//#include "\..\src\LoRa-payload-BKU.h"
//#include "D:\Schule\VS-Cdode\VSC MKR 1300\LoRa_mkr_wan_Lib\LoRa_mkr_wan_Lib.h"

//use your secrets.h file or enter appEui & appKey below
//  #include secrets.h

    String appEui = "70B3D57ED0029F3D";
    String appKey = "F0CD3364EEBD105757610701EF578F15";
//set your frequenze plan values are: (EU868,AS923,AU915,KR920,IN865,US915,US915_HYBRID)
    _lora_band frequency = EU868;

void setup()
{
    Serial.begin(115200);
    setupLorawan(appEui, appKey, frequency);
    
    Serial.print("Your device EUI is: ");
    Serial.println(modem.deviceEUI());
}

void loop()
{
    //fill your payload          Zeilenweises befüllen 
    payload testpayload[2];
    testpayload[0].TYPE = TYPE_TEMP;
    testpayload[0].wert = (-15.5);
    testpayload[1].TYPE = TYPE_RH;
    testpayload[1].wert = (27);
    
    /*                           Blockbefüllung
    payload testpayload2[] = {
                            payload(TYPE_RH, 66),
                            payload(TYPE_TEMP, 20.6),
                            };
    */
    /*                          Blockbefüllung 
    payload testpayload3[] = {
                            {TYPE_RH, 66},
                            {TYPE_TEMP, 20.6},
                            };
    */


    sendPayload(testpayload);
    delay(1000);    
    uint8_t *MSG = receiveData();
    if (MSG[0] = 0){Serial.println("No downlink message received at this time.");} 
    printMSG(MSG);

    delay(22000);

}

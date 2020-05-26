#include <LoRa_payload_BKU.h>
using namespace Bku;
//use your secrets.h file or enter appEui & appKey below
#include <c:\secrets\secrets.h>
String appEui = xxxxxxxxxxxxxxxx;
String appKey = xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;

//set your frequenze plan values are: (EU868,AS923,AU915,KR920,IN865,US915,US915_HYBRID)
_lora_band frequency = EU868;

void setup()
{
    Serial.begin(115200);
    SetupLoraBku(appEui, appKey, frequency);
    
    Serial.print("Your device EUI is: ");
    Serial.println(modem.deviceEUI());
}

void loop()
{
    //fill your payload
    Bku::PayloadLoraBku testpayload[2];
    testpayload[0].TYPE = TYPE_TEMP;
    testpayload[0].wert = (-15.5);
    testpayload[1].TYPE = TYPE_RH;
    testpayload[1].wert = (27);
    
    /*
    PayloadLoraBku testpayload2[] = {
                            PayloadLoraBku(TYPE_RH, 66),
                            PayloadLoraBku(TYPE_TEMP, 20.6),
                            };
    */
    /*
    PayloadLoraBku testpayload3[] = {
                            {TYPE_RH, 66},
                            {TYPE_TEMP, 20.6},
                            };
    */


    SendPayloadLoraBku(testpayload);
    delay(1000);    
    uint8_t *MSG = ReceiveDataLoraBku();
    if (MSG[0] = 0){Serial.println("No downlink message received at this time.");} 
    PrintMSGLoraBku(MSG);

    //You may stick to the fair use policy max 30 sec airtime per day per node
    //If you run this scetch 24/7 please set delay to 300000 or higher
    //Bitte beachte die maximale Sendezeit von 30 Sekunden pro Tag und Gerät
    //Bei rund um die Uhr Betrieb delay bitte mindestens auf 300000 setzen
    
    delay(22000);

}

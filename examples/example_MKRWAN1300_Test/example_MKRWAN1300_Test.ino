#include <Zanshin_BME680.h>
#include <LoRa-payload-BKU.h>

//use your secrets.h file or enter appEui & appKey below
//#include <c:\secrets\secrets.h>
String appEui = xxxxxxxxxxxxxxxx;
String appKey = xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;

//set your frequenze plan values are: (EU868,AS923,AU915,KR920,IN865,US915,US915_HYBRID)
_lora_band frequency = EU868;


void setup()
{
    Serial.begin(115200);
    BkuSetupLorawan(appEui, appKey, frequency);
    
    Serial.print("Your device EUI is: ");
    Serial.println(modem.deviceEUI());
}

void loop()
{
    //fill your payload
    BkuPayload testpayload[2];
    testpayload[0].TYPE = TYPE_TEMP;
    testpayload[0].wert = (-15.5);
    testpayload[1].TYPE = TYPE_RH;
    testpayload[1].wert = (27);
    
    /*
    BkuPayload testpayload2[] = {
                            payload(TYPE_RH, 66),
                            payload(TYPE_TEMP, 20.6),
                            };
    */
    /*
    BkuPayload testpayload3[] = {
                            {TYPE_RH, 66},
                            {TYPE_TEMP, 20.6},
                            };
    */


    BkuSendPayload(testpayload);
    delay(1000);    
    uint8_t *MSG = BkuReceiveData();
    if (MSG[0] = 0){Serial.println("No downlink message received at this time.");} 
    BkuPrintMSG(MSG);

    delay(22000);

}

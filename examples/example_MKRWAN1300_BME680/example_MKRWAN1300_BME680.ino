#include <Zanshin_BME680.h>
#include <LoRa_payload_BKU.h>

//Create an instance of the sensor
BME680_Class BME680;

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

    while (!BME680.begin(I2C_STANDARD_MODE))
    {
        Serial.print(F("-  Unable to find BME680. Trying again in 5 seconds.\n"));
        delay(5000);
    }
    BME680.setOversampling(TemperatureSensor,Oversample16); // Use enumerated type values
    BME680.setOversampling(HumiditySensor,   Oversample16); // Use enumerated type values
    BME680.setOversampling(PressureSensor,   Oversample16); // Use enumerated type values
    BME680.setIIRFilter(IIR4); // Use enumerated type values
    BME680.setGas(320,150); // 320°c for 150 milliseconds
}

int32_t inttemperature, inthumidity, intpressure, intgas;
double temperature, humidity, pressure, gas;

void loop()
{  
    BME680.getSensorData(inttemperature, inthumidity, intpressure, intgas, false);
    temperature = inttemperature/100.0;
    humidity = inthumidity/1000.0;
    pressure = intpressure/100.0;
    gas = intgas/100.0;

    //printMesswerte();

    //fill your payload
    BkuPayload testpayload[4];
    testpayload[0].TYPE = TYPE_TEMP;
    testpayload[0].wert = (temperature);
    testpayload[1].TYPE = TYPE_RH;
    testpayload[1].wert = (humidity);
    testpayload[2].TYPE = TYPE_PRESSURE;
    testpayload[2].wert = (pressure);
    testpayload[3].TYPE = TYPE_GAS_KOHMS;
    testpayload[3].wert = (gas);

    
    
    /*
    BkuPayload testpayload2[] = {
                            BkuPayload(TYPE_TEMP, temperature),
                            BkuPayload(TYPE_RH, humidity),
                            BkuPayload(TYPE_PRESSURE, pressure),
                            BkuPayload(TYPE_GAS_KOHMS, gas),
                            };
    */
    /*
    BkuPayload testpayload3[] = {
                            {TYPE_TEMP, temperature},
                            {TYPE_RH, humidity},
                            {TYPE_PRESSURE, pressure},
                            {TYPE_GAS_KOHMS, gas},
                            };
    */


    BkuSendPayload(testpayload);
    delay(1000);    
    uint8_t *MSG = BkuReceiveData();
    if (MSG[0] = 0){Serial.println("No downlink message received at this time.");} 
    BkuPrintMSG(MSG);

    //You may stick to the fair use policy max 30 sec airtime per day per node
    //If you run this scetch 24/7 please set delay to 300000 or higher
    //Bitte beachte die maximale Sendezeit von 30 Sekunden pro Tag und Gerät
    //Bei rund um die Uhr Betrieb delay bitte mindestens auf 300000 setzen

    delay(22000);
    //delay(300000);
}


void printMesswerte()
{
<<<<<<< HEAD
    Serial.print(temperature);
    Serial.print(" Grad\t\t");

    Serial.print(humidity);
    Serial.print(" Prozent\t\t");

    Serial.print(pressure);
    Serial.print(" Pascals\t\t");

    Serial.print(gas);
    Serial.println(" Air Quality");
}
=======
    //Serial.print("\t");
    Serial.print(temperature); //-1 damit Messung 1 bis 15 Schubladen 0 bis 14 ergeben
    Serial.print("\t\tGrad");

    //Serial.print("\t");
    Serial.print(humidity); //-1 damit Messung 1 bis 15 Schubladen 0 bis 14 ergeben
    Serial.print("\t\tProzent");

    //Serial.print("\t");
    Serial.print(pressure); //-1 damit Messung 1 bis 15 Schubladen 0 bis 14 ergeben
    Serial.print("\t\tPascals");

    //Serial.print("\t");
    Serial.print(gas); //-1 damit Messung 1 bis 15 Schubladen 0 bis 14 ergeben
    Serial.print("\t\tAir Quality");
    Serial.println("");
}
>>>>>>> f8ea605f9fd8b05f7bae1c56b2accd3c6080f46f

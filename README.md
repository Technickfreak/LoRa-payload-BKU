# LoRa-payload-BKU
# EN
This library will allow you to send predefined datatypes to TheThingsNetwork.org (TTN) via an Arduino MKRWAN 1300/1310.

### Preperation
Copy the content of the file "extras/Decoder.js" to the "Payload Formats" tab of your application on thethingsnetwork.org
### Sourcecode on your Arduino.
To fill your payload-object with your measurement data you have three options.
First you have to pass on the desired datatype from the list below, second your value. Repeat for all your measurements.
All three options lead to the same results.

# DE
Diese Library erlaubt es vorgefertigete Datentypen an TheThingsNetwork.org (TTN) mit einem Arduino MKRWAN 1300/1310 zu senden.
### Vorbereitung
Kopiere den Inhalt der Datei "extras/Decoder.js" in das "Payload Formats" Tab deiner Anwendug bei TheThingsNetwork.org
### Quellcode auf dem Arduino.
Um das Payload Objekt mit deinen Sensorwerten zu füllen gibt es drei Möglichkeiten.
In jeder übergibst du zuerst den gewünschten Datentypen aus der Liste (ganz unten), danach deinen Messwert. Wiederhole das für alle Messwerte.
Alle drei Möglichkeiten führen zum selben Ergebnis.

# Snippets

Nr1 (Zeilenweise Befüllung)
```
BkuPayload testpayload[2];
meinpayload[0].TYPE = TYPE_TEMP;
meinpayload[0].wert = (-15.5);
meinpayload[1].TYPE = TYPE_HUMIDITY;
meinpayload[1].wert = (27);
```
2 using the constructor
```
BkuPayload meinpayload[] = {
                        payload(TYPE_TEMP, -15.5),
                        payload(TYPE_HUMIDITY, 27),
                        };
```
3 using the constructor with String
```
BkuPayload meinpayload[] = {
                        {TYPE_TEMP, -15.5},
                        {TYPE_HUMIDITY, 27},
                        };
```
## supported datatypes
ELSYS.se compatible
``` 
TYPE_TEMP           = 0x01;  //temperature;         2 bytes;    1 decimal place;    -3276.8°C->3276.7°C;
TYPE_HUMIDITY       = 0x02;  //Humidity;            1 byte;     0 decimal place;    0->100%;
TYPE_ACC            = 0x03;  //acceleration;        3 bytes;    0 decimal place;    X,Y,Z -128->127 +/-63=1G;
TYPE_LIGHT          = 0x04;  //Light;               2 bytes;    0 decimal place;    0->65535 Lux;
TYPE_MOTION         = 0x05;  //No of motion         1 byte;     0 decimal place;    0->255;
TYPE_CO2            = 0x06;  //Co2                  2 bytes;    0 decimal place;    0->65535 ppm; 
TYPE_VDD            = 0x07;  //VDD                  2 byte;     0 decimal place;    0->65535mV;
TYPE_ANALOG1        = 0x08;  //Analog input 1       2 byte;     0 decimal place;    0->65535mV;
TYPE_GPS            = 0x09;  //GPS                  6 byte;     0 decimal place;    3 bytes lat 3 bytes long binary
TYPE_PULSE1         = 0x0A;  //Pulse input 2        2 bytes;    0 decimal place;    relative pulse count
TYPE_PULSE1_ABS     = 0x0B;  //Pulse 2 absolute     4 bytes;    0 decimal place;    no 0->0xFFFFFFFF
TYPE_EXT_TEMP1      = 0x0C;  //External temp        2 bytes;    1 decimal place;    -3276.5C->3276.5°C;
TYPE_EXT_DIGITAL    = 0x0D;  //Digital input        1 bytes;    0 decimal place;    value 1 or 0
TYPE_EXT_DISTANCE   = 0x0E;  //Distance sensor      2 bytes;    0 decimal place;    distance in mm
TYPE_ACC_MOTION     = 0x0F;  //Acc motion           1 byte;     0 decimal place;    number of vibration/motion
TYPE_IR_TEMP        = 0x10;  //IR temperature       4 bytes;    1 decimal place;    -3276.5C->3276.5°C; 2bytes internal temp 2bytes external temp
TYPE_OCCUPANCY      = 0x11;  //Body occupancy       1 byte;     0 decimal place;    data
TYPE_WATERLEAK      = 0x12;  //Water leak           1 byte;     0 decimal place;    0-255   data
TYPE_GRIDEYE        = 0x13;  //temperature         65 byte;     1 decimal place;    nicht inplementiert
TYPE_PRESSURE       = 0x14;  //External Pressure    4 byte;     3 decimal place;    pressure data (hPa)
TYPE_SOUND          = 0x15;  //Sound                2 byte;     0 decimal place;    sound data (peak/avg)
TYPE_PULSE2         = 0x16;  //Pulse input 2        2 bytes;    0 decimal place;    0->0xFFFF
TYPE_PULSE2_ABS     = 0x17;  //Pulse 2 absolute     4 bytes;    0 decimal place;    no 0->0xFFFFFFFF
TYPE_ANALOG2        = 0x18;  //Analog input 2       2 bytes;    0 decimal place;    voltage in mV
TYPE_EXT_TEMP2      = 0x19;  //External temp 2      2 bytes;    1 decimal place;    -3276.5C->3276.5°C;
TYPE_EXT_DIGITAL2   = 0x1A;  //Digital input 2      1 bytes;    0 decimal place;    value 1 or 0 
TYPE_EXT_ANALOG_UV  = 0x1B;  //Load cell analog uV  4 bytes;    0 decimal place;    signed int (uV)
TYPE_DEBUG          = 0x3D;  //debug                4 bytes;    0 decimal place;    debug
```
own extensions
```
TYPE_TEMP32		    = 0x1C;  //temperature;         4 bytes;    2 decimal place;    -21474836.48°C->21474181.12°C;
TYPE_HUMIDITY32     = 0x1D;  //Humidity;            4 byte;     2 decimal place;    0.00%->100.00%;
TYPE_GAS_KOHMS      = 0x1E;  //Gas qualität         4 Byte;     0 decimal place;    in kOhm
TYPE_sign_of_life   = 0x1F;  //minimale übertragung;0 bytes;    0 decimal place;    I_am_alive=true;
```

## extend List
To add your own datatypes please refer to /src/construct_TYPE.h and /extras/Decoder.js

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

1 line by line
```
BkuPayload testpayload[2];
meinpayload[0].TYPE = TYPE_TEMP;
meinpayload[0].wert = (-15.5);
meinpayload[1].TYPE = TYPE_HUMIDITY;
meinpayload[1].wert = (27);
```
2 using the constructor type1
```
BkuPayload meinpayload[] = {
                        payload(TYPE_TEMP, -15.5),
                        payload(TYPE_HUMIDITY, 27),
                        };
```
3 using the constructor type2
```
BkuPayload meinpayload[] = {
                        {TYPE_TEMP, -15.5},
                        {TYPE_HUMIDITY, 27},
                        };
```
## supported datatypes
ELSYS.se compatible

TYPE_TEMP           = 0x01;  //temperature;         2 bytes;    1 decimal place;    -3276.8°C->3276.7°C;
|activated|TYPE_Bezeichnung|TYPE_ID|Übertragungs einheit|bytes|decimal place|Übertragungs min -> Übertragungs max|
| --- | --- | --- | --- | --- | --- | --- |
| {0} | {1} | {2} | {3} | {4} | {5} | {6} |
| compile | TYPE_Bezeichnung | TYPE_ID | Übertragungs einheit | bytes | sub bytes | decimal place |
| true | TYPE_TEMP | 0x01 | temperature | 2 | 2 | 1 |
| false | TYPE_HUMIDITY | 0x02 | Humidity | 1 | 1 | 0 |
| true | TYPE_ACC | 0x03 | ["Acceleration","x","y","z"] | 3 | [3,1,1,1] | 0 |
| false | TYPE_LIGHT | 0x04 | Light | 2 | 2 | 0 |
| false | TYPE_MOTION | 0x05 | No of motion | 1 | 1 | 0 |
| false | TYPE_CO2 | 0x06 | Co2 | 2 | 2 | 0 |
| false | TYPE_VDD | 0x07 | VDD | 2 | 2 | 0 |
| false | TYPE_ANALOG1 | 0x08 | Analog input 1 | 2 | 2 | 0 |
| false | TYPE_GPS | 0x09 | ["GPS","lat","long"] | 6 | [6,3,3] | 0 |
| false | TYPE_PULSE1 | 0x0A | Pulse input 2 | 2 | 2 | 0 |
| false | TYPE_PULSE1_ABS | 0x0B | Pulse 2 absolute | 4 | 4 | 0 |
| false | TYPE_EXT_TEMP1 | 0x0C | External temp | 2 | 2 | 1 |
| false | TYPE_EXT_DIGITAL | 0x0D | Digital input | 1 | 1 | 0 |
| false | TYPE_EXT_DISTANCE | 0x0E | Distance sensor | 2 | 2 | 0 |
| false | TYPE_ACC_MOTION | 0x0F | Acc motion | 1 | 1 | 0 |
| false | TYPE_IR_TEMP | 0x10 | ["IR temperature","irInternalTemperature","irExternalTemperature"] | 4 | [4,2,2] | 1 |
| false | TYPE_OCCUPANCY | 0x11 | Body occupancy | 1 | 1 | 0 |
| false | TYPE_WATERLEAK | 0x12 | Water leak | 1 | 1 | 0 |
| false | TYPE_GRIDEYE | 0x13 | grideye Error: nicht inplementiert | 52 | 52 | 1 |
| false | TYPE_PRESSURE | 0x14 | External Pressure | 4 | 4 | 3 |
| false | TYPE_SOUND | 0x15 | ["Sound","soundPeak","soundAvg"] | 2 | [2,1,1] | 0 |
| false | TYPE_PULSE2 | 0x16 | Pulse input 2 | 2 | 2 | 0 |
| false | TYPE_PULSE2_ABS | 0x17 | Pulse 2 absolute | 4 | 4 | 0 |
| false | TYPE_ANALOG2 | 0x18 | Analog input 2 | 2 | 2 | 0 |
| false | TYPE_EXT_TEMP2 | 0x19 | External temp 2 | 2 | 2 | 1 |
| false | TYPE_EXT_DIGITAL2 | 0x1A | Digital input 2 | 1 | 1 | 0 |
| false | TYPE_EXT_ANALOG_UV | 0x1B | Load cell analog uV | 4 | 4 | 0 |
| false | TYPE_DEBUG | 0x3D | debug | 4 | 4 | 0 |

## extend List
To add your own datatypes please refer to /src/construct_TYPE.h and /extras/Decoder.js

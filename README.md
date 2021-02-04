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
<!--TYPE_TEMP           = 0x01;  //temperature;         2 bytes;    1 decimal place;    -3276.8°C->3276.7°C;-->
| compile | TYPE_Bezeichnung | TYPE_ID | Übertragungs min -> Übertragungs max    | beschreibung |
| --- | --- | --- | --- | --- |
| true | TYPE_TEMP | 0x01 | -3276.8°C->3276.7°C |  |
| false | TYPE_HUMIDITY | 0x02 | 0%->100% |  |
| true | TYPE_ACC | 0x03 | X,Y,Z -128->127 +/-63 1G |  |
| false | TYPE_LIGHT | 0x04 | 0->65535 Lux |  |
| false | TYPE_MOTION | 0x05 | 0->255 |  |
| false | TYPE_CO2 | 0x06 | 0->65535 ppm |  |
| false | TYPE_VDD | 0x07 | 0->65535 mV |  |
| false | TYPE_ANALOG1 | 0x08 | 0->65535 mV |  |
| false | TYPE_GPS | 0x09 |  | 3 bytes lat 3 bytes long binary |
| false | TYPE_PULSE1 | 0x0A | 0->0xFFFF | relative pulse count |
| false | TYPE_PULSE1_ABS | 0x0B | no 0->0xFFFFFFFF |  |
| false | TYPE_EXT_TEMP1 | 0x0C | -3276.5C->3276.5°C |  |
| false | TYPE_EXT_DIGITAL | 0x0D |  | value 1 or 0 |
| false | TYPE_EXT_DISTANCE | 0x0E |  | distance in mm |
| false | TYPE_ACC_MOTION | 0x0F |  | number of vibration/motion |
| false | TYPE_IR_TEMP | 0x10 | -3276.5C->3276.5°C  | 2bytes internal temp 2bytes external temp |
| false | TYPE_OCCUPANCY | 0x11 | data |  |
| false | TYPE_WATERLEAK | 0x12 | 0-255   data |  |
| false | TYPE_GRIDEYE | 0x13 |  | nicht inplementiert |
| false | TYPE_PRESSURE | 0x14 |  | pressure data (hPa) |
| false | TYPE_SOUND | 0x15 |  | sound data (peak/avg) |
| false | TYPE_PULSE2 | 0x16 | 0->0xFFFF |  |
| false | TYPE_PULSE2_ABS | 0x17 | no 0->0xFFFFFFFF |  |
| false | TYPE_ANALOG2 | 0x18 | 0->65535 mV | voltage in mV |
| false | TYPE_EXT_TEMP2 | 0x19 | -3276.5C->3276.5°C |  |
| false | TYPE_EXT_DIGITAL2 | 0x1A |  | value 1 or 0  |
| false | TYPE_EXT_ANALOG_UV | 0x1B |  | signed int (uV) |
| false | TYPE_DEBUG | 0x3D |  | debug |

## extend List
To add your own datatypes please refer to /src/construct_TYPE.h and /extras/Decoder.js

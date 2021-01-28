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
<!--Python-Marker#| {0} | {1} | {2} | {3} | {4} | {5} | {6} | -->
<!--Python-Marker#| {0} | {1} | {2} | {3} | {4} | {5} | {6} | -->

## extend List
To add your own datatypes please refer to /src/construct_TYPE.h and /extras/Decoder.js

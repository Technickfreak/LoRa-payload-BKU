# LoRa-payload-BKU

Diese Library erlaubt es vorgefertigete Datentypen an TheThingsNetwork.org zu senden.




## Arbeitsweise:
### Vorbereitung
Kopiere den Inhalt der Datei extras/Decoder.js in den Payload Formats Tab bei deiner Anwendug bei The Things Network.org

### Schritt1.
Initialisiere ein Objekt vom Type "payload" mit einem frei Wählbaren Namen,
gib in den Klammern die Anzahl der zu übertragenden Datensätzen pro Sendung an.
        paylaod meinpayload[2];

### Schritt2.
Befülle dein Payload Objekt mit deinen Sensorwerten dazu übergibst du 
Erste den gewünschten Datentypen aus der Liste unten, dann deinen Messwert.
Für diesen Vorgang stehten dir 3 Möglichkeiten/Vorgehensweisen zur Verfügung.
Alle 3 Möglichkeitren führen zum Selben Ergebniss.
Nr1 (Zeilenweise Befüllung)
   
    meinpayload[0].TYPE = TYPE_TEMP;
    meinpayload[0].wert = (-15.5);
    meinpayload[1].TYPE = TYPE_RH;
    meinpayload[1].wert = (27);


Nr2 (Blockweise Befüllung mit Aufruf des Datentypen)

    payload meinpayload[] = {
                            payload(TYPE_TEMP, -15.5),
                            payload(TYPE_RH, 27),
                            };


Nr3 (Blockweise Befüllung z.B aus einem String)

    payload meinpayload[] = {
                            {TYPE_TEMP, -15.5},
                            {TYPE_RH, 27},
                            };







## Unterstütze Daten Formate
ELSYS.se kopatiebel
``` 
TYPE_TEMP           = 0x01;  //temperature;         2 bytes;    1 decimal place;    -3276.8°C->3276.7°C;
TYPE_RH             = 0x02;  //Humidity;            1 byte;     0 decimal place;    0->100%;
TYPE_ACC            = 0x03;  //acceleration;        3 bytes;    0 decimal place;    X,Y,Z -128->127 +/-63=1G;
TYPE_LIGHT          = 0x04;  //Light;               2 bytes;    0 decimal place;    0->65535 Lux;
TYPE_MOTION         = 0x05;  //No of motion         1 byte;     0 decimal place;    0->255;
TYPE_CO2            = 0x06;  //Co2                  2 bytes;    0 decimal place;    0->65535 ppm; 
TYPE_VDD            = 0x07;  //VDD                  2 byte;     0 decimal place;    0->65535mV;
TYPE_ANALOG1        = 0x08;  //Analog input 1       2 byte;     0 decimal place;    0->65535mV;
TYPE_GPS            = 0x09;  //GPS                  6 byte;     0 decimal place;                                        3 bytes lat 3 bytes long binary
TYPE_PULSE1         = 0x0A;  //Pulse input 2        2 bytes;    0 decimal place;                                        relative pulse count
TYPE_PULSE1_ABS     = 0x0B;  //Pulse 2 absolute     4 bytes;    0 decimal place;    no 0->0xFFFFFFFF
TYPE_EXT_TEMP1      = 0x0C;  //External temp        2 bytes;    1 decimal place;    -3276.5C->3276.5°C;
TYPE_EXT_DIGITAL    = 0x0D;  //Digital input        1 bytes;    0 decimal place;                                        value 1 or 0
TYPE_EXT_DISTANCE   = 0x0E;  //Distance sensor      2 bytes;    0 decimal place;                                        distance in mm
TYPE_ACC_MOTION     = 0x0F;  //Acc motion           1 byte;     0 decimal place;                                        number of vibration/motion
TYPE_IR_TEMP        = 0x10;  //IR temperature       4 bytes;    1 decimal place;    -3276.5C->3276.5°C;                2bytes internal temp 2bytes external temp
TYPE_OCCUPANCY      = 0x11;  //Body occupancy       1 byte;     0 decimal place;                                        data
TYPE_WATERLEAK      = 0x12;  //Water leak           1 byte;     0 decimal place;    0-255                               data
TYPE_GRIDEYE        = 0x13;  //temperature         65 byte;     1 decimal place;                                        nicht inplementiert
TYPE_PRESSURE       = 0x14;  //External Pressure    4 byte;     3 decimal place;                                        pressure data (hPa)
TYPE_SOUND          = 0x15;  //Sound                2 byte;     0 decimal place;                                        sound data (peak/avg)
TYPE_PULSE2         = 0x16;  //Pulse input 2        2 bytes;    0 decimal place;    0->0xFFFF
TYPE_PULSE2_ABS     = 0x17;  //Pulse 2 absolute     4 bytes;    0 decimal place;    no 0->0xFFFFFFFF
TYPE_ANALOG2        = 0x18;  //Analog input 2       2 bytes;    0 decimal place;                                        voltage in mV
TYPE_EXT_TEMP2      = 0x19;  //External temp 2      2 bytes;    1 decimal place;    -3276.5C->3276.5°C;
TYPE_EXT_DIGITAL2   = 0x1A;  //Digital input 2      1 bytes;    0 decimal place;                                        value 1 or 0 
TYPE_EXT_ANALOG_UV  = 0x1B;  //Load cell analog uV  4 bytes;    0 decimal place;                                        signed int (uV)
TYPE_DEBUG          = 0x3D;  //debug                4 bytes;    0 decimal place;                                        debug
```
Eigene erweiterungen
```
TYPE_TEMP32		    = 0x1C;  //temperature;         4 bytes;    2 decimal place;    -21474836.48°C->21474181.12°C;
TYPE_RH32           = 0x1D;  //Humidity;            4 byte;     2 decimal place;    0.00%->100.00%;
TYPE_GAS_KOHMS      = 0x1E;  //Gas qualität         4 Byte;     0 decimal place;                                        in KOhm
TYPE_sign_of_life   = 0x1F;  //minimale übertragung;0 bytes;    0 decimal place;    I_am_alive=true;
```
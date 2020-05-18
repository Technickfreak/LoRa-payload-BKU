#ifndef _Encoder_TYPE_h
#define _Encoder_TYPE_h

    typedef enum{
        //   \/  ELSYS kopatiebel \/
        TYPE_TEMP           = 0x01,  //temperature;         2 bytes;    1 decimal place;    -3276.8°C --> 3276.7°C;
        TYPE_RH             = 0x02,  //Humidity;            1 byte;     0 decimal place;    0-100%;
        TYPE_ACC            = 0x03,  //acceleration;        3 bytes;    0 decimal place;    X,Y,Z -128 --> 127 +/-63=1G;
        TYPE_LIGHT          = 0x04,  //Light;               2 bytes;    0 decimal place;    0-->65535 Lux;
        TYPE_MOTION         = 0x05,  //No of motion         1 byte;     0 decimal place;    0-255
        TYPE_CO2            = 0x06,  //Co2                  2 bytes;    0 decimal place;    0-65535 ppm 
        TYPE_VDD            = 0x07,  //VDD                  2 byte;     0 decimal place;    0-65535mV
        TYPE_ANALOG1        = 0x08,  //Analog input 1       2 byte;     0 decimal place;    0-65535mV
        TYPE_GPS            = 0x09,  //GPS                  6 byte;     0 decimal place;    3 bytes lat 3 bytes long binary
        TYPE_PULSE1         = 0x0A,  //Pulse input 2        2 bytes;    0 decimal place;    relative pulse count
        TYPE_PULSE1_ABS     = 0x0B,  //Pulse 2 absolute     4 bytes;    0 decimal place;    no 0->0xFFFFFFFF
        TYPE_EXT_TEMP1      = 0x0C,  //External temp        2 bytes;    1 decimal place;    -3276.5C-->3276.5C
        TYPE_EXT_DIGITAL    = 0x0D,  //Digital input        1 bytes;    0 decimal place;    value 1 or 0
        TYPE_EXT_DISTANCE   = 0x0E,  //Distance sensor      2 bytes;    0 decimal place;    distance in mm
        TYPE_ACC_MOTION     = 0x0F,  //Acc motion           1 byte;     0 decimal place;    number of vibration/motion
        TYPE_IR_TEMP        = 0x10,  //IR temperature       4 bytes;    1 decimal place;    2bytes internal temp 2bytes external temp -3276.5C-->3276.5C
        TYPE_OCCUPANCY      = 0x11,  //Body occupancy       1 byte;     0 decimal place;    data
        TYPE_WATERLEAK      = 0x12,  //Water leak           1 byte;     0 decimal place;    data 0-255 
        TYPE_GRIDEYE        = 0x13,  //temperature         65 byte;     1 decimal place;    1byte ref + 64*1byte external temp
        TYPE_PRESSURE       = 0x14,  //External Pressure    4 byte;     3 decimal place;    pressure data (hPa)
        TYPE_SOUND          = 0x15,  //Sound                2 byte;     0 decimal place;    sound data (peak/avg)
        TYPE_PULSE2         = 0x16,  //Pulse input 2        2 bytes;    0 decimal place;    0-->0xFFFF
        TYPE_PULSE2_ABS     = 0x17,  //Pulse 2 absolute     4 bytes;    0 decimal place;    no 0->0xFFFFFFFF
        TYPE_ANALOG2        = 0x18,  //Analog input 2       2 bytes;    0 decimal place;    voltage in mV
        TYPE_EXT_TEMP2      = 0x19,  //External temp 2      2 bytes;    1 decimal place;    -3276.5C-->3276.5C
        TYPE_EXT_DIGITAL2   = 0x1A,  //Digital input 2      1 bytes;    0 decimal place;    value 1 or 0 
        TYPE_EXT_ANALOG_UV  = 0x1B,  //Load cell analog uV  4 bytes;    0 decimal place;    signed int (uV)
        TYPE_DEBUG          = 0x3D,  //debug                4 bytes;    0 decimal place;    debug
        //   /\  ELSES kopatiebel /\ 

        TYPE_TEMP32		    = 0x1C,  //temperature;         4 bytes;    2 decimal place; 
        TYPE_RH32           = 0x1D,  //Humidity;            4 byte;     2 decimal place;    0-100%;
        TYPE_GAS_KOHMS      = 0x1E,  //Gas qualität         4 Byte;     0 decimal place;    in KOhm
        TYPE_sign_of_life   = 0x1F,  //minimale übertragung;0 bytes;    0 decimal place;    I_am_alive=true;

    } TYPE_;


    // Definiert die Anzahl der reservierten Bytes im Payload Array //EN:Defines number of bytes used in Payload Array 
    int TYPE_byte_amount(TYPE_ type) {          
        switch (type)
        {
        case TYPE_TEMP:
            return 2;
        case TYPE_RH:
            return 1;
        case TYPE_ACC:
            return 3;
        case TYPE_LIGHT:
            return 2;
        case TYPE_MOTION:
            return 1;
        case TYPE_CO2:
            return 2;
        case TYPE_VDD:
            return 2;
        case TYPE_ANALOG1:
            return 2;
        case TYPE_GPS:
            return 6;
        case TYPE_PULSE1:
            return 2;
        case TYPE_PULSE1_ABS:
            return 4;
        case TYPE_EXT_TEMP1:
            return 2;
        case TYPE_EXT_DIGITAL:
            return 1;
        case TYPE_EXT_DISTANCE:
            return 2;
        case TYPE_ACC_MOTION:
            return 1;
        case TYPE_IR_TEMP:
            return 4;
        case TYPE_OCCUPANCY:
            return 1;
        case TYPE_WATERLEAK:
            return 1;
        case TYPE_GRIDEYE:
            return 65;
        case TYPE_PRESSURE:
            return 4;
        case TYPE_SOUND:
            return 2;
        case TYPE_PULSE2:
            return 2;
        case TYPE_PULSE2_ABS:
            return 4;
        case TYPE_ANALOG2:
            return 2;
        case TYPE_EXT_TEMP2:
            return 2;
        case TYPE_EXT_DIGITAL2:
            return 1;
        case TYPE_EXT_ANALOG_UV:
            return 4;
        case TYPE_DEBUG:
            return 4;



        case TYPE_TEMP32:
            return 4;    
        case TYPE_RH32:
            return 4; 
        case TYPE_GAS_KOHMS:
            return 4;    
        case TYPE_sign_of_life:
            return 0; 
        

        default:
            return 0;
        }
    }

    // Definiert die Anzahl der Nachkomma Stellen die Übertragen werden //EN: Defines number of decimal places kept to transmit
    int TYPE_decimal_places(TYPE_ type) {
        switch (type)
        {
        case TYPE_TEMP:
            return 1;
        case TYPE_RH:
            return 0;
        case TYPE_ACC:
            return 0;
        case TYPE_LIGHT:
            return 0;
        case TYPE_MOTION:
            return 0;
        case TYPE_CO2:
            return 0;
        case TYPE_VDD:
            return 0;
        case TYPE_ANALOG1:
            return 0;
        case TYPE_GPS:
            return 0;
        case TYPE_PULSE1:
            return 0;
        case TYPE_PULSE1_ABS:
            return 0;
        case TYPE_EXT_TEMP1:
            return 1;
        case TYPE_EXT_DIGITAL:
            return 0;
        case TYPE_EXT_DISTANCE:
            return 0;
        case TYPE_ACC_MOTION:
            return 0;
        case TYPE_IR_TEMP:
            return 1;
        case TYPE_OCCUPANCY:
            return 0;
        case TYPE_WATERLEAK:
            return 0;
        case TYPE_GRIDEYE:
            return 1;
        case TYPE_PRESSURE:
            return 3;
        case TYPE_SOUND:
            return 0;
        case TYPE_PULSE2:
            return 0;
        case TYPE_PULSE2_ABS:
            return 0;
        case TYPE_ANALOG2:
            return 0;
        case TYPE_EXT_TEMP2:
            return 1;
        case TYPE_EXT_DIGITAL2:
            return 0;
        case TYPE_EXT_ANALOG_UV:
            return 0;
        case TYPE_DEBUG:
            return 0;



        case TYPE_TEMP32:
            return 2;    
        case TYPE_RH32:
            return 2; 
        case TYPE_GAS_KOHMS:
            return 0;    
        case TYPE_sign_of_life:
            return 0;


        default:
            return 0;
        }
    }



    struct payload
    {
        static int size;    //länge des Arrays
        double wert;        //Nimmt den Wert des Users entgegen //EN: Carries the Value from User
        TYPE_ TYPE;         //in Encoder_TYPE.h difnirte Datentypen //EN: Carries DataTypes defined in Encoder_TYPE.h file
        payload(){
            size ++;
        }
        payload(TYPE_ TYPE, double wert):TYPE(TYPE), wert(wert){
            size ++;
        }
        ~payload(){
            size --;
        }
        
        // gibt die Anzahl der reservierten Bytes im Payload Array zurück //EN:returns number of bytes used in Payload Array 
        int getLength(){
            return TYPE_byte_amount(TYPE);
        }
        // Konvertiert den Benutzerwert in eine Ganzzahl und passt die Dezimalstellen entsprechend dem ausgewählten Datentyp an. //EN: Converts User Value to Integer and adjusts decimal places according to chosen Data type.
        int get_int_wert(){
            return wert * pow(10, TYPE_decimal_places(TYPE));
        }
        
        //Gibt die Gesammtgröße des erstelleten Arrays zurück //EN: Returns the total size of the created array
        int arraysize(){
            return size;
        }
    };

    int payload::size = 0;


    int payloadlength(payload *mypayload){
        int length = 0;
        for (size_t i = 0; i < mypayload[0].arraysize(); i++)
        {
            length += mypayload[i].getLength() + 1;
        }
        return length;
    }


    uint8_t *buildPayload = nullptr;
    uint8_t *payloadconverter(payload *mypayload){
        
        delete[] buildPayload;
        int uebertrag = payloadlength(mypayload);
        
        uint8_t *buildPayload = new uint8_t[uebertrag];

        int buildposition = 0;

        for (size_t i = 0; i < mypayload[0].arraysize(); i++)
        {
            buildPayload[buildposition] = mypayload[i].TYPE;
            buildposition ++;
            for (size_t k = 0; k < mypayload[i].getLength(); k++)
            {
                uint8_t o = lowByte(mypayload[i].get_int_wert()>>(mypayload[i].getLength()*8-8*(k+1)));
                buildPayload[buildposition] = o;
                buildposition ++;
            }
            
        }
        //uint8_t buildPayload2[] = {*buildPayload};
        //delete[] buildPayload;
        return buildPayload;
    }
    
    void printPayload(payload *mypayload)
    {	
        //uint8_t MSG[] = {uint8_t(payloadconverter(mypayload))};
        uint8_t MSG[] = {*payloadconverter(mypayload)};
        for (size_t i = 0; i < payloadlength(mypayload); i++)
        {
            if (MSG[i]<0x10) {Serial.print("0");}
            Serial.print(MSG[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
    }
    

#endif
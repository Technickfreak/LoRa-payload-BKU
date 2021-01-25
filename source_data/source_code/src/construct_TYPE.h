#ifndef _construct_TYPE_h
#define _construct_TYPE_h

namespace Bku
{

    typedef enum
    {
        //TYPE_TEMP = 0x01,
        //Python-Marker#\t\t{1} = {2},
        

    } TYPE_;

    namespace debugStatusLoraBku
    {

        // Definiert die Anzahl der reservierten Bytes im Payload Array //EN:Defines number of bytes used in Payload Array
        int TYPE_byte_amount(TYPE_ type)
        {
            switch (type)
            {
            //Python-Marker#\t\t\tcase {1}: \n\t\t\t\treturn {4};

          
            default:
                return 0;
            }
        }

        // Definiert die Anzahl der Nachkomma Stellen die Übertragen werden //EN: Defines number of decimal places kept to transmit
        int TYPE_decimal_places(TYPE_ type)
        {
            switch (type)
            {
            //Python-Marker#\t\t\tcase {1}: \n\t\t\t\treturn {5};
            

            default:
                return 0;
            }
        }

    } // namespace debugStatusLoraBku

    struct PayloadLoraBku
    {
        static int size; //länge des Arrays
        double wert;     //Nimmt den Wert des Users entgegen //EN: Carries the Value from User
        TYPE_ TYPE;      //in construct_TYPE.h difnirte Datentypen //EN: Carries DataTypes defined in construct_TYPE.h file
        PayloadLoraBku()
        {
            size++;
        }
        PayloadLoraBku(TYPE_ TYPE, double wert) : TYPE(TYPE), wert(wert)
        {
            size++;
        }
        ~PayloadLoraBku()
        {
            size--;
        }

        // gibt die Anzahl der reservierten Bytes im Payload Array zurück //EN:returns number of bytes used in Payload Array
        int getLength()
        {
            return debugStatusLoraBku::TYPE_byte_amount(TYPE);
        }
        // Konvertiert den Benutzerwert in eine Ganzzahl und passt die Dezimalstellen entsprechend dem ausgewählten Datentyp an. //EN: Converts User Value to Integer and adjusts decimal places according to chosen Data type.
        int get_int_wert()
        {
            return wert * pow(10, debugStatusLoraBku::TYPE_decimal_places(TYPE));
        }

        //Gibt die Gesammtgröße des erstelleten Arrays zurück //EN: Returns the total size of the created array
        int arraysize()
        {
            return size;
        }
    };
    int PayloadLoraBku::size = 0;

    int PayloadlengthLoraBku(PayloadLoraBku *mypayload)
    {
        int length = 0;
        for (size_t i = 0; i < mypayload[0].arraysize(); i++)
        {
            length += mypayload[i].getLength() + 1;
        }
        return length;
    }

    uint8_t* PayloadconverterLoraBku(PayloadLoraBku *mypayload)
    {
        //uint8_t *buildPayload = nullptr;
        //delete[] buildPayload;
        int uebertrag = PayloadlengthLoraBku(mypayload);

        uint8_t *buildPayload = new uint8_t[uebertrag];

        int buildposition = 0;

        for (size_t i = 0; i < mypayload[0].arraysize(); i++)
        {
            buildPayload[buildposition] = mypayload[i].TYPE;
            buildposition++;
            for (size_t k = 0; k < mypayload[i].getLength(); k++)
            {
                uint8_t o = lowByte(mypayload[i].get_int_wert() >> (mypayload[i].getLength() * 8 - 8 * (k + 1)));
                buildPayload[buildposition] = o;
                buildposition++;
            }
        }
        //uint8_t buildPayload2[] = {*buildPayload};
        //delete[] buildPayload;
        return buildPayload;
    }

    void PrintPayloadLoraBku(PayloadLoraBku *mypayload)
    {
        //uint8_t MSG[] = {uint8_t(payloadconverter(mypayload))};
        uint8_t MSG[] = {*PayloadconverterLoraBku(mypayload)};
        for (size_t i = 0; i < PayloadlengthLoraBku(mypayload); i++)
        {
            if (MSG[i] < 0x10)
            {
                Serial.print("0");
            }
            Serial.print(MSG[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
    }

} // namespace Bku
#endif
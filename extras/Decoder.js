/*
  ELSYS simple payload decoder. 
  Use it as it is or remove the bugs :)
  www.elsys.se
  peter@elsys.se
*/

//   \/  ELSYS kopatiebel \/
var TYPE_TEMP           = 0x01;  //temperature;             2 bytes;    1 decimal place;    -3276.8°C --> 3276.7°C;
var TYPE_HUMIDITY       = 0x02;  //Humidity;                1 byte;     0 decimal place;    0-100%;
var TYPE_ACC            = 0x03;  //acceleration;            3 bytes;    0 decimal place;    X,Y,Z -128 --> 127 +/-63=1G;
var TYPE_LIGHT          = 0x04;  //Light;                   2 bytes;    0 decimal place;    0-->65535 Lux;
var TYPE_MOTION         = 0x05;  //No of motion             1 byte;     0 decimal place;    0-255
var TYPE_CO2            = 0x06;  //Co2                      2 bytes;    0 decimal place;    0-65535 ppm 
var TYPE_VDD            = 0x07;  //VDD                      2 byte;     0 decimal place;    0-65535mV
var TYPE_ANALOG1        = 0x08;  //Analog input 1           2 byte;     0 decimal place;    0-65535mV
var TYPE_GPS            = 0x09;  //GPS                      6 byte;     0 decimal place;                                        3 bytes lat 3 bytes long binary
var TYPE_PULSE1         = 0x0A;  //Pulse input 1            2 bytes;    0 decimal place;                                        relative pulse count
var TYPE_PULSE1_ABS     = 0x0B;  //Pulse 1 absolute         4 bytes;    0 decimal place;    no 0->0xFFFFFFFF
var TYPE_EXT_TEMP1      = 0x0C;  //External temp            2 bytes;    1 decimal place;    -3276.5C-->3276.5°C;
var TYPE_EXT_DIGITAL    = 0x0D;  //Digital input            1 bytes;    0 decimal place;                                        value 1 or 0
var TYPE_EXT_DISTANCE   = 0x0E;  //Distance sensor          2 bytes;    0 decimal place;                                        distance in mm
var TYPE_ACC_MOTION     = 0x0F;  //Acc motion               1 byte;     0 decimal place;                                        number of vibration/motion
var TYPE_IR_TEMP        = 0x10;  //IR temperature           4 bytes;    1 decimal place;    -3276.5C-->3276.5°C;                2bytes internal temp 2bytes external temp
var TYPE_OCCUPANCY      = 0x11;  //Body occupancy           1 byte;     0 decimal place;    data
var TYPE_WATERLEAK      = 0x12;  //Water leak               1 byte;     0 decimal place;    data 0-255 
var TYPE_GRIDEYE        = 0x13;  //temperature             65 byte;     1 decimal place;                                        1byte ref + 64*1byte external temp
var TYPE_PRESSURE       = 0x14;  //External Pressure        4 byte;     3 decimal place;                                        pressure data (hPa)
var TYPE_SOUND          = 0x15;  //Sound                    2 byte;     0 decimal place;                                        sound data (peak/avg)
var TYPE_PULSE2         = 0x16;  //Pulse input 2            2 bytes;    0 decimal place;    0-->0xFFFF
var TYPE_PULSE2_ABS     = 0x17;  //Pulse 2 absolute         4 bytes;    0 decimal place;    no 0->0xFFFFFFFF
var TYPE_ANALOG2        = 0x18;  //Analog input 2           2 bytes;    0 decimal place;                                        voltage in mV
var TYPE_EXT_TEMP2      = 0x19;  //External temp 2          2 bytes;    1 decimal place;    -3276.5C-->3276.5°C;
var TYPE_EXT_DIGITAL2   = 0x1A;  //Digital input 2          1 bytes;    0 decimal place;                                        value 1 or 0 
var TYPE_EXT_ANALOG_UV  = 0x1B;  //Load cell analog uV      4 bytes;    0 decimal place;                                        signed int (uV)
var TYPE_DEBUG          = 0x3D;  //debug                    4 bytes;    0 decimal place;                                        debug
//   /\  ELSYS kopatiebel /\ 

var TYPE_TEMP32		    = 0x1C;  //temperature;             4 bytes;    2 decimal place;    -21474836.48°C --> 21474181.12°C;
var TYPE_HUMIDITY32           = 0x1D;  //Humidity;                4 byte;     2 decimal place;    0.00%-100.00%;
var TYPE_GAS_KOHMS      = 0x1E;  //air sensor resistance;   4 Byte;     0 decimal place;                                        in KOhm
var TYPE_sign_of_life   = 0x1F;  //minimale übertragung;    0 bytes;    0 decimal place;    I_am_alive=true;


function TYPE_Name_relation(TYPE_ID) {
    switch (TYPE_ID) {
        case TYPE_TEMP:
            return "temperature";
        case TYPE_HUMIDITY:
            return "humidity";
        case TYPE_ACC:
            return ["Acceleration","x","y","z"];
        case TYPE_LIGHT:
            return "Light";
        case TYPE_MOTION:
            return "No of motion";
        case TYPE_CO2:
            return "Co2";
        case TYPE_VDD:
            return "VDD";
        case TYPE_ANALOG1:
            return "Analog input 1";
        case TYPE_GPS:
            return ["GPS","lat","long"];
        case TYPE_PULSE1:
            return "Pulse input 1";
        case TYPE_PULSE1_ABS:
            return "Pulse 1 absolute";
        case TYPE_EXT_TEMP1:
            return "External temp";
        case TYPE_EXT_DIGITAL:
            return "Digital input";
        case TYPE_EXT_DISTANCE:
            return "Distance sensor";
        case TYPE_ACC_MOTION:
            return "Acc motion";
        case TYPE_IR_TEMP:
            return ["IR temperature","irInternalTemperature","irExternalTemperature"];
        case TYPE_OCCUPANCY:
            return "Body occupancy";
        case TYPE_WATERLEAK:
            return "Water leak";
        case TYPE_GRIDEYE:
            var grideye = ["grideye","ref"];
            for (grideyeN_i = 0; grideyeN_i < 64; grideyeN_i++) {grideye[grideyeN_i+2] = "grideye["+grideyeN_i+"]";}
            return "grideye Error: nicht inplementiert";
        case TYPE_PRESSURE:
            return "External Pressure";
        case TYPE_SOUND:
            return ["Sound","soundPeak","soundAvg"];
        case TYPE_PULSE2:
            return "Pulse input 2";
        case TYPE_PULSE2_ABS:
            return "Pulse 2 absolute";
        case TYPE_ANALOG2:
            return "Analog input 2";
        case TYPE_EXT_TEMP2:
            return "External temp 2";
        case TYPE_EXT_DIGITAL2:
            return "Digital input 2";
        case TYPE_EXT_ANALOG_UV:
            return "Load cell analog uV";
        case TYPE_DEBUG:
            return "debug";



        case TYPE_TEMP32:
            return "temperature";    
        case TYPE_HUMIDITY32:
            return "Humidity"; 
        case TYPE_GAS_KOHMS:
            return "air sensor resistance";    
        case TYPE_sign_of_life:
            return "I_am_alive"; 
        

        default:
            return 0;
    }

}
function TYPE_byte_amount(TYPE_ID) {
    switch (TYPE_ID) {
        case TYPE_TEMP:
            return 2;
        case TYPE_HUMIDITY:
            return 1;
        case TYPE_ACC:
            return [3,1,1,1];
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
            return [6,3,3];
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
            return [4,2,2];
        case TYPE_OCCUPANCY:
            return 1;
        case TYPE_WATERLEAK:
            return 1;
        case TYPE_GRIDEYE:
            var grideye = [65,1];
            for (grideye_i = 0+2; grideye_i < 64+2; grideye_i++) {grideye[grideye_i] = 1;}
            return 52;//65;
        case TYPE_PRESSURE:
            return 4;
        case TYPE_SOUND:
            return [2,1,1];
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
        case TYPE_HUMIDITY32:
            return 4; 
        case TYPE_GAS_KOHMS:
            return 4;    
        case TYPE_sign_of_life:
            return 0; 
        

        default:
            return 0;
    }
}
function TYPE_decimal_places(TYPE_ID) {
    switch (TYPE_ID) {
        case TYPE_TEMP:
            return 1;
        case TYPE_EXT_TEMP1:
            return 1;        
        case TYPE_IR_TEMP:
            return 1;        
        case TYPE_GRIDEYE:
            return 1;
        case TYPE_PRESSURE:
            return 3;        
        case TYPE_EXT_TEMP2:
            return 1;

        case TYPE_TEMP32:
            return 2;    
        case TYPE_HUMIDITY32:
            return 2;

        default:    //all other 0 decimal_places
            return 0;
    }
}
function TYPE_with_sign(TYPE_ID) {
    switch (TYPE_ID) {
        case TYPE_TEMP:
            return true;
        case TYPE_ACC:
            return true;
        case TYPE_EXT_TEMP1:
            return true;
        case TYPE_IR_TEMP:
            return true;
        case TYPE_EXT_TEMP2:
            return true;

        default:    //all other unsigned
            return false;
    }
}

//unsigned to with_sign
function bintodec(TYPE_ID, num) {
    if(TYPE_with_sign(TYPE_ID)){
        console.log("with_sign");
        if(1<<(TYPE_byte_amount(TYPE_ID)*8-1) & num){
            var move = 1 << TYPE_byte_amount(TYPE_ID)*8;
            num = - (move - num);
        }
    }else{
        console.log("unsigned");
    }
    return num;
}

function DecodeBkuPayload(data){
    var obj = new Object();
    for(i=0;i<data.length;i++){

        if (!Array.isArray(TYPE_byte_amount(data[i]))) {

            var j=1;
            while(obj[TYPE_Name_relation(data[i]) + j] !== undefined){
                j++;
            }

            var temp=0;
            for (k = 1; k <= TYPE_byte_amount(data[i]); k++)
            {
                temp=temp|(data[i+k]<<(TYPE_byte_amount(data[i])*8-8*(k)));
            }

            if(TYPE_with_sign(data[i])){
                if(1<<(TYPE_byte_amount(data[i])*8-1) & temp){
                    var move = 1 << TYPE_byte_amount(data[i])*8;
                    temp = - (move - temp);
                }
            }
            
            obj[TYPE_Name_relation(data[i]) + j] = temp / Math.pow(10, TYPE_decimal_places(data[i]));

            i += TYPE_byte_amount(data[i]);

        }else { /////////// is Array //////////////
            
            var j=1;
            while(obj[TYPE_Name_relation(data[i])[0] + j] !== undefined){
                j++;
            }
            obj[TYPE_Name_relation(data[i])[0] + j] = new Object();

            var ll=1;
            for (l = 1; ll <= TYPE_byte_amount(data[i])[0]; l++) {
                var temp=0;
                for (k = 1; k <= TYPE_byte_amount(data[i])[l]; k++){
                    temp=temp|(data[i+ll]<<(TYPE_byte_amount(data[i])[l]*8-8*(k)));
                    ll++;
                }

                if(TYPE_with_sign(data[i])){
                    if(1<<(TYPE_byte_amount(data[i])[l]*8-1) & temp){
                        var move = 1 << TYPE_byte_amount(data[i])[l]*8;
                        temp = - (move - temp);
                    }
                }

                obj[TYPE_Name_relation(data[i])[0]+j][TYPE_Name_relation(data[i])[l]] = temp / Math.pow(10, TYPE_decimal_places(data[i]));
            }
            i += TYPE_byte_amount(data[i])[0];
        }
    }
    return obj;
}

function Decoder(bytes, port) {
    return DecodeBkuPayload(bytes);
}

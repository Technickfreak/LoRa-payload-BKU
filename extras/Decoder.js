//var TYPE_TEMP           = 0x01;  //temperature;           3276.8°C --> 3276.7°C;
//Python-Marker#var {1} = {2};      //{3};      {8}
var TYPE_TEMP = 0x01;      //temperature;      -3276.8°C->3276.7°C
var TYPE_ACC = 0x03;      //["Acceleration","x","y","z"];      X,Y,Z -128->127 +/-63 1G


function TYPE_Name_relation(TYPE_ID) {
    switch (TYPE_ID) {
        //Python-Marker#\t\tcase {1}: \n\t\t\treturn {3};
		case TYPE_TEMP: 
			return temperature;
		case TYPE_ACC: 
			return ["Acceleration","x","y","z"];

        default:
            return 0;
    }

}
function TYPE_byte_amount(TYPE_ID) {
    switch (TYPE_ID) {
        //Python-Marker#\t\tcase {1}: \n\t\t\treturn {5};
		case TYPE_TEMP: 
			return ;
		case TYPE_ACC: 
			return [3,1,1,1];

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
        //Python-Marker#\t\tcase {1}: \n\t\t\treturn {6};
		case TYPE_TEMP: 
			return 1;
		case TYPE_ACC: 
			return 0;

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
        //Python-Marker#\t\tcase {1}: \n\t\t\treturn {7};
		case TYPE_TEMP: 
			return true;
		case TYPE_ACC: 
			return true;
        
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

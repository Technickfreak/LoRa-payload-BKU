//var TYPE_TEMP           = 0x01;  //temperature;           3276.8°C --> 3276.7°C;
//Python-Marker#var {1} = {2};      //{3};      {8}


function TYPE_Name_relation(TYPE_ID) {
    switch (TYPE_ID) {
        //Python-Marker#\t\tcase {1}: \n\t\t\treturn {3};

        default:
            return 0;
    }

}
function TYPE_byte_amount(TYPE_ID) {
    switch (TYPE_ID) {
        //Python-Marker#\t\tcase {1}: \n\t\t\treturn {5};

        default:
            return 0;
    }
}
function TYPE_decimal_places(TYPE_ID) {
    switch (TYPE_ID) {
        //Python-Marker#\t\tcase {1}: \n\t\t\treturn {6};

        default:    //all other 0 decimal_places
            return 0;
    }
}
function TYPE_with_sign(TYPE_ID) {
    switch (TYPE_ID) {
        //Python-Marker#\t\tcase {1}: \n\t\t\treturn {7};

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

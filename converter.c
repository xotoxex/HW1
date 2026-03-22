#include <stdio.h>
#include <stdlib.h>

//maps index value to hex. For example 10th index is A
char DecimalToHex(int value){
    //given value is considered as index
    char HexMap[] = "0123456789abcdef";
    return HexMap[value];
}

//does opposite operation. Uses property of char being integer value.
int HexToDecimal(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

//Prints ASCII values to the output file
void DecimalToASCII(char ***array , int size1 , int size2 , FILE *output){
    fprintf(output, "[*] ASCII Codes: ");
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {

            int high = HexToDecimal(array[i][j][0]); //first 4 bits
            int low  = HexToDecimal(array[i][j][1]); //latter 4 bits

            int value = (high << 4) | low; //bit shift operation to store 8 bits (1 byte)

            //checks if byte has ASCII representation
            if(value >= 32 && value <= 126){
                fprintf(output , "%c ", value);
            }
            else{
                fprintf(output , ". ");
            }

            
        }
    }
    fprintf(output , "\n");
}

//Prints Signed Character values to Output Files. Similar method to ASCII printing
void DecimalToSC(char ***array ,int size1 ,int size2 , FILE *output){
    fprintf(output , "[*] Signed Char: ");
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {

            int high = HexToDecimal(array[i][j][0]);
            int low  = HexToDecimal(array[i][j][1]);

            int value = (high << 4) | low;

            fprintf(output , "%d " , value);
            
        }
    }
    fprintf(output , "\n");
}

//Prints Unsigned Character values to Output Files. Similar method to ASCII and Signed Character printing
void DecimalToUC(char ***array ,int size1 ,int size2 , FILE *output){
    fprintf(output , "[*] Unsigned Char: ");
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {

            int high = HexToDecimal(array[i][j][0]);
            int low  = HexToDecimal(array[i][j][1]);

            int value = (high << 4) | low;

            fprintf(output , "%u " , value);
            
        }
    }
    fprintf(output , "\n");
}

//Prints Signed Integer values to Output Files.
void DecimalToS_INT(char ***array , int layer , FILE *output){
    fprintf(output , "[*] Signed Int: ");
    //traces through 64-bit chunks
    for (int i = 0; i < layer; i++){
        //groupping 64 bits into 32-bit chunks
        for(int j = 3; j < 8; j+=4){
            
            signed int value = 0;//storage of bits
            //considers every 8-bit in 32-bit chunk.8 bits are stored 4 times , resulting in 32 bit value. 
            for(int k = 0; k < 4; k++){
                //each hex is given to char, as holders of 4 bits
                char high = HexToDecimal(array[i][j-k][0]);
                char low = HexToDecimal(array[i][j-k][1]);
                value = (value << 4) | high; value = (value << 4) | low;//bit shift operation
            }
            fprintf(output , "%d " , value);
        }
    }
    fprintf(output , "\n");
}

//Prints Unsigned Integer values to Output Files. Similar Operation to printing Signed Integer.
void DecimalToU_INT(char ***array , int layer , FILE *output){
    fprintf(output , "[*] Unsigned Int: ");
    //traces through 64-bit chunks
    for (int i = 0; i < layer; i++){
        //groups into 32-bit chunks by skipping 4 indexes
        for(int j = 3; j < 8; j+=4){
            
            unsigned int value = 0; //storage of bits
            //considers every 8-bit in 32-bit chunk.8 bits are stored 4 times , resulting in 32 bit value.
            for(int k = 0; k < 4; k++){
                //each hex is given to char, as holders of 4 bits
                char high = HexToDecimal(array[i][j-k][0]);
                char low = HexToDecimal(array[i][j-k][1]);
                value = (value << 4) | high; value = (value << 4) | low;//bit shift operation
                }
            fprintf(output , "%u " , value);
        }
    }
    fprintf(output , "\n");
}

//Prints Signed Float values to Output Files. Same as Integer Printing , but converts integer holder to float holder. 
void DecimalToS_FLOAT(char ***array , int layer , FILE *output){
    fprintf(output , "[*] Signed Float: ");
    //traces through 64-bit chunks
    for (int i = 0; i < layer; i++){
        //groups into 32-bit chunks by skipping 4 indexes
        for(int j = 3; j < 8; j+=4){
            
            signed int value = 0;//storage for integer bits
            float fvalue; //storage for float bits
            
            //considers every 8-bit in 32-bit chunk.8 bits are stored 4 times , resulting in 32 bit value. 
            for(int k = 0; k < 4; k++){
                char high = HexToDecimal(array[i][j-k][0]);
                char low = HexToDecimal(array[i][j-k][1]);
                value = (value << 4) | high; value = (value << 4) | low;
                
                
                

            }
            fvalue = *(float *)&value; //copies bits of integer to float
            fprintf(output , "%.4f " , fvalue);
            
            
        }
        
    }
    fprintf(output , "\n");
}

//Prints Signed Double values to Output Files. Similar to printing Signed Float , but uses long long int.
void DecimalToS_DOUBLE(char ***array , int layer , FILE *output){
    fprintf(output , "[*] Signed Double: ");
    for (int i = 0; i < layer; i++){
        long long value = 0; //sizeof(long long int); #8 (64 bits)
        double df;
        //using all 64 bits. Going from high index to small ,as it is small endian.
        for (int j = 7; j >= 0 ; j--){
            char high = HexToDecimal(array[i][j][0]);
            char low = HexToDecimal(array[i][j][1]);
            value = (value << 4) | high; value = (value << 4) | low;//shifts 8 bits 8 times , resulting in storage of 64 bits
        }
        df = *(double *)&value; //copies bits of long long int to signed double
        fprintf(output , "%.4lf " , df);
    }
    fprintf(output , "\n");
}

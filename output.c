#include <stdio.h>
#include <stdlib.h>

//Stored for convenience
void Output(char ***array , int layer , FILE *output){
    DecimalToSC(array , layer , 8 , output);
    DecimalToASCII(array , layer , 8 , output);
    DecimalToUC(array , layer , 8 , output);
    DecimalToS_INT(array , layer , output);
    DecimalToU_INT(array , layer , output);
    DecimalToS_FLOAT(array , layer , output);
    DecimalToS_DOUBLE(array , layer , output);
}
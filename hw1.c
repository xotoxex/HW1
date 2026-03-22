#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hw1.h"

int main(void){
    
    int layer = 1; //initial size of memory
    
    // Creation of 3D array (Tensor) with dynamic layer size , row size of 8 and column size of 8.
    // Basically , dividing memory into 64 bit chunks.
    char ***chunks_of_64bits;
    chunks_of_64bits = CreateArr(chunks_of_64bits, layer , 8 , 8);

    FILE *file_pointer;
    file_pointer = fopen("input.txt" , "r"); //gets the pointer to the file location

    chunks_of_64bits = FileToArr(chunks_of_64bits , file_pointer , &layer);//fills array with data from file
    
    //Creation of Tensor , where previous Binary Tensor will be saved as hex values
    char ***chunks_of_16hex;
    chunks_of_16hex = CreateArr(chunks_of_16hex , layer , 8 , 2);//4 bits = 1 hex , so 8 bits = 2 hex
    
    //Filling Hex Tensor
    int value = 0;
    for(int i = 0; i < layer; i++){
        for(int j=0; j<8; j ++){
            for(int k=0; k<8; k+=4){ //skipping 4 indexes , as 4 bits = 1 hex
                value = 0;//holder of conversion form binary to decimal
                for(int a = 0; a<4; a++){ //4th loop to compensate skipping.
                    
                    //bit shifting to convert from array of bits to decimal
                    value = (value << 1) | (chunks_of_64bits[i][j][k+a] - '\0') - 48; 
                }
                chunks_of_16hex[i][j][k/4] = DecimalToHex(value);
                
            }
                
        }    
    }

    ChangeEndian(chunks_of_16hex , layer);//endian of Hex Tensor changed from Big Endian to Small Endian
    
    //pointer to output file is taken
    FILE *output;
    output = fopen("output.txt" , "w");

    //converting hex values to every data type and printing in the file
    Output(chunks_of_16hex , layer , output);
    
    //freeing memory in the heap and closing files
    FreeArr(chunks_of_64bits, layer , 8);
    FreeArr(chunks_of_16hex , layer , 8);
    fclose(output);
    fclose(file_pointer);  


}
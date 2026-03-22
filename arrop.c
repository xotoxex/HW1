#include <stdio.h>
#include <stdlib.h>

//creates dyanamic 3D array
char ***CreateArr(char ***array , int size1 , int size2 , int size3){
    //increases size of array in runtime , using malloc
    array = (char ***)malloc(size1 * sizeof(char **)); 
    // triple pointer means layer , double - row , single - column and without - the value
    for (int i = 0; i < size1; i++) {
        array[i] = (char **)malloc(size2 * sizeof(char *));
        for (int j = 0; j < size2; j++) {
            array[i][j] = (char *)malloc(size3 * sizeof(char));
        }
    }

    return array;
}

//frees dynamic memory in heap
void FreeArr(char ***array ,int size1 ,int size2){
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            free(array[i][j]);   //free columns
        }
        free(array[i]);          //free rows
    }
    free(array); //free layers
}

char ***FileToArr(char ***array , FILE *file_pointer , int *layer){
    
    int buffer_size = 64;//current size of memory
    int index = 0;//current number of elements in memory
    int ch;//placeholder of read data from file
    int i = 0; int j = 0; int k = 0; //indexes of 3D array

    //loop that places data from file into array
    while((ch = fgetc(file_pointer)) != EOF){ //reads character one by one until file is empty
        
        if (index >= buffer_size){
            (*layer)++; //increasing layer size of 3D array , adding additional chunk of 64 bit
            buffer_size += 64; 
                    
                    
            //updating size of array, using realloc
            char ***temp;
            temp = realloc(array , *layer * sizeof(char **));
            array= temp;

                    
            array[*layer-1] = malloc(8 * sizeof(char *));
            for (char x = 0; x < 8; x++){
                array[*layer-1][x] = malloc(8 * sizeof(char));
            }
        }
        
        if(ch == '\n'){continue;}//if read data is newline , it is skipped
        
            
        array[i][j][k] = ch;//conversion from ASCII to integer
        index++; 
        
        
        //increment of indexes without for loop
        k++;
        if(k == 8){
            k = 0;
            j++;
        }
        if(j == 8){
            j = 0;
            i++;
        }
                    
    }
    return array;
}

//traces through Tensor and prints every value. Used to debug and flag.
void PrintArr(char ***array , int size1 , int size2 , int size3){
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            for (int k = 0; k < size3; k++) {
                printf("%c ", array[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}


//swaps values on opposing indexes , changing endian of inner chunks (not chunk itself)
void ChangeEndian(char ***array , int layer) {
    for(int j = 0; j < layer; j++){

        for (int i = 0; i < 4; i++) {
            char *temp = array[j][i];
            array[j][i] = array[j][7 - i];
            array[j][7 - i] = temp;
        }
    }
    
}
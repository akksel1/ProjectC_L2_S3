//
// Created by Cyprien on 17/10/2022.
//

#include "fileUtils.h"

#define MAX_LINE_LENGTH 1024

//reads the txt file and returns a 2D array of chars
//each index of the array points to a string
//the file is loaded line by line in the array.
//also returns the size of the array
//we do not care about size of each line as we can use strlen or seek for \0
int readFile(char* fpath, char*** return_value, int* size){;
    FILE* file;
    file = fopen(fpath, "r");
    if (file == NULL){
        *(size) = 0;
        return 0;
    }
    int line_nbr = 0;
    char buffer[MAX_LINE_LENGTH];
    //we run through the file a first time to get the number of lines.
    while (!feof(file)){
        fgets(buffer, MAX_LINE_LENGTH, file);
        line_nbr ++;
    }
    //we reset pointer's position
    fseek(file, 0, SEEK_SET);
    char** storage = (char*) malloc(line_nbr*sizeof(char*));
    int index_count = 0;
    while (!feof(file)){
        fgets(buffer, MAX_LINE_LENGTH, file);
        int line_size = strlen(buffer);
        storage[index_count] = (char*)malloc(line_size*sizeof(char));
        strncpy(storage[index_count], buffer, line_size);
        index_count++;
    }
    fclose(file);
    *(size) = line_nbr;
    *(return_value) = storage;
    return 1;
}
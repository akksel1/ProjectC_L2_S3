//
// Created by Cyprien on 26/10/2022.
//

#include "stringUtils.h"

void findChar(char* string, char target, int** indexes, int* indexes_size){
    int str_size = strlen(string);
    int* tab = NULL;
    int nbr_occur = 0;
    for (int i = 0; i < str_size; i++){
        if (string[i] == target){
            nbr_occur ++;
        }
    }
    if (nbr_occur){
        tab = (int*)malloc(nbr_occur * sizeof(int));
        int count = 0;
        for (int e = 0; e < str_size; e++){
            if (string[e] == target){
                tab[count] = e;
                count++;
            }
        }
        *(indexes) = tab;
        *(indexes_size) = nbr_occur;
        return;
    }
    *(indexes) = tab;
    *(indexes_size) = nbr_occur;

}
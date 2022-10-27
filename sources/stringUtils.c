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

void splitStr(char* string, char separator, char*** split_tab, int* tab_size){
    int* sep_indexes;
    int sep_indexes_size;
    char** tab = NULL;
    int tab_s = 0;
    findChar(string, separator, &sep_indexes, &sep_indexes_size);
    if (!sep_indexes_size){
        *(split_tab) = tab;
        *(tab_size) = tab_s;
        return;
    }
    int str_size = strlen(string);
    tab_s = sep_indexes_size + 1;
    tab = (char*)malloc(tab_s * sizeof(char*));
    for (int i = 0; i < sep_indexes_size; i++){
        int chunk_size;
        if (i == 0 && i == sep_indexes_size-1){
            chunk_size = sep_indexes[i];
            int chunk2_size = str_size - sep_indexes[i];
            tab[i] = (char*)malloc(chunk_size);
            tab[i+1] = (char*)malloc(chunk2_size);
            strncpy(tab[i], string, chunk_size);
            strncpy(tab[i+1], string+sep_indexes[i]+1, chunk2_size);
            tab[i][chunk_size] = '\0';
            tab[i+1][chunk2_size] = '\0';
        }
        else {
            if (i == 0){
                chunk_size = sep_indexes[i];
                tab[i] = (char*)malloc(chunk_size);
                strncpy(tab[i], string, chunk_size);
                tab[i][chunk_size] = '\0';
            }
            else if (i == sep_indexes_size-1){
                chunk_size = sep_indexes[i] - sep_indexes[i-1];
                int chunk2_size = str_size - sep_indexes[i];
                tab[i] = (char*)malloc(chunk_size);
                tab[i+1] = (char*)malloc(chunk2_size);
                strncpy(tab[i], string+sep_indexes[i-1]+1, chunk_size-1);
                strncpy(tab[i+1], string+sep_indexes[i]+1, chunk2_size);
                tab[i][chunk_size] = '\0';
                tab[i+1][chunk2_size] = '\0';

            }
            else {
                chunk_size = sep_indexes[i] - sep_indexes[i-1]-1;
                tab[i] = (char*)malloc(chunk_size);
                strncpy(tab[i], string+sep_indexes[i-1]+1, chunk_size);
                tab[i][chunk_size] = '\0';
            }
        }
    }

    *(split_tab) = tab;
    *(tab_size) = tab_s;
}
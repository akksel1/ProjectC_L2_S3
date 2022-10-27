//
// Created by Cyprien on 26/10/2022.
//

#ifndef PROJET_C_STRINGUTILS_H
#define PROJET_C_STRINGUTILS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void findChar(char* string, char target, int** indexes, int* indexes_size);
void splitStr(char* string, char separator, char*** split_tab, int* tab_size);

#endif //PROJET_C_STRINGUTILS_H

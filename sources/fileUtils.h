//
// Created by Cyprien on 17/10/2022.
//

#ifndef PROJET_C_FILEUTILS_H
#define PROJET_C_FILEUTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int readFile(char* fpath, char*** return_value, int* size);

#endif //PROJET_C_FILEUTILS_H

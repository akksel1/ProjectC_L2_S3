//
// Created by Cyprien on 17/10/2022.
//

#ifndef PROJET_C_WORDS_H
#define PROJET_C_WORDS_H

#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int BOOL;
typedef struct word_node {
    char value;
    char* racine;
    BOOL masc;
    BOOL sing;
    struct word_node* tab;
    int nbelem;
} wnode, *pwnode;

typedef struct root{
    pwnode node;
};

#endif //PROJET_C_WORDS_H

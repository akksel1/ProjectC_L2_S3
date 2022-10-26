//
// Created by Cyprien on 17/10/2022.
//

#ifndef PROJET_C_WORDS_H
#define PROJET_C_WORDS_H

#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef int BOOL;

typedef struct s_word {
    int magic_nbr;
    char * value;
    int size;
}word, *p_word;

typedef struct s_node {
    char val;
    BOOL end;
    p_word derives;
    int d_size;
}node, *p_node;

typedef struct s_root{
    p_node node;
}root, *p_root;

#endif //PROJET_C_WORDS_H

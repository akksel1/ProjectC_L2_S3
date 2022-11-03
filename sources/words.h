//
// Created by Cyprien on 17/10/2022.
//

#ifndef PROJET_C_WORDS_H
#define PROJET_C_WORDS_H

#include <stdlib.h>
#include "stringUtils.h"

#define TRUE 1
#define FALSE 0
typedef int BOOL;

typedef struct s_dict_line {
    char* word;
    char* root;
    char* details;
}dict_line, *p_dict_line;

typedef struct s_word {
    int magic_nbr;
    char* value;
    int size;
}word, *p_word;

typedef struct s_node {
    char val;
    BOOL end;
    p_word derives;
    int d_size;
    struct s_node** next[26];
    int n_size;
}node, *p_node;

typedef struct s_root{
    p_node node;
}root, *p_root;

p_dict_line buildDictLine(char* line);

#endif //PROJET_C_WORDS_H

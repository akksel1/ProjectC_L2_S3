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
    char* magic_nbr;
    char* value;
}word, *p_word;


struct s_cell
{
    p_word derive;
    struct s_cell *next;
};

typedef struct s_cell cell, *p_cell;

typedef struct s_list
{
    p_cell head;
    int size;
} t_list, *p_list;

//here
typedef struct s_node {
    char val;
    BOOL end;
    p_list derives;
    struct s_node* next[26];
}node, *p_node;

typedef struct s_root{
    p_node node;
}root, *p_root;


p_dict_line buildDictLine(char* line);
p_node CreateEmptyNode();
p_cell CreateEmptyCell();
p_list CreateEmptyList();
p_node CreateNode(char);
p_cell CreateCell(char*);
int which_index(char);
int which_type(char*);
int which_tree_root(p_root,char*);
char* GenerateMagicNumber(char*, int);
p_node findword(p_dict_line,p_root,int);
void findword_print(p_dict_line,p_root);
p_node createword(p_dict_line,p_node);
void fillMNb(p_dict_line, int,p_node);
p_root* addword(p_root*,p_dict_line,int);

#endif //PROJET_C_WORDS_H

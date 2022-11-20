//
// Created by Cyprien on 03/11/2022.
//

#ifndef PROJET_C_TREEUTILS_H
#define PROJET_C_TREEUTILS_H

#include "words.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>

p_root createEmptyTree();
//creation of the general tree
p_node setupsubTree(char);
p_root setupTree();
void fillTree(p_root*,p_dict_line*,int,int);
char* findwordoftype(p_root,int);
void sentence1(p_root);
void sentence2(p_root);
#endif //PROJET_C_TREEUTILS_H

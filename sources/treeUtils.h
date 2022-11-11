//
// Created by Cyprien on 03/11/2022.
//

#ifndef PROJET_C_TREEUTILS_H
#define PROJET_C_TREEUTILS_H

#include "words.h"

typedef struct s_root{
    p_node node;
}root, *p_root;

root createEmptyTree();

p_node setupsubTree(char*);
root setupTree(root);

#endif //PROJET_C_TREEUTILS_H

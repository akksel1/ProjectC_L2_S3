//
// Created by Cyprien on 17/10/2022.
//

#include "words.h"
#include <string.h>

p_dict_line buildDictLine(char* line){
    int tabSize;
    char** tab;
    splitStr(line, '\t', &tab, &tabSize);
    if (tabSize == 3){
        p_dict_line dline = (p_dict_line)malloc(sizeof(dict_line));
        dline->word = tab[0];
        dline->root = tab[1];
        dline->details = tab[2];
        return dline;
    }
    else {
        return NULL;
    }
}


// create an empty node with no character as a value which is not the end of a word, no letters after and no derive
p_node CreateEmptyNode(){
    p_node p;
    p->val="";
    p->end=0;
    memset(p->next,0,26);
    p->derives=NULL;
    return p;
}

//
// Created by Cyprien on 17/10/2022.
//

#include "words.h"

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

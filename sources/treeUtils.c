//
// Created by Cyprien on 03/11/2022.
//

#include "treeUtils.h"

root createEmptyTree()
{
    root t;
    t.node = NULL;
    return t;
}

p_node setupsubTree(char* type){
    p_node p;
    p=CreateEmptyNode();
    p->val=type;
    return p;
}

root setupTree(root t){
    p_node hub,verbe,nom,adjectif,adverbe;
    hub=setupsubTree("hub");
    verbe=setupsubTree("verbe");
    nom=setupsubTree("nom");
    adjectif=setupsubTree("adjectif");
    adverbe=setupsubTree("adverbe");
    hub->next[0]=&verbe;
    hub->next[1]=&nom;
    hub->next[2]=&adjectif;
    hub->next[3]=&adverbe;
    t.node=hub;
    return t;
}
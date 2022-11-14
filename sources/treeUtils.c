//
// Created by Cyprien on 03/11/2022.
//

#include "treeUtils.h"

p_root createEmptyTree()
{
    p_root t;
    t = (p_root) malloc(sizeof(root));
    t->node = CreateEmptyNode();
    return t;
}
// create each tree
p_node setupsubTree(char type){
    p_node p;
    p=CreateEmptyNode();
    p->val=type;
    return p;
}
// set up general
p_root setupTree(){
    p_root tree;
    tree = createEmptyTree();
    p_node hub,verbe,nom,adjectif,adverbe;
    hub=setupsubTree('h');
    verbe=setupsubTree('v');
    nom=setupsubTree('n');
    adjectif=setupsubTree('a');
    adverbe=setupsubTree('A');
    hub->next[0]=verbe;
    hub->next[1]=nom;
    hub->next[2]=adjectif;
    hub->next[3]=adverbe;
    tree->node=hub;
    return tree;
}
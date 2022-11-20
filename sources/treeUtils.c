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

//Fill the tree with n random words from the dictionary
//n should be < size when you call fillTree in main
void fillTree(p_root* my_tree,p_dict_line* my_dico,int n,int size)
{
    int random_line,cpt=0;
    time_t t;
    srand( (unsigned) time (&t));
    for(int i=0;i<n;i++) {
        //Pick a random line from the dict
        random_line=rand()%size;
        printf("We added: %s %d\n",my_dico[random_line]->root, which_type(my_dico[random_line]->details));
        //Add this word to the right subtree
        addword(my_tree, my_dico[random_line], which_type(my_dico[random_line]->details));
    }
}
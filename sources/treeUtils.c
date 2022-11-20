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

char* findwordoftype(p_root my_tree,int type){
    time_t t;
    srand( (unsigned) time (&t));
    p_node subtree = my_tree->node->next[type];
    p_node temp = subtree; //temp ptr to cross the subtree
    char* word;
    word=(char*) malloc(sizeof(char)*25);
    int n;
    int nextexist=1,foundword=0; //boolean to check the different cases
    while (foundword==0){ //as long as we did not take a word
        //if we start again we have to reset some variables
        temp=subtree;
        int k=0;
        word="";
        while(nextexist==1){ //as long as we still have possibilities for the next letter
            if (temp->derives!=NULL){
                foundword=rand()%2; //if this is the end of a word then 50% chance of taking it
            }
            if (foundword==0){
                word[k]=temp->val;
                n=0;
                for (int i=0;i<26;i++){
                    if(temp->next[i]!=NULL){ // find the number of possible letters
                        n++;
                    }
                }
                if (n==0){
                    nextexist=0; //check if there are any
                }
                else{
                    int* tab=(int*) malloc(sizeof(int)*n);
                    n=0;
                    for (int i=0;i<26;i++){
                        if(temp->next[i]!=NULL){
                            tab[n]=i;
                            n++; //fill the tab of possible next letters
                        }
                    }
                    int nextl;
                    nextl=rand()%n;//choose one
                    temp=temp->next[nextl];//and go to the next letter
                }
            }
            else{
                nextexist=0; //if we have a word we need to get out of the loop
            }
            nextexist=0;//to delete

        }
        foundword=1;//to delete

    }

    return word;
}


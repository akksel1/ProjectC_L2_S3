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
p_root fillTree(p_root* my_tree,p_dict_line* my_dico,int n,int size)
{
    int random_line,cpt=0;
    time_t t;
    srand( (unsigned) time (&t));
    for(int i=0;i<n;i++) {
        //Pick a random line from the dict
        random_line=rand()%size;
        printf("We added: %s %d\n",my_dico[random_line]->root, which_type(my_dico[random_line]->details));
        //Add this word to the right subtree
        my_tree = addword(my_tree, my_dico[random_line], which_type(my_dico[random_line]->details));
    }
    return (*my_tree);
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
    while (foundword!=1){ //as long as we did not take a word
        //if we start again we have to reset some variables
        temp=subtree;
        int k=0;
        nextexist=1;
        while(nextexist==1){ //as long as we still have possibilities for the next letter
            if (temp->derives->head!=NULL){
                if (k<6){
                    foundword=rand()%(7-k); //the longer the word the higher the chance to take it
                }
                else{
                    foundword=rand()%2;//if this is the end of a word longer than 5 letters then 50% chance of taking it
                }

            }
            if (foundword!=1){
                if (k!=0){
                    word[k-1]=temp->val;
                }

                n=0;
                for (int i=0;i<26;i++){
                    if(temp->next[i]!=NULL){ // find the number of possible letters
                        n++;
                    }
                }
                if (n==0){
                    nextexist=0; //check if there are any
                    foundword=1; // if we r at the end of the tree then it's a word
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
                    temp=temp->next[tab[nextl]];//and go to the next letter
                    k++;
                }
            }
            else{
                nextexist=0; //if we have a word we need to get out of the loop
            }
        }
    }
    return word;
}

void sentence1(p_root my_tree){//nom – adjectif – verbe – nom
    char* noun = findwordoftype(my_tree,1);
    sleep(1); //to reset seed for randomness because it uses time.
    char* adj = findwordoftype(my_tree,2);
    char* verb = findwordoftype(my_tree,0);
    char* noun2 = findwordoftype(my_tree,1);
    printf("Un %s %s %s un %s",noun, adj, verb, noun2);
}
void sentence2(p_root my_tree){//nom – ‘qui’ – verbe – verbe – nom – adjectif
    char* noun = findwordoftype(my_tree,1);
    char* verb = findwordoftype(my_tree,0);
    sleep(1); //to reset seed for randomness because it uses time.
    char* verb2 = findwordoftype(my_tree,0);
    char* noun2 = findwordoftype(my_tree,1);
    char* adj = findwordoftype(my_tree,2);
    printf("Un %s qui %s %s un %s %s",noun, verb, verb2, noun2, adj);

}

void sentence3(p_root my_tree){//nom - adjectif - verbe '-t-il' adverbe
    char* noun = findwordoftype(my_tree,1);
    char* adj = findwordoftype(my_tree,2);
    char* verb = findwordoftype(my_tree,0);
    char* adv = findwordoftype(my_tree,3);
    printf("%s %s %s-t-il %s ?",noun, adj, verb, adv);
}
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
    printf("1\n");
    while (foundword!=1){ //as long as we did not take a word
        //if we start again we have to reset some variables
        temp=subtree;
        int k=0;
        //word="";
        printf("2\n");
        nextexist=1;
        while(nextexist==1){ //as long as we still have possibilities for the next letter
            printf("3\n");
            if (temp==NULL){
                printf("et bah si\n");
            }
            if (temp->derives->head!=NULL){
                printf("4\n");
                if (k<6){
                    printf("5\n");
                    foundword=rand()%(7-k); //the longer the word the higher the chance to take it
                    printf("6\n");
                }
                else{
                    foundword=rand()%2;//if this is the end of a word longer than 5 letters then 50% chance of taking it
                    printf("7\n");
                }

            }
            if (foundword!=1){
                printf("8\n");
                if (k!=0){
                    printf("value : %c and k= %d\n",temp->val,k);
                    word[k-1]=temp->val;
                    printf(" word : %s\n",word);
                }

                n=0;
                printf("8.5\n");
                for (int i=0;i<26;i++){
                    printf("9\n");
                    if(temp->next[i]!=NULL){ // find the number of possible letters
                        n++;
                        printf("10\n");
                    }
                    printf(" size of tab is %d\n",n);
                }
                if (n==0){
                    printf("11\n");
                    nextexist=0; //check if there are any
                    foundword=1; // if we r at the end of the tree then it's a word
                }
                else{
                    printf("12\n");
                    int* tab=(int*) malloc(sizeof(int)*n);
                    n=0;
                    for (int i=0;i<26;i++){
                        printf("13\n");
                        if(temp->next[i]!=NULL){
                            printf("14\n");
                            printf("index= %d\n",i);
                            tab[n]=i;
                            n++; //fill the tab of possible next letters
                        }
                    }
                    printf("15\n");
                    int nextl;
                    nextl=rand()%n;//choose one
                    temp=temp->next[tab[nextl]];//and go to the next letter
                    k++;
                }
                printf("16\n");
            }
            else{
                printf("17\n");
                nextexist=0; //if we have a word we need to get out of the loop
            }
            //nextexist=0;//to delete
            printf("18\n");
        }
        //foundword=1;//to delete
        printf("19\n");
    }
    printf("20\n");
    return word;
}

void sentence1(p_root my_tree){//nom – adjectif – verbe – nom
    printf("Un %s %s %s un %s",findwordoftype(my_tree,1),findwordoftype(my_tree,2),findwordoftype(my_tree,0),findwordoftype(my_tree,1));
}
void sentence2(p_root my_tree){//nom – ‘qui’ – verbe – verbe – nom – adjectif
    printf("Un %s qui %s %s un %s %s",findwordoftype(my_tree,1),findwordoftype(my_tree,0),findwordoftype(my_tree,0),findwordoftype(my_tree,1),findwordoftype(my_tree,2));

}
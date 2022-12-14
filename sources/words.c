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

p_cell CreateEmptyCell(){
    p_cell my_cell = (p_cell) malloc(sizeof(cell));
    my_cell->derive = (p_word) malloc(sizeof(word));
    my_cell->next=NULL;
    return my_cell;
}

p_list CreateEmptyList(){
    p_list my_list=(p_list)malloc(sizeof(t_list));
    my_list->head = NULL;
    return my_list;
}

// create an empty node with no character as a value which is not the end of a word, no letters after and no derive be careful
p_node CreateEmptyNode(){
    p_node p;
    p = (p_node) malloc(sizeof(node));
    p->val='0';
    p->end=0;
    //memset(p->next,0,26);
    for(int i=0;i<26;i++)
    {
        p->next[i]=NULL;
    }
    p->derives=CreateEmptyList();
    return p;
}

//Function which assigns val to a node
p_node CreateNode(char val)
{
    p_node p = CreateEmptyNode();
    p->val=val;
    return p;
}



//Function which assigns val to a cell
p_cell CreateCell(char* my_str)
{
    p_cell p=CreateEmptyCell();
    p->derive->value = my_str;
    p->next=NULL;
    return p;
}


//Function which returns the index of a letter in the alphabet using ASCII code
int which_index(char my_letter)
{
    if(my_letter>96 && my_letter<123){
        return my_letter-97;
    }
    else {
        return -1;
    }
}

//Function which returns the type number of a word
int which_type(char* derive_type)
{
    char* type = malloc(sizeof(char)*3);
    strncpy(type,derive_type,3);
    if(strcmp(type,"Ver")==0)
    {
        return 0;
    }
    if(strcmp(type,"Nom")==0)
    {
        return 1;
    }
    if(strcmp(type,"Adj")==0)
    {
        return 2;
    }
    if(strcmp(type,"Adv")==0)
    {
        return 3;
    }
    return -1;
    free(type);
}

int which_tree_root(p_root my_tree,char* my_str)
{
    int bool = 0;
    p_node result;
    int type=0;
    p_dict_line word=(p_dict_line)malloc(sizeof(dict_line));
    word->root = my_str;

    while(bool==0 && type<3)
    {
        result=findword(word,my_tree,type);
        if(result==NULL)
        {
            bool=0;
        }
        else
        {
            bool = 1;
        }
        type++;
    }

    if(bool == 0)
    {
        return -1; // Not found
    }
    return type-1;
}


//Function which generates the magic nb
char* GenerateMagicNumber(char* derive_type, int type)
{
    char type_str=type+48;
    char* MagicNumber = (char*) malloc(sizeof(char)*4);
    MagicNumber[0]=type_str;
    switch(type)
    {
        case 0:
        {
            //verbs is a tense is not implemented yet tense =-1
            int i;
            char* tense,*pers,*nb;
            tense = (char*)malloc(sizeof(char)*7);
            pers = (char*)malloc(sizeof(char)*7);
            nb = (char*)malloc(sizeof(char)*7);

            //We extract the relevant infos from details
            i=0;
            while(derive_type[i]!='+')
            {
                tense[i] = derive_type[i];
                i++;
            }
            i++;
            int j=0;
            while(derive_type[i]!='+')
            {
                nb[j] = derive_type[i];
                i++;
                j++;
            }
            i++;
            int n=0;
            while(n<2)
            {
                pers[n] = derive_type[i];
                i++;
                n++;
            }

            if(strcmp(tense,"IPre")==0)
            {
                MagicNumber[1]='0';
            }
            else{
                if(strcmp(tense,"IImp")==0)
                {
                    MagicNumber[1]='1';
                }
                else{
                    if(strcmp(tense,"SPre")==0)
                    {
                        MagicNumber[1]='2';
                    }
                    else{
                        MagicNumber[1]='9';
                    }
                }

            }
            if(strcmp(nb,"SG")==0)
            {
                MagicNumber[2]='0';
            }
            if(strcmp(nb,"PL")==0)
            {
                MagicNumber[2]='1';
            }
            if(strcmp(pers,"P1")==0)
            {
                MagicNumber[3]='0';
            }
            if(strcmp(pers,"P2")==0)
            {
                MagicNumber[3]='1';
            }
            if(strcmp(pers,"P3")==0)
            {
                MagicNumber[3]='2';
            }
            break;
        }
        case 1:
        {
            int i;
            char*gender,*nb;
            gender = (char*)malloc(sizeof(char)*7);
            nb = (char*)malloc(sizeof(char)*7);

            //We extract the relevant infos from details
            i=0;
            while(derive_type[i]!='+')
            {
                gender[i] = derive_type[i];
                i++;
            }
            i++; //to avoid the +
            int n=0;
            while(n<2)
            {
                nb[n] = derive_type[i];
                i++;
                n++;
            }
            if(strcmp(gender,"Mas")==0)
            {
                MagicNumber[1]='0';
            }
            if(strcmp(gender,"Fem")==0)
            {
                MagicNumber[1]='1';
            }
            if(strcmp(gender,"InvGen")==0)
            {
                MagicNumber[1]='2';
            }
            if(strcmp(nb,"SG")==0)
            {
                MagicNumber[2]='0';
            }
            if(strcmp(nb,"PL")==0)
            {
                MagicNumber[2]='1';
            }
            break;
        }
        case 2:
        {
            int i;
            char*gender,*nb;
            gender = (char*)malloc(sizeof(char)*7);
            nb = (char*)malloc(sizeof(char)*7);

            //We extract the relevant infos from details
            i=0;
            while(derive_type[i]!='+')
            {
                gender[i] = derive_type[i];
                i++;
            }
            i++;
            int n=0;
            while(n<2)
            {
                nb[n] = derive_type[i];
                i++;
                n++;
            }
            if(strcmp(gender,"Mas")==0)
            {
                MagicNumber[1]='0';
            }
            if(strcmp(gender,"Fem")==0)
            {
                MagicNumber[1]='1';
            }
            if(strcmp(gender,"InvGen")==0)
            {
                MagicNumber[1]='2';
            }
            if(strcmp(nb,"SG")==0)
            {
                MagicNumber[2]='0';
            }
            if(strcmp(nb,"PL")==0)
            {
                MagicNumber[2]='1';
            }
            break;
        }
        case 3:
        {
            break;
        }
        default: printf("error GenerateMagicNumber - wrong type");
    }
    return MagicNumber;
}

p_node findword(p_dict_line my_word,p_root my_tree,int type){
    p_node subtree = my_tree->node->next[type];
    p_node temp = subtree; //temp ptr to cross the subtree
    char my_letter;
    //Loop to cross the subtree & add nodes
    for(int i=0;i<strlen(my_word->root);i++)
    {
        my_letter = my_word->root[i];
        if (temp->next[which_index(my_letter)] == NULL){
            return NULL;
        }
        temp = temp->next[which_index(my_letter)];
    }

    if(temp->derives->head!=NULL){
        return temp;
    }
    printf("%c %p",temp->val,temp->derives->head);
    return NULL;
}

void findword_print(p_dict_line my_word,p_root my_tree){
    int type;
    type = which_tree_root(my_tree,my_word->root);
    printf("type:%d\n",type);
    if(type!=-1){
    p_node subtree = my_tree->node->next[type];
    p_node temp = subtree; //temp ptr to cross the subtree
    char my_letter,temp_char;
    //Loop to cross the subtree & add nodes
    for(int i=0;i<=strlen(my_word->root);i++)
    {
        my_letter = my_word->root[i];
        if(i==0){
            switch(type){
                case 0:{
                    printf("TYPE: VERB\n");
                    break;
                }
                case 1:{
                    printf("TYPE: NOUN\n");
                    break;
                }
                case 2:{
                    printf("TYPE: ADJECTIVE\n");
                    break;
                }
                case 3:{
                    printf("TYPE: ADVERB\n");
                    break;
                }
                default:printf("KK");
            }
        }
        else{
            printf("Letter: %c\n",temp->val);
        }


        printf("| ");
        for(int j=0;j<26;j++)
        {
            if(temp->next[j]==NULL){
                printf("0 |");
            }
            else{
                printf("%c |",temp->next[j]->val);
            }
        }
        printf("\n\n");
        //sleep(1);
        if(i<strlen(my_word->root)){
            temp = temp->next[which_index(my_letter)];
        }
    }
    }
    else{
        printf("\n %s not found",my_word->root);
    }
}

p_node createword(p_dict_line my_word,p_node temp){
    p_node result;
    char my_letter;
    int temp2;
    //Loop to cross the subtree & add nodes
    for(int i=0;i<strlen(my_word->root);i++) {
        my_letter = my_word->root[i];
        temp2 = which_index(my_letter);
        if (temp2 != -1) {
            if (temp == NULL || (temp->next[which_index(my_letter)] == NULL)) {
                result = CreateNode(my_letter);
                temp->next[which_index(my_letter)] = result;
            }

            if (i < strlen(my_word->root)) //de base il y avait -1
                temp = temp->next[which_index(my_letter)];
        }
    }
    return temp;
}

void fillMNb(p_dict_line my_word, int type,p_node temp){
    p_cell temp1, temp2; //temp ptrs to cross the derivation list
    char *MagicNb;
    int tabSize,n;
    char **details_tab;
    int bool=n=0;
    //Creation of the array of details
    splitStr(my_word->details, ':', &details_tab, &tabSize);

    // If tabSize =O => it means it's an adv
    if (tabSize == 0) {
        details_tab = (char**)malloc(sizeof(char*)*2);
        details_tab[0] = "Adv";
    }

    // Is '+' in the details ?
    if(type!=3){
        while (bool != 1 && n < strlen((my_word->details))) {
            if (my_word->details[n] == '+') {
                bool = 1;
            }
            n++;
        }
    }

    if (bool == 1 || type == 3) {
        for (int i = 1; i < tabSize; i++) {
            MagicNb = GenerateMagicNumber(details_tab[i], type);
            //Is my derivation list empty ?
            if (temp->derives->head == NULL) {
                temp->derives->head = CreateCell(my_word->word);
                temp->derives->head->derive->magic_nbr = MagicNb;
            }
                // If not: is the derivation already in the list ?
            else {
                bool = 0;
                //Is the derivation already in the list ?
                temp1 = temp->derives->head;
                while (temp1->next != NULL && bool != 1) {
                    if (MagicNb == temp1->derive->magic_nbr) {
                        bool = 1;
                    }
                    temp1 = temp1->next;
                }
                //Add the derivation to the list if not exist
                if (bool != 1) {
                    temp2 = CreateCell(my_word->word);
                    temp2->derive->magic_nbr = MagicNb;
                    temp1->next = temp2;
                }
            }
        }
    }
    free(details_tab);
}
/*Function which add n words to a subtree
 * n: nb words in dict (-1 for all)
 * type: 0 verb , 1 noun , 2 adj , 3 adv , -1 any type
*/
p_root* addword(p_root* my_tree,p_dict_line my_word, int type)
{
    switch(type){
        case 0:
        {
            p_node subtree = (*my_tree)->node->next[0];
            p_node temp = subtree; //temp ptr to cross the subtree
            temp = createword(my_word,temp);
            fillMNb(my_word, type, temp);
            break;
        }
        case 1:
        {
            p_node subtree = (*my_tree)->node->next[1];
            p_node temp = subtree; //temp ptr to cross the subtree
            temp = createword(my_word,temp);
            fillMNb(my_word, type, temp);
            free(temp);
            break;
        }
        case 2:
        {
            p_node subtree = (*my_tree)->node->next[2];
            p_node temp = subtree; //temp ptr to cross the subtree
            temp = createword(my_word,temp);
            fillMNb(my_word, type, temp);
            break;
        }
        case 3:
        {
            p_node subtree = (*my_tree)->node->next[3];
            p_node temp = subtree; //temp ptr to cross the subtree
            temp = createword(my_word,temp);
            fillMNb(my_word, type, temp);
            break;
        }
        case -1:
        {
            break;
        }
        default: printf("error addword - unknown type");
    }
    return my_tree;
}
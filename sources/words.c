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


// create an empty node with no character as a value which is not the end of a word, no letters after and no derive be careful
p_node CreateEmptyNode(){
    p_node p;
    p->val="";
    p->end=0;
    memset(p->next,0,26);
    p->derives=NULL;
    return p;
}

//Function which assigns val to a node
p_node CreateNode(char val)
{
    p_node p = CreateEmptyNode();
    p->val=&val;
    return p;
}

//Function which assigns val to a cell
p_cell CreateCell(char* my_str)
{
    p_cell p;
    p->derive->value = my_str;
    p->next=NULL;
    return p;
}

//Function which returns the index of a letter in the alphabet using ASCII code
int which_index(char my_letter)
{
    if(my_letter>96 && my_letter<123)
    return my_letter % 26;

    else printf("error - unknown letter");
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
}

//Function which generates the magic nb
char GenerateMagicNumber(char* derive_type, int type)
{
    char type_str=type+48;
    char* MagicNumber = (char*) malloc(sizeof(char)*4);
    MagicNumber[0]=type_str;
    switch(type)
    {
        case 0:
        {

            break;
        }
        case 1:
        {
            char* gender = malloc(sizeof(char)*3);
            strncpy(gender,derive_type+4,2);
            if(strcmp(gender,"Mas")==0)
            {
                MagicNumber[1]='0';
            }
            if(strcmp(gender,"Fem")==0)
            {
                MagicNumber[1]='1';
            }

            char* nb = malloc(sizeof(char)*3);
            strncpy(nb,derive_type+8,2);
            if(strcmp(nb,"SG")==0)
            {
                MagicNumber[1]='0';
            }
            if(strcmp(nb,"PL")==0)
            {
                MagicNumber[1]='1';
            }
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
            break;
        }
        default: printf("error GenerateMagicNumber - wrong type");
    }
    return *MagicNumber;
}


/*Function which add n words to a subtree
 * n: nb words in dict (-1 for all)
 * type: 0 verb , 1 noun , 2 adj , 3 adv , -1 any type
*/
void addword(p_root my_tree,p_dict_line my_word,int n, int type)
{
    switch(type){
        case 0:
        {
            break;
        }
        case 1:
        {
            p_node* subtree = my_tree->node->next[1];
            p_node* temp = subtree; //temp ptr to cross the subtree
            p_cell temp1,temp2; //temp ptrs to cross the derivation list
            p_node result;
            char my_letter;
            int bool=0;

            //Loop to cross the subtree & add nodes
            for(int i=0;i<strlen(my_word->root);i++)
            {
                my_letter = my_word->root[i];
                if(temp==NULL ||((*temp)->next[which_index(my_letter)] == NULL) )
                {
                    result = CreateNode(my_letter);
                    (*temp)->next[which_index(my_letter)] = &result;
                }

                if(i<strlen(my_word->root)-1)
                temp = (*temp)->next[which_index(my_letter)];
            }

            temp1 = (*temp)->derives->head;
            if(temp1==NULL)
            {
                temp1 = CreateCell(my_word->word);
                temp1->derive->magic_nbr= GenerateMagicNumber(my_word->details,type);
            }

            bool=0;
            //Is the derivation already in the list ?
            while(temp1->next!=NULL && bool!=1)
            {
                if(my_word->word == temp1->derive->value)
                {
                    bool=1;
                }
                temp1=temp1->next;
            }
            //Add the derivation to the list if not exist
            if(bool!=1)
            {
                temp2 = CreateCell(my_word->word);
                temp2->derive->magic_nbr= GenerateMagicNumber(my_word->details,type);
                temp1->next = temp2;
                free(temp2);
            }
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
            break;
        }
        case -1:
        {
            break;
        }
        default: printf("error addword - unknown type");
    }
}
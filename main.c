#include <stdio.h>
#include "sources/words.h"
#include "sources/treeUtils.h"
#include "sources/fileUtils.h"
#include "sources/stringUtils.h"
#include <unistd.h>



char* generate_dict_abs_path(char* relative_path){
    char abs_path[256];
    getcwd(abs_path, 256);
    int s2 = strlen(relative_path);

    //project in clion usually builds an exe in a path like this project_folder/cmake-build-debug/project.exe
    //we want to cut this path to get the project folder absolute path and then append the relative path
    //of the dict. Doing so, wherever our exe is on our computer, it will find the dict. It also
    //works on every computer as it only need the dict relative path according to the project folder.

    int* indexes;
    int size_indexes;
    findChar(abs_path, '\\', &indexes, &size_indexes);
    int sl_index = indexes[size_indexes-1] + 1;
    // we get index of last \ but we don't want to delete it

    //getcwd will return the current working directory so, on build it will return something like
    //project_folder/cmake-build-debug
    //then we search for the first / or \ index to cut the path

    int final_size = sl_index + s2 + 1;
    char* final_path = (char*)malloc(final_size);
    strncpy(final_path, abs_path, sl_index);
    final_path[sl_index] = "\0";
    strcat(final_path, relative_path);
    final_path[final_size-1] = "\0";

    free(indexes);
    return final_path;


}

p_dict_line* parseLines(int* tabsize){
    char* fpath = generate_dict_abs_path("/sources/dico.txt");
    char** lines;
    int size;
    *(tabsize) = 0;
    int result = readFile(fpath, &lines, &size);
    printf("There are %d lines in the dict \n", size);
    if (result) {
        p_dict_line* tab = malloc(sizeof(p_dict_line)*size);
        for (int i = 0; i < size; i++){
            char* line = lines[i];
            p_dict_line dictLine = buildDictLine(line);
            if (dictLine){
                tab[*(tabsize)] = dictLine;
                *(tabsize)+=1;
            }
            else{
                //printf("Failed line %d :\n", i);
                //printf("%s\n", lines[i]);
            }
        }
        return tab;
    }
    else{
        return NULL;
    }
}

int main() {
    int size,nb;
    char* word;
    word = (char*) malloc(sizeof(char)*25);
    p_root my_tree=createEmptyTree();
    my_tree = setupTree();
    p_dict_line* parsedDict = parseLines(&size);
    p_dict_line my_word = (p_dict_line) malloc(sizeof(dict_line));
    int choice,type;
    int stop =0;
    int middle_line;

    while(stop==0) {
        printf("\n\n\t-- MAIN MENU --\n\n1 - Extract a word from the dictionary\n2 - Add a word to the tree\n3 - Add words from the dictionary\n4 - Display a word\n5- Generate a sentence\n6- Quit\nEnter:"
        );
        scanf("%d",&choice);
        while(choice>6||choice<1)
        {
            printf("Error\nRe-enter:");
            scanf("%d",&choice);
        }
        switch (choice) {
            case (1): {
                printf("%d lines parsed. \n", size);
                printf("Give a number <%d:",size);
                scanf("%d",&middle_line);
                if(middle_line>size)
                {

                }
                printf("Line %d is :\n", middle_line);
                printf("-Root : %s\n-Word : %s\n-Details : %s\n", parsedDict[middle_line]->root,
                       parsedDict[middle_line]->word, parsedDict[middle_line]->details);
                sleep(2);
                break;
            }
            case (2): {
                printf("Give a number < %d:",size);
                scanf("%d",&middle_line);
                printf("-Root : %s\n-Word : %s\n-Details : %s\n", parsedDict[middle_line]->root,parsedDict[middle_line]->word, parsedDict[middle_line]->details);
                addword(&my_tree, parsedDict[middle_line], which_type(parsedDict[middle_line]->details));
                findword_print(parsedDict[middle_line], my_tree, which_type(parsedDict[middle_line]->details));

                sleep(2);
                break;
            }
            case(3):
            {
                printf("\nHow many words do you want to add ?(Max: %d)\nEnter:",5000);
                scanf("%d",&nb);
                while(nb>5000||nb<1)
                {
                    printf("Error\nRe-enter:");
                    scanf("%d",&nb);
                }
                fillTree(&my_tree,parsedDict,nb,size);
                break;
            }
            case(4):
            {
                printf("Saisir le mot que vous souhaitez affficher:");
                scanf("%s",word);
                scanf("%d",&type);
                my_word->root=word;
                printf("type: %d\n",type);
                findword_print(my_word,my_tree,type);
                break;
            }
            case(5):
            {
                printf("\n1 - Sentence type 1 (nom  adjectif  verbe  nom)\n2 - Sentence type 2 (nom \"qui\" verbe verbe nom adjectif)\n3 - Sentence type 3 (nom  adjectif  verbe \" t il\" adverbe ?)\n4: Go back\nEnter:");
                scanf("%d",&choice);
                while(choice>3||choice<1)
                {
                    printf("Error\nRe-enter:");
                    scanf("%d",&choice);
                }
                switch(choice)
                {
                    case 1:
                    {
                        sentence1(my_tree);
                        break;
                    }
                    case 2:
                    {
                        sentence2(my_tree);
                        break;
                    }
                    case 3:
                    {
                        sentence3(my_tree);
                        break;
                    }
                    case 4:
                    {
                        break;
                    }
                    default:printf("Error");
                }

                break;
            }
            case(6):
            {
                stop=1;
                break;
            }
            default:
                printf("Erreur");
        }

    }
    free(parsedDict);
    return 0;
}

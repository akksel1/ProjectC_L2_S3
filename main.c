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
    char* fpath = "C:\\Users\\akksel\\CLionProjects\\ProjectC_L2_S3\\sources\\dico.txt";
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
    int size;
    p_root my_tree=createEmptyTree();
    my_tree = setupTree();
    p_dict_line* parsedDict = parseLines(&size);
    int choice;
    int stop =0;
    int middle_line;

    while(stop==0) {
        printf("\n\n\t\t\t-- MAIN MENU --\n1 - Extract a word from the dictionary\n2 - Add a word to the tree\n3 - Quit");
        scanf("%d",&choice);
        switch (choice) {
            case (1): {
                printf("%d lines parsed. \n", size);
                middle_line = 9388;
                printf("Line %d is :\n", middle_line);
                printf("-Root : %s\n-Word : %s\n-Details : %s\n", parsedDict[middle_line]->root,
                       parsedDict[middle_line]->word, parsedDict[middle_line]->details);
                break;
            }
            case (2): {
                middle_line = 9388;
                printf("-Root : %s\n-Word : %s\n-Details : %s\n", parsedDict[middle_line]->root,parsedDict[middle_line]->word, parsedDict[middle_line]->details);
                addword(&my_tree, parsedDict[middle_line], which_type(parsedDict[middle_line]->details));
                findword_print(parsedDict[middle_line], my_tree, which_type(parsedDict[middle_line]->details));
                break;
            }
            case(3):
            {
                stop=1;
            }
            default:
                printf("Erreur");
        }

    }
    free(parsedDict);
    return 0;
}

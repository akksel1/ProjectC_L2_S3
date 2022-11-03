#include <stdio.h>
#include "sources/words.h"
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
    char* fpath = generate_dict_abs_path("sources\\dico.txt");
    char** lines;
    int size;
    *(tabsize) = 0;
    int result = readFile(fpath, &lines, &size);
    printf("There are %d lines in the dict \n", size);
    p_dict_line* tab = malloc(sizeof(p_dict_line)*size);
    if (result) {
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
    /*char* fpath = generate_dict_abs_path("sources\\dico.txt");
    char** lines;
    int size;
    int result = readFile(fpath, &lines, &size);
    if(result){
        int t_s;
        char** t;
        char* middle_line = lines[size/2];
        printf("We have %d lines \n", size);
        printf("Middle Line (l %d) is  : %s \n", size-1/2, middle_line);
        splitStr(middle_line, '\t', &t, &t_s);
        if (t_s){
            printf("splitted in :\n");
            for (int i = 0; i < t_s; i++){
                printf("%s\n", t[i]);
            }
        }
    }
    free(lines);
    free(fpath);*/
    int size;
    p_dict_line* parsedDict = parseLines(&size);
    printf("%d lines parsed. \n", size);
    int middle_line = 45221;
    printf("Line %d is :\n", middle_line);
    printf("-Root : %s\n-Word : %s\n-Details : %s\n", parsedDict[middle_line]->root, parsedDict[middle_line]->word, parsedDict[middle_line]->details);

    free(parsedDict);
    return 0;
}

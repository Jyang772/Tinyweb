//Cleans up argv[0]
//Useful for nothing other than my personal preference
//Takes in a pointer to argv[0]
//
#include <stdio.h>
#include <string.h>


void cleanUpName(char **v, char *name){

    char *progName;
    progName = name;
    *v = progName + strlen(name);
   for(*v;**v != '/';(*v)--);
    (*v)--;
    **v = '.';
}

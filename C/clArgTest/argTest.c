#include <stdio.h>
#include <string.h>

void argTest(char *arg[])
{

}


int main ( int argc, char *argv[] )
{
    int i;
    for (i=0;i<argc;++i){
        printf("%s\n",argv[i]);
    }
    return 0;
}

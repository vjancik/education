#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STREQ(a, b) (strcmp((a), (b)) == 0)
#define EMPTY(a) (strlen((a)) == 0)

typedef struct {
  int rows;
  int cols;
  unsigned char *cells;
} Map;

void print_desc()
{
    printf("Usage: proj3 --test FILENAME\n"
           "       proj3 --lpath R C FILENAME\n"
           "       proj3 --rpath R C FILENAME\n"
           "\n"
           "Program tests a map file for validity and finds a path through the maze using either\n"
           "the left hand or the right hand rule.\n"
           "\n"
           "Options:\n"
           "  --test FILENAME           Tests specified file and prints out Valid, if the map in\n"
           "                            the file is valid and has a valid format, Invalid otherwise.\n"
           "  --lpath R C FILENAME      Solves the maze by using the left hand rule and prints out the path.\n"
           "  --rpath R C FILENAME      Solves the maze by using the right hand rule and prints out the path.\n"
           );

}

//function isborder returns true if there is a border on the side specified by int border at position [r][c]
bool isborder(Map *map, int r, int c, int border) { //border: 0 - left, 1 - right, 2 - up/down
    return (map->cells[map->cols*r + c] >> border) & 1;
}

//function computes the first border the algorithm should check, based on the starting position and left/right hand rule
int start_border(Map *map, int r, int c, int leftright) { //return: 0 - left 1 - right, 2 - up/down; leftright: 0 - left, 1 - right
    if(r%2==0) {
        if(r==0) {
            if((c==0&&isborder(map,r,c,0))||(c==(map->cols-1)&&isborder(map,r,c,1)))
                return leftright == 0 ? 1 : 0;
        }
        if(c==0)
            return leftright == 0 ? 2 : 1;
        else if(c==(map->cols-1)) {
            if(c%2==0)
                return leftright == 0 ? 0 : 2;
            else
                return leftright == 0 ? 2 : 0;
        }
    }
    else {
        if(r==(map->rows-1)) {
            if(!(c==0&&!isborder(map,r,c,0))&&!(c==(map->cols-1)&&!isborder(map,r,c,1)))
                return leftright == 0 ? 0 : 1;
        }
        if(c==0)
            return leftright == 0 ? 1 : 2;
        else if(c==(map->cols-1)) {
            if(c%2==0)
                return leftright == 0 ? 2 : 0;
            else
                return leftright == 0 ? 0 : 2;
        }
    }
    return -1;
}

//function tests the logical validity of a map inside a file, it is called after the file has been tested for format validity
int test_map_format(Map *map) {
    for(int i=0;i < map->rows; ++i) {
        for(int j=0;j < map->cols; ++j) {
            if(i!=map->rows-1&&((i%2==0&&j%2==1)||(i%2==1&&j%2==0)))
                //checkDown
                if(isborder(map, i, j, 2) != isborder(map, i+1, j, 2))
                    return 0;
            if(j!=map->cols-1)
                //checkRight
                if(isborder(map, i, j, 1) != isborder(map, i, j+1, 0))
                    return 0;
        }
    }
    return 1;
}

//function tests the format validity of a map inside a file
int test_map_file(FILE *testFile, Map *map) {
    char symbol[9], symbol2[9];
    char newline;
    char *text, *text2;
    int number;

    map->cells = NULL;

    if(fscanf(testFile,"%s",symbol) == 0 || fscanf(testFile,"%s",symbol2) == 0) {
        return 0;
    }
    map->rows = (int) strtol(symbol, &text, 10);
    map->cols = (int) strtol(symbol2, &text2, 10);
    if(!EMPTY(text) || !EMPTY(text2)) {
        return 0;
    }
    if(map->rows <=0 || map->cols <=0) {
        return 0;
    }
    newline = fgetc(testFile);
    if(newline != '\n') {
        return 0;
    }

    if((map->cells = malloc(map->rows*map->cols)) == NULL){
        fprintf(stderr,"Couldn't allocate enough memory.");
        return -1;
    }

    for(int i=0;i<map->rows;++i) {
        for(int j=0;j<map->cols;++j) {
            if(fscanf(testFile,"%s",symbol) == 0) {
                return 0;
            }
            number = (int) strtol(symbol, &text, 10);
            map->cells[i*map->cols+j] = (char) number;
            if(!EMPTY(text)) {
                return 0;
            }
            if(number<0 || number>7) {
                return 0;
            }
        }
        newline = fgetc(testFile);
        if(newline != '\n') {
            return 0;
        }
    }
    return test_map_format(map);
}

//solves the maze by using either the left hand rule or the right hand rule
int solve_maze_lr(Map *map, int R, int C, char leftright) { //leftright: 0 - left, 1 - right
    char orient;
    int lastR = -1, lastC= -1;
    int turnC;
    bool canReturn;
    if(R<0 || R>=map->rows || C<0 || C>=map->cols) {
        fprintf(stderr,"Starting position outside of map bounds.\n");
        return 0;
    }
    orient = start_border(map,R,C,leftright);
    //while the "player" doesn't trail off the map
    while(R>=0 && R<map->rows && C>=0 && C<map->cols) {
        //prints the position if a move was carried out in the last loop
        if(lastR!=R || lastC != C) {
            printf("%d,%d\n",R+1,C+1);
            turnC=0;
            canReturn=false;
        }
        else { ++turnC; }
        //enables the "player" to return after exhausting all other options
        if(turnC==2)
            canReturn=true;
        lastR=R; lastC=C;
        //checks for borders in a given direction and performs the move
        switch(orient) {
            case 0:
                if(!isborder(map,R,C,0) && (C-1!=lastC || canReturn)) { --C; orient=1; } //leaving from left border -> entering from right
                break;
            case 1:
                if(!isborder(map,R,C,1) && (C+1!=lastC || canReturn)) { ++C; orient=0; } //leaving from right border -> entering from left
                break;
            case 2:
                if(!isborder(map,R,C,2)) {
                    if(((R%2==0&&C%2==0)||(R%2==1&&C%2==1)) && (R-1!=lastR || canReturn)) { --R; } //reversed triangles
                    else if((R+1!=lastR || canReturn)) { ++R; } //normal triangles
                }
                break;
        }
        //changes orientation for the next move based on the left/right hand rule setting
        if((R%2==0&&C%2==0)||(R%2==1&&C%2==1))
            leftright==0 ? --orient : ++orient;
        else
            leftright==0 ? ++orient : --orient;
        if(orient<0)
            orient+=3;
        else
            orient = orient%3;
    }
    return 1;
}

//handles command line arguments, calls respsonsible functions, allocates, deallocates memory safely
int main(int argc, const char *argv[])
{
    int returnVal;
    if(argc>=2) {
        Map map;
        FILE *testFile;
        if(STREQ(argv[1],"--help"))
            print_desc();
        else if(STREQ(argv[1],"--test") && argc==3) {
            if((testFile = fopen(argv[2], "r+")) == NULL) {
                fprintf(stderr,"Failed to open file.\n");
                return EXIT_FAILURE;
            }
            if((returnVal=test_map_file(testFile, &map))==1) {
                printf("Valid\n");
            }
            else if(returnVal==0)
                printf("Invalid\n");
            free(map.cells);
            fclose(testFile);
            if(returnVal==-1)
                return EXIT_FAILURE;
        }
        else if((STREQ(argv[1],"--lpath") || STREQ(argv[1],"--rpath")) && argc==5) {
            if((testFile = fopen(argv[4], "r+")) == NULL) {
                fprintf(stderr,"Failed to open file.\n");
                return EXIT_FAILURE;
            }
            if(test_map_file(testFile, &map)==1)
                solve_maze_lr(&map, strtol(argv[2],NULL,10)-1, strtol(argv[3],NULL,10)-1, STREQ(argv[1],"--lpath") ? 0 : 1);
            free(map.cells);
            fclose(testFile);
        }
        else if(STREQ(argv[1],"--shortest") && argc==5) {
        }
        else {
            fprintf(stderr,"No valid input argument combination.\n");
            return EXIT_FAILURE;

        }
    }
    return EXIT_SUCCESS;
}

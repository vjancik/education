#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include <errno.h>

#define MAX_CHAR_LINE 256

long count_lines(FILE *file) {
    char str[MAX_CHAR_LINE+1];
    str[MAX_CHAR_LINE-1]='\0';
    long num_of_lines=0;
    while(fgets(str, MAX_CHAR_LINE+1, file) != NULL) {
        if(str[MAX_CHAR_LINE-1]=='\n' || str[MAX_CHAR_LINE-1]=='\0')
            ++num_of_lines;
        str[MAX_CHAR_LINE-1]='\0';
    }
    rewind(file);
    return num_of_lines;
}

void skip_lines(long skip_num_lines, FILE *file) {
    char str[MAX_CHAR_LINE+1];
    str[MAX_CHAR_LINE-1]='\0';
    long num_of_lines=0;
    while(num_of_lines<skip_num_lines) {
        if(fgets(str, MAX_CHAR_LINE+1, file) == NULL)
            break;
        if(str[MAX_CHAR_LINE-1]=='\n' || str[MAX_CHAR_LINE-1]=='\0')
            ++num_of_lines;
        str[MAX_CHAR_LINE-1]='\0';
    }
}

void print_from_line(long from_line, FILE *file) {
    char str[MAX_CHAR_LINE+1];
    str[MAX_CHAR_LINE-1]='\0';
    skip_lines(from_line, file);
    while(fgets(str, MAX_CHAR_LINE+1, file) != NULL) {
        printf("%s",str);
    }
}

FILE *read_stdin_to_tmp() {
    FILE *file = tmpfile();
    int c;
    while((c = getchar()) != EOF) {
        fputc(c, file);
    }
    rewind(file);
    return file;
}

int main(int argc, char *argv[])
{
    bool from_line=false;
    long n_arg=10;

    int c;
    char *rest;
    //OPTION HANDLING
    while((c = getopt(argc, argv, "n:")) != -1) {
        switch (c) {
            case 'n':
                n_arg = strtol(optarg,&rest,10);
                if(strlen(rest)!=0 || n_arg<0) {
                    fprintf(stderr, "%s: %s: invalid number of lines\n", argv[0], optarg);
                    return 1;
                }
                if(optarg[0]=='+') {
                    from_line=true;
                }
                else {
                    from_line=false;
                }
                break;
            case '?':
                return 1;
            default:
                abort();
        }
    }

    long num_of_lines;

    if(optind==argc || strcmp(argv[optind],"-") == 0) {
        FILE *tmpfile;
        tmpfile = read_stdin_to_tmp();
        if(from_line) {
            print_from_line(n_arg-1, tmpfile);
        } else {
            num_of_lines = count_lines(tmpfile);
            print_from_line(num_of_lines-n_arg, tmpfile);
        }
        fclose(tmpfile);
    } else {
        FILE *file;
        for (int index = optind; index < argc; ++index) {
            file = fopen(argv[index], "r");
            if(file == NULL) {
                printf("tail: cannot open ‘%s’ for reading: %s\n",argv[index], strerror(errno));
                continue;
            }
            if((argc-optind)>1) {
                printf("==> %s <==\n",argv[index]);
            }
            if(from_line) {
                print_from_line(n_arg-1, file);
            } else {
                num_of_lines = count_lines(file);
                print_from_line(num_of_lines-n_arg, file);
            }
            if(argc-index!=1)
                printf("\n");
            fclose(file);
        }
    }
    return 0;
}

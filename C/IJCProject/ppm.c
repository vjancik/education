#include "ppm.h"

struct ppm * ppm_read(const char * filename) {
    struct ppm* ppmFile;
    char id[3];
    int byte;
    int colors, xsize, ysize;
    FILE * fp;
    fp = fopen(filename,"r");
    if(fp==NULL) {
        Warning("Subor sa nepodarilo otvorit.\n");
        return NULL;
    }
    fscanf(fp, "%2[^\n]", id);
    if(strcmp(id,"P6")!=0) {
        Warning("Subor nie je formatu PPM. ID: %s\n", id);
        fclose(fp);
        return NULL;
    }
    fscanf(fp,"%d %d %d ", &xsize, &ysize, &colors);
    if(colors!=255 || xsize<1 || ysize < 1) {
        Warning("Nepodporovany rozsah farieb alebo zly format. Farby: %d. Xsize: %d. Ysize: %d\n", colors, xsize, ysize);
        fclose(fp);
        return NULL;
    }
    //printf("Znak: '%c'\n",(char)fgetc(fp));
    ppmFile = malloc((sizeof(struct ppm))+3*xsize*ysize);
    ppmFile->xsize = xsize;
    ppmFile->ysize = ysize;
    for(int i=0; i<(3*xsize*ysize); ++i){
        byte = fgetc(fp);
        if(byte==EOF) {
            Warning("Subor je neuplny alebo poskodeny.\n");
            free(ppmFile);
            fclose(fp);
            return NULL;
        }
        ppmFile->data[i]=(char)byte;
    }
    fclose(fp);
    return ppmFile;
}

int ppm_write(struct ppm *p, const char * filename) {
    FILE * fp;
    int error;
    fp = fopen(filename, "w");
    if(fp==NULL) {
        Warning("Subor sa nepodarilo otvorit/vytvorit.\n");
        return -1;
    }

    fprintf(fp,"P6\n%d %d\n255\n",p->xsize, p->ysize);
    for(int i=0; i<(3*p->xsize*p->ysize); ++i) {
        error = fputc(p->data[i], fp);
        if(error==EOF) {
            Warning("Nastala chyba pri pisani suboru.\n");
            fclose(fp);
            return -1;
        }
    }

    fclose(fp);
    return 0;
}

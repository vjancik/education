
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define RIADOK 1025

enum rozsahEnum {riadok,stlpec,riadky,stlpce,rozsah};
enum operaciaEnum {vyber,minimum,maximum,suma,priemer};

double scitac=0;
int pocetPrvkov=0;
bool prvaHodnota=true;

struct flagyS {
    enum rozsahEnum rozsah;
    enum operaciaEnum operacia;
    int riadokD;
    int riadokH;
    short stlpecD;              //short, pretoze stlpcov moze byt maximalne 512
    short stlpecH;
} flagy;

void help()                     //vypise napovedu
{
    printf(" Vitajte v aplikaci jednoduchy tabulkovy kalkulator!\n\n"
           "Program ocakava textovu tabulku (CSV s bielymi znakmi namiesto ciarok) na stdin\n"
           "Dalej ocakava jednu z nasledujucich operacii ako parameter:\n"
           "\tselect\t(vypis)\n"
           "\tmin\t(minimum)\n"
           "\tmax\t(maximum)\n"
           "\tsum\t(sucet)\n"
           "\tavg\t(priemerna hodnota)\n\n"
           "Po tomto parametri je treba zadat rozsah buniek dalsim parametrom:\n"
           "\trow X \t\t\t(riadok X)\n"
           "\tcol X \t\t\t(stlpec X)\n"
           "\trows X Y \t\t(riadky X az Y vratane)\n"
           "\tcols X Y \t\t(stlpce X az Y vratane)\n"
           "\trange Y1 Y2 X1 X2 \t(rozsah X1 Y1 az X2 Y2 vratane)\n\n"
           "Maximalna dlzka riadku je 1024 znakov.\n\n"
           "Priklad vstupu: ./proj1 select rows 1 3 <tabulka.txt\n");
}

double max(double a, double b)
{
    return a>b ? a : b;
}

double min(double a, double b)
{
    return a<b ? a : b;
}

void chyba(char *sprava)
{
    fprintf(stderr, "%s\n", sprava);
}

bool nastavenieOperacie(char *argv[])                   //do struktury nastavi hodnoty podla zadanych argumentov
{
    if (strcmp(argv[1], "select")==0)
    {
        flagy.operacia=vyber;
    }
    else if (strcmp(argv[1], "min")==0)
    {
        flagy.operacia=minimum;
    }
    else if (strcmp(argv[1], "max")==0)
    {
        flagy.operacia=maximum;
    }
    else if (strcmp(argv[1], "sum")==0)
    {
        flagy.operacia=suma;
    }
    else if (strcmp(argv[1], "avg")==0)
    {
        flagy.operacia=priemer;
    }
    else
    {
        chyba("Zle zadana operacia. Pre pomoc zadajte \"--help\".");            //ak nenastane ani jeden z vyssie uvedenych pripadov, vypise chybu
        return false;
    }
    return true;
}

bool nastavenieRozsahu(char *argv[])                    //do struktury nastavi hodnoty podla zadanych argumentov
{
    if (strcmp(argv[2], "row")==0)
    {
        flagy.rozsah=riadok;
    }
    else if (strcmp(argv[2], "rows")==0)
    {
        flagy.rozsah=riadky;
    }
    else if (strcmp(argv[2], "col")==0)
    {
        flagy.rozsah=stlpec;
    }
    else if (strcmp(argv[2], "cols")==0)
    {
        flagy.rozsah=stlpce;
    }
    else if (strcmp(argv[2], "range")==0)
    {
        flagy.rozsah=rozsah;
    }
    else
    {
        chyba("Zly rozsah. Pre pomoc zadajte \"--help\".");                     //ak nenastane ani jeden z vyssie uvedenych pripadov, vypise chybu
        return false;
    }
    return true;
}

bool nastavenieLimitov(int argc, char *argv[])          //skontroluje ci je zadany spravny pocet argumentov
{
    bool validneArgumenty=true;
    flagy.riadokD=1;
    flagy.riadokH=INT_MAX;                              //inicializacia premennej kvoli neskorsej podmienke, kde sa tato premenna pouziva
    flagy.stlpecD=1;
    flagy.stlpecH=SHRT_MAX;
    switch (flagy.rozsah) {                             //porovnava ci pre jednotlive pripady bol zadany spravny pocet argumentov
        case riadok:                                    //ak ano, priradi do struktury hodnoty ciselnych argumentov
            if (argc==4) {
                flagy.riadokD=atoi(argv[3]);
            }
            else {
                
                validneArgumenty=false;
            }
            break;
        case riadky:
            if (argc==5) {
                flagy.riadokD=atoi(argv[3]);
                flagy.riadokH=atoi(argv[4]);
            }
            else {
                validneArgumenty=false;
            }
            break;
        case stlpec:
            if (argc==4) {
                flagy.stlpecD=atoi(argv[3]);
            }
            else {
                validneArgumenty=false;
            }
            break;
        case stlpce:
            if (argc==5) {
                flagy.stlpecD=atoi(argv[3]);
                flagy.stlpecH=atoi(argv[4]);
            }
            else {
                validneArgumenty=false;
            }
            break;
        case rozsah:
            if (argc==7) {
                flagy.riadokD=atoi(argv[3]);
                flagy.riadokH=atoi(argv[4]);
                flagy.stlpecD=atoi(argv[5]);
                flagy.stlpecH=atoi(argv[6]);
            }
            else {
                validneArgumenty=false;
            }
            break;
    }
    if (flagy.riadokD<1 || flagy.riadokH<1 || flagy.stlpecD<1 || flagy.stlpecH<1)   // kontroluje sucasne chybu pri konverzii na int a zadany zaporny rozsah
        validneArgumenty=false;
    if (!validneArgumenty) {
        chyba("Nespravny rozsah. Pre pomoc zadajte \"--help\".");       //ak niekde nastala chyba, upovedomi o tom uzivatela
    }
    return validneArgumenty;
}

bool kontrolaLimitov(char *argv[])              //skontroluje ci su argumenty zadane v zmysluplnom poradi
{
    bool validneArgumenty=true;
    switch (flagy.rozsah) {
        case riadky:
            if (atoi(argv[3])>atoi(argv[4]))    //porovnava ci rozsah riadku nie je zadany od vacsieho k mensiemu
                validneArgumenty=false;
            break;
        case stlpce:
            if (atoi(argv[3])>atoi(argv[4]))    //porovnava ci stlpca riadku nie je zadany od vacsieho k mensiemu
                validneArgumenty=false;
            break;
        case rozsah:
            if (atoi(argv[3])>atoi(argv[4]) || atoi(argv[5])>atoi(argv[6]))     //porovnava ci rozsah rozsahu nie je zadany od vacsieho k mensiemu
                validneArgumenty=false;                                                         //pre dvojice riadkov a stlpcov
            break;
        default:
            break;
    }
    if (!validneArgumenty) {
        chyba("Zly rozsah argumentov. Pre pomoc zadajte \"--help\".");
    }
    return validneArgumenty;
}

bool spracovanieStlpca(char *stlpecString)
{
    double tempNumber=0;
    char *zvysokSlova=NULL;
    switch (flagy.operacia) {
        case vyber:
            tempNumber = strtod(stlpecString, &zvysokSlova);
            if (strlen(zvysokSlova)!=0)                         //ak je nieco v zvysokSlova, nacitane slovo nebolo cislo a vypiseho ho ako string
                printf("%s\n", stlpecString);
            else
                printf("%.10g\n", tempNumber);                  //nacitane slovo bolo cislo, vypise v tvare .10g
            break;
        case minimum:
            if(prvaHodnota) {
                scitac = strtod(stlpecString, &zvysokSlova);    //prve slovo riadku priradi do minima
                prvaHodnota=false;
            }
            else
                scitac = min(scitac,strtod(stlpecString, &zvysokSlova));    //potom uz hodnoty porovnava, pripadne priradi
            break;
        case maximum:
            if(prvaHodnota) {
                scitac = strtod(stlpecString, &zvysokSlova);    //prve slovo riadku priradi do maxima
                prvaHodnota=false;
            }
            else
                scitac =  max(scitac,strtod(stlpecString, &zvysokSlova));   //potom uz hodnoty porovnava, pripadne priradi
            break;
        case suma:
            scitac += strtod(stlpecString, &zvysokSlova);
            break;
        case priemer:
            scitac += strtod(stlpecString, &zvysokSlova);
            ++pocetPrvkov;                                      //inkrementuje pocet prvkov pre neskorsi vypocet priemeru
            break;
    }
    if (flagy.operacia!=vyber && strlen(zvysokSlova)!=0){       //ak operacia obsahuje neciselne argumenty ulozne strtod-om do zvysokSlova
        chyba("Neciselne hodnoty v rozsahu. Pre pomoc zadajte \"--help\".");
        return false;
    }
    return true;
}

bool kontrolaRozsahuStlpca(char *stlpecString, int cisloStlpca)
{
    bool uspesneSpracovanie=true;
    //printf("'%s'\n", stlpecString);
    switch (flagy.rozsah)
    {
        case stlpec:
            if(flagy.stlpecD==cisloStlpca)                                  //ak sa zadane cislo stlpca rovna cislu nacitaneho riadku, posunie ho na spracovanie
                uspesneSpracovanie = spracovanieStlpca(stlpecString);
            break;
        case stlpce:                                                        //ak sa zadane cislo stlpcov rovna cislu nacitaneho riadku, posunie ho na spracovanie
            if(flagy.stlpecD<=cisloStlpca&&flagy.stlpecH>=cisloStlpca)
                uspesneSpracovanie = spracovanieStlpca(stlpecString);
            break;
        case rozsah:                                                        //ak sa zadane cislo stlpcov rovna cislu nacitaneho riadku, posunie ho na spracovanie
            if(flagy.stlpecD<=cisloStlpca&&flagy.stlpecH>=cisloStlpca)
                uspesneSpracovanie = spracovanieStlpca(stlpecString);
            break;
        case riadok:
        case riadky:
            uspesneSpracovanie = spracovanieStlpca(stlpecString);           //spracuva vsetky stlpce
            break;
    }
    if (!uspesneSpracovanie)
        return false;
    return true;
}

bool mimoRozsahuStlpca(int cisloStlpca)             //kontroluje ci uzivatel nezadal rozsah presahujuci pocet stlpcov
{
    bool validneArgumenty=true;
    switch (flagy.rozsah)
    {
        case rozsah:
        case stlpce:
            if (flagy.stlpecH>cisloStlpca) validneArgumenty=false;
        case stlpec:
            if (flagy.stlpecD>cisloStlpca) validneArgumenty=false;
            break;
        default:
            break;
    }
    if(!validneArgumenty)
    {
        chyba("Zadany rozsah presahuje pocet stlpcov. Pre pomoc zadajte \"--help\".");
        return false;
    }
    return true;
}


bool spracovanieRiadku(char *riadokString)
{
    int cisloStlpca = 1;
    
    char *ukazovatel;
    const char *medzera = " \t\n";                  //mozne oddelenia slov v tabulke, podla ich bude rozdelovat
    ukazovatel = strtok(riadokString, medzera);     //postupne vracia ukazovatele na casti riadokString oddelene medzerou
    
    while((ukazovatel!= NULL))                      //kym nepride na koniec riadokString
    {
        if(!kontrolaRozsahuStlpca(ukazovatel, cisloStlpca))
            return false;
        ukazovatel = strtok(NULL, medzera);
        ++cisloStlpca;
    }
    if(!mimoRozsahuStlpca(cisloStlpca)) return false;
    return true;
}

bool kontrolaRozsahuRiadku(char *riadokString,int cisloRiadku)              //zisti ci ma pracovat s nacitanym riadkom
{
    bool uspesneSpracovanie=true;
    switch (flagy.rozsah) {
        case riadok:
            if(flagy.riadokD==cisloRiadku)
                uspesneSpracovanie = spracovanieRiadku(riadokString);       //ak sa zadane cislo riadku rovna cislu nacitaneho riadku, posunie ho na spracovanie
            break;
        case riadky:
        case rozsah:
            if(flagy.riadokD<=cisloRiadku && flagy.riadokH>=cisloRiadku)    //ak sa zadane cislo riadkov rovna cislu nacitaneho riadku, posunie ho na spracovanie
                uspesneSpracovanie = spracovanieRiadku(riadokString);
            break;
        case stlpec:
        case stlpce:
            uspesneSpracovanie = spracovanieRiadku(riadokString);           //spracuva vsetky riadky
            break;
    }
    if(!uspesneSpracovanie) return false;
    return true;
}

bool mimoRozsahuRiadku(int cisloRiadku)                                     //kontroluje ci uzivatel nezadal rozsah presahujuci pocet riadkov
{
    bool validneArgumenty=true;
    
    switch (flagy.rozsah) {
        case rozsah:
        case riadky:
            if (flagy.riadokH>cisloRiadku) validneArgumenty=false;
        case riadok:
            if (flagy.riadokD>cisloRiadku) validneArgumenty=false;
            break;
        default:
            break;
    }
    if(!validneArgumenty)
    {
        chyba("Zadany rozsah presahuje pocet riadkov. Pre pomoc zadajte \"--help\".");
        return false;
    }
    return true;
}

bool spracovanieVstupu()
{
    char riadok[RIADOK];
    char znak,buduciZnak;
    int index=0, cisloRiadku=1;
    znak=getchar();
    buduciZnak=getchar();               //do znaku aj buducehoZnaku priradi hodnoty este pred cyklom, pretoze inak by nam usiel prvy znak riadku
    
    while (znak!=EOF)
    {
        riadok[index]=znak;             //nacitava cely riadok po znakoch
        ++index;
        
        if (/*znak=='\n' && */buduciZnak==EOF)
        {
            kontrolaRozsahuRiadku(riadok,cisloRiadku);
            break;
        }
        if (znak=='\n')                //konec riadku
        {
            if(!kontrolaRozsahuRiadku(riadok,cisloRiadku))
            {
                return false;
            }
            index=0;
            ++cisloRiadku;
            //  printf("Som tu, ty koala.\n");
        }
        znak=buduciZnak;
        if(znak!=EOF) buduciZnak=getchar();
    }
    if(!mimoRozsahuRiadku(cisloRiadku)) return false;
    
    if(flagy.operacia==priemer)         //vydeli sumu poctom prvkov
        scitac/=pocetPrvkov;
    return true;
}

int main(int argc, char * argv[])
{
    if (argc<2)
    {
        chyba("Malo argumentov. Pre pomoc zadajte \"--help\".");
        return EXIT_FAILURE;
    }
    
    if (strcmp(argv[1], "--help")==0)
    {
        help();
        return EXIT_SUCCESS;
    }
    
    if (!nastavenieOperacie(argv) ||
        !nastavenieRozsahu(argv) ||
        !nastavenieLimitov(argc, argv) ||
        !kontrolaLimitov(argv) ||
        !spracovanieVstupu())
    {
        return EXIT_FAILURE;    //pretekanim osetrene, ak niekde v procese nastal false, cele false
    }
    if(!flagy.operacia==vyber)
        printf("%.10g\n",scitac);
}

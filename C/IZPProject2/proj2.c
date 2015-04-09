#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define PI 3.14159265358979
#define STREQ(a, b) (strcmp((a), (b)) == 0)

//globalna struktura potrebna pre optimalizaciu pocitania taylor_tan z dovodu stanoveneho formatu prototypu taylor_tan
//ktory mi ine riesenie nepovoluje, power by sa dal optimalizovat bez globalnej struktury, ale ked uz to robim takto, tak vsade
struct partialResult {
    double result;
    unsigned int iter;
} prTaylor, prPow;

//Coefficients for calculating the tangent using taylor_tan. First 13 iterations.
double taylorNum[13] = {1, 1, 2, 17, 62, 1382, 21844, 929569, 6404582, 443861162, 18888466084, 113927491862, 58870668456604};
double taylorDenom[13] = {1, 3, 15, 315, 2835, 155925, 6081075, 638512875, 10854718875, 1856156927625, 194896477400625, 49308808782358125, 3698160658676859375};

//Required function prototypes
double taylor_tan(double x, unsigned int n);
double cfrac_tan(double x, unsigned int n);

//prints description of the program
void print_desc(){
    printf("Usage: proj2 --tan A N M\n"
           "       proj2 [-c X] -m A [B]\n"
           "Compute tangent of an angle in radians, or height / distance of an object.\n"
           "\n"
           "Options:\n"
           "  --tan A N M       Calculates tangent of angle A and prints out results from Nth to Mth iteration.\n"
           "  -m A [B]          Calculates the distance of the object based on angle A and implicit measuring device height 1.5m.\n"
           "                    If the optional angle B is input, also calculates the height of the object being measured.\n"
           "  [-c X]            Overrides the default measuring device height 1.5m to be X (in meters).\n"
    );
}
//Calculates Nth power of a float. For optimalization purposes, only works for a single number throught the program.
double power(double x, unsigned int n){
    for (;prPow.iter<n; ++prPow.iter)
        prPow.result*=x;
    return prPow.result;
}
//Calculates the taylor expansion up to nth iteration of the function tan
double taylor_tan(double x, unsigned int n) {
    for (;prTaylor.iter<n; prTaylor.iter++) {
        prTaylor.result+=taylorNum[prTaylor.iter]*power(x,2*prTaylor.iter+1)/taylorDenom[prTaylor.iter];
    }
    return prTaylor.result;
}
//Calculates tan function  up to nth iteration using chained fractions
double cfrac_tan(double x, unsigned int n) {
    double xx = x*x;
    double denominator = 0;
    if(x==0)
        return 0;
    for(int i=(n+1); i>0; --i) {
        denominator = (2*i - 1) - xx/denominator;
    }
    return x/denominator;
}
//Function responsible for running taylor_tan and cfrac_tan and printing out the results as required by the specification
void comp_tan(double angle, unsigned int N, unsigned int M) {
    double taylor,cfrac=0,mathlib,diffTaylor,diffCfrac=0;
    mathlib = tan(angle);
    for (unsigned int i = N; i<=M; ++i) {
        taylor = taylor_tan(angle,i);
        cfrac = cfrac_tan(angle,i);
        diffTaylor = mathlib - taylor;
        diffCfrac = mathlib - cfrac;
        printf("%d %e %e %e %e %e\n",i,mathlib,taylor,diffTaylor,cfrac,diffCfrac);
    }
}
//function that calculates distance and height of a measured object based on the angles between it and the measuring device, which are provided
void measures(double alpha, double beta, double mHeight) {
    int i = 2;
    double tanAlpha0 = alpha, tanAlpha1 = cfrac_tan(alpha, i);
    double distance = 0;
    if(mHeight == 0)
        mHeight = 1.5;
    while(tanAlpha1 - tanAlpha0 >= 0.0000000001) {
        ++i;
        tanAlpha0 = tanAlpha1;
        tanAlpha1 = cfrac_tan(alpha, i);
    }
    distance = mHeight/tanAlpha1;
    printf("%.10e\n", distance);

    if (beta!=0){
        i = 2;
        double tanBeta0 = beta, tanBeta1 = cfrac_tan(beta, i);
        while(tanBeta1 - tanBeta0 >= 0.0000000001) {
            ++i;
            tanBeta0 = tanBeta1;
            tanBeta1 = cfrac_tan(beta, i);
        }
        printf("%.10e\n", tanBeta1*distance + mHeight);
    }
}
int main(int argc, const char *argv[])
{
    double argX = 0;
    double argB = 0;
    //input arguments processing
    if(STREQ(argv[1],"--help")) {
        print_desc();
        return 0;
    }
    else if (STREQ(argv[1],"--tan") && argc == 5) {
        prTaylor.result=strtod(argv[2],NULL);
        prTaylor.iter=1;
        prPow.result=strtod(argv[2],NULL);
        prPow.iter=1;
        comp_tan(fmod(strtod(argv[2],NULL),(PI/2)),strtod(argv[3],NULL),strtod(argv[4],NULL));
    }
    else if (STREQ(argv[1],"-c") && argc >= 5) {
        argX = strtod(argv[2],NULL);
        if (argc == 6 )
            argB = strtod(argv[5],NULL);
        measures(strtod(argv[4],NULL),argB, argX);

    }
    else if (STREQ(argv[1],"-m") && argc >= 3) {
        if (argc == 4)
            argB = strtod(argv[3],NULL);
        measures(strtod(argv[2],NULL),argB,0);
    }
    return 0;
}

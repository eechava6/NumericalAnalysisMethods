#include "function.h"

double f(double x){
    return pow(x,4)-x-10;
}

//pow(x,2) - (3 * x) - 4

double df(double x){
    return (4*pow(x,3)) - 1;
}

double ddf(double x){
    return 12*pow(x,2);
}

double g(double x){
    return pow(x+10,0.25);
}
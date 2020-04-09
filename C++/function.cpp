#include "function.h"

double f(double x){
    return pow(x,4.5)-75;
}

//pow(x,2) - (3 * x) - 4

double dx(double x){
    return (2 * x) - 3;
}

double secondDf(double x){
    return 0;
}

double g(double x){
    return 0;
}
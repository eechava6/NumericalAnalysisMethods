#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "function.h"

using namespace std;

vector<vector<double>> bisection(double a, double b, double tolerance, int max_iterators) {
    vector<vector<double>> returnList;
    vector<double> row;
    
    double a_evaluated_f = f(a);
    double b_evaluated_f = f(b);

    if (a_evaluated_f == 0) {
        cout << "root on " << a;
    }
    else if(b_evaluated_f == 0 ){
        cout << "root on " << b;
    }
    else if (a_evaluated_f * b_evaluated_f < 0) {

        int count = 1;

        double xMiddle = (a + b) / 2;
        double yMiddle = f(xMiddle);

        double error = tolerance + 1;

        row.push_back(count);
        row.push_back(a);
        row.push_back(b);
        row.push_back(xMiddle);
        row.push_back(yMiddle);
        row.push_back(0);
        returnList.push_back(row);
        row.clear();

        while (error > tolerance  && yMiddle != 0 and count <  max_iterators)
        {
            if (a_evaluated_f * yMiddle < 0) {
                b = xMiddle;
                b_evaluated_f = yMiddle;
            }
            else {
                a = xMiddle;
                a_evaluated_f = yMiddle;

            }

            double auxMiddle = xMiddle;

            xMiddle = (a + b) / 2;
            yMiddle = f(xMiddle);

            error = abs(xMiddle - auxMiddle);

            count++;

            row.push_back(count);
            row.push_back(a);
            row.push_back(b);
            row.push_back(xMiddle);
            row.push_back(yMiddle);
            row.push_back(error);
            returnList.push_back(row);
            row.clear();
        }
    }
    return returnList;
}

int main()
{
    cout << "Enter a" << "\n";
    double a;
    cin >> a;

    cout << "Enter b" << "\n";
    double b;
    cin >> b;

    cout << "Enter tol" << "\n";
    double tolerancia;
    cin >> tolerancia;

    cout << "Enter max_iter" << "\n";
    int repeticiones;
    cin >> repeticiones;

    vector<vector<double>> tabla = bisection(a, b, tolerancia, repeticiones);

    for (int i = 0; i < tabla.size(); i++)
    {
        cout << "| " << tabla[i][0] 
            << " | " << tabla[i][1] 
            << " | " << tabla[i][2] 
            << " | " << tabla[i][3] 
            << " | " << tabla[i][4] 
            << " | " << tabla[i][5] << "\n";
    }
}



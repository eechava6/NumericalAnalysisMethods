#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "function.h"

using namespace std;

vector<vector<double>> secant(double x0, double x1, double tolerance, int max_iterators) {
    vector<vector<double>> returnList;
    vector<double> row;
    
    double x0_f = f(x0);
    double x1_f = f(x1);
    double denominator = NULL;
    if (x0_f == 0) {
        cout << "root on " << x0;
    }
    else
    {
        int count = 0;
        double error = tolerance + 1;

        denominator = x1_f - x0_f;

        row.push_back(count);
        row.push_back(x0);
        row.push_back(x0_f);
        row.push_back(0);
        returnList.push_back(row);
        row.clear();

        while (error > tolerance  && x1_f != 0 and count <  max_iterators)
        {
            double xAux = x1 - ((x1_f * (x1 - x0)) / denominator);

            error = abs(xAux - x1);

            x0 = x1;
            x0_f = x1_f;

            x1 = xAux;
            x1_f = f(x1);

            denominator = x1_f - x0_f;

            count++;

            row.push_back(count);
            row.push_back(x0);
            row.push_back(x0_f);
            row.push_back(error);
            returnList.push_back(row);
            row.clear();
        }
    }

    if (x1_f == 0) {
        cout << x1 << "is a root" << "\n";
    }
    else if (denominator == 0) {
        cout << "possible multiple root" << "\n";
    }
    return returnList;
}

int main()
{
    cout << "Enter x0" << "\n";
    double x0;
    cin >> x0;

    cout << "Enter x1" << "\n";
    double x1;
    cin >> x1;

    cout << "Enter tol" << "\n";
    double tolerance;
    cin >> tolerance;

    cout << "Enter max_iter" << "\n";
    int max_iterations;
    cin >> max_iterations;

    vector<vector<double>> tabla = secant(x0, x1, tolerance, max_iterations);

    for (int i = 0; i < tabla.size(); i++)
    {
        cout << "| " << tabla[i][0] 
            << " | " << tabla[i][1] 
            << " | " << tabla[i][2] 
            << " | " << tabla[i][3] << "\n";
    }
}




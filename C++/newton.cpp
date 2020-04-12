#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "function.h"

using namespace std;

vector<vector<double>> newton(double x0, double tolerance, int max_iterations) {
    vector<vector<double>> returnList;
    vector<double> row;

    double f_x = f(x0);
    double df_x = df(x0);

    int count = 0;
    double error = tolerance + 1;

    row.push_back(count);
    row.push_back(x0);
    row.push_back(f_x);
    row.push_back(df_x);
    row.push_back(0);
    returnList.push_back(row);
    row.clear();

    while (error > tolerance&& count < max_iterations && f_x != 0 && df_x != 0) {
        double next_x = x0 - (f_x / df_x);
        f_x = f(next_x);
        df_x = df(next_x);

        error = abs(next_x - x0);
        x0 = next_x;
        count++;

        row.push_back(count);
        row.push_back(x0);
        row.push_back(f_x);
        row.push_back(df_x);
        row.push_back(error);
        returnList.push_back(row);
        row.clear();
    }

    if (f_x == 0) {
        cout << x0 << " is a root" << "\n";
    }
    else if (error <= tolerance) {
        cout << " is an approximation with tolerance " << "\n";
    }
    else if (df_x == 0) {
        cout << " is a possible multiple root" << "\n";
    }
    else {
        cout << "maximum iterations reached" << "\n";
    }

    return returnList;

}


int main()
{
    cout << "Enter x0" << "\n";
    double x0;
    cin >> x0;

    cout << "Enter tolerance" << "\n";
    double tolerancia;
    cin >> tolerancia;

    cout << "Enter max iterations" << "\n";
    int repeticiones;
    cin >> repeticiones;

    vector<vector<double>> tabla = newton(x0, tolerancia, repeticiones);

    for (int i = 0; i < tabla.size(); i++)
    {
        cout << "| " << tabla[i][0]
            << " | " << tabla[i][1]
            << " | " << tabla[i][2]
            << " | " << tabla[i][3]
            << " | " << tabla[i][4] << "\n";
    }
}
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "function.h"

using namespace std;

vector<vector<double>> fixedPoint(double xi, double tol, int max_iter) {
    vector<vector<double>> returnList;
    vector<double> row;
    
    double f_xi = f(xi);
    double g_xi = g(xi);
    double error = tol + 1 ;
    int iter = 1;
    row.push_back(xi);
    row.push_back(g_xi);
    row.push_back(f_xi);
    row.push_back(0);
    returnList.push_back(row);
    row.clear();

    while(error > tol && iter <= max_iter){
        double xn = g_xi;
        g_xi = g(xn);
        f_xi = f(xn);
        error = abs(xn-xi);
        xi = xn;
        row.push_back(xi);
        row.push_back(g_xi);
        row.push_back(f_xi);
        row.push_back(error);
        returnList.push_back(row);
        row.clear();
        if(f_xi == 0){
            cout << "Root found!" << endl;
            return returnList;
        }else if(error <= tol){
            cout << "Err lower than tolerance!" << endl;
            return returnList;
        }else if(iter >= max_iter){
            cout << "Overpassed max iteration!" << endl;
        }
        iter ++;

    }
    return returnList;
}

int main()
{
    cout << "Enter xi" << "\n";
    double xi;
    cin >> xi;

    cout << "Enter tol" << "\n";
    double tol;
    cin >> tol;
    
    cout << "Enter max_iter" << "\n";
    double max_iter;
    cin >> max_iter;

    vector<vector<double>> tabla = fixedPoint(xi, tol, max_iter);
    cout << "| " << "xi"
            << " | " << "g(xi)"
            << " | " << "f(xi)"
            << " | " << "error \n";

    for (int i = 0; i < tabla.size(); i++)
    {
        cout << "| " << tabla[i][0] 
            << " | " << tabla[i][1] 
            << " | " << tabla[i][2] 
            << " | " << tabla[i][3]  << endl;
    }
}



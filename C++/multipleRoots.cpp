#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "function.h"
#include <math.h>

using namespace std;


double x_next(double xn){
    return xn - ((f(xn)*df(xn))/((pow(df(xn),2))-(f(xn)*ddf(xn))));
}

vector<vector<double>> multipleRoots(double xi, double tol, int max_iter) {
    vector<vector<double>> returnList;
    vector<double> row;

    double f_xi = f(xi);
    double df_xi = df(xi);
    double ddf_xi = ddf(xi);
    double error = tol + 1 ;
    int iter = 1;
    row.push_back(xi);
    row.push_back(f_xi);
    row.push_back(df_xi);
    row.push_back(ddf_xi);
    row.push_back(0);
    returnList.push_back(row);
    row.clear();

    while(error > tol && iter < max_iter){
        
        double tempXi = xi;
        xi = x_next(xi);
        error = abs(xi - tempXi);
        f_xi = f(xi);
        df_xi = df(xi);
        ddf_xi = ddf(xi);
        row.push_back(xi);
        row.push_back(f_xi);
        row.push_back(df_xi);
        row.push_back(ddf_xi);
        row.push_back(error);
        returnList.push_back(row);
        row.clear();
        if(f_xi == 0){
            cout << "Root found!" << endl;
            return returnList;
        }else if(error < tol){
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

    vector<vector<double>> tabla = multipleRoots(xi, tol, max_iter);
    cout << "| " << "xi"
            << " | " << "f(xi)"
            << " | " << "f'(xi)" 
            << " | " << "f''(xi)"
            << " | " << "error \n";

    for (int i = 0; i < tabla.size(); i++)
    {
        cout << "| " << tabla[i][0] 
            << " | " << tabla[i][1] 
            << " | " << tabla[i][2] 
            << " | " << tabla[i][3] 
            << " | " << tabla[i][4] << endl;
    }
}



#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "function.h"

using namespace std;


double xrCalc(double xi, double xs){
    return xi - ((f(xi)*(xs-xi))/(f(xs)-f(xi)));
}

vector<vector<double>> falseRule(double xi, double xs, double tol, int max_iter) {
    vector<vector<double>> returnList;
    vector<double> row;
    
    double xr = xrCalc(xi,xs);
    double f_xr = f(xr);
    double error = tol + 1 ;
    int iter = 1;
    row.push_back(xi);
    row.push_back(xs);
    row.push_back(xr);
    row.push_back(f_xr);
    row.push_back(0);
    returnList.push_back(row);
    row.clear();

    while(error > tol && iter < max_iter){
        if(f_xr < 0){
            xi = xr;
        }else{
            xs = xr; 
        }
        double tempXr = xr;
        xr = xrCalc( xi, xs);
        error = abs(xr - tempXr);
        f_xr = f(xr);
        
        row.push_back(xi);
        row.push_back(xs);
        row.push_back(xr);
        row.push_back(f_xr);
        row.push_back(error);
        returnList.push_back(row);
        row.clear();
        if(f_xr == 0){
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

    cout << "Enter xs" << "\n";
    double xs;
    cin >> xs;

    cout << "Enter tol" << "\n";
    double tol;
    cin >> tol;
    
    cout << "Enter max_iter" << "\n";
    double max_iter;
    cin >> max_iter;

    vector<vector<double>> tabla = falseRule(xi, xs, tol, max_iter);
    cout << "| " << "xi"
            << " | " << "xs"
            << " | " << "xr" 
            << " | " << "f(xr)"
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



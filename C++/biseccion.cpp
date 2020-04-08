#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

double functionMethod(double x) {
    return x - 2.35;
}

vector<vector<double>> biseccion(double a, double b, double tolerance, int max_iterators) {
    vector<vector<double>> returnList;
    vector<double> row;
    
    double a_evaluated_f = functionMethod(a);
    double b_evaluated_f = functionMethod(b);

    if (a_evaluated_f == 0) {
        cout << "root on " << a;
    }
    else if(b_evaluated_f == 0 ){
        cout << "root on " << b;
    }
    else if (a_evaluated_f * b_evaluated_f < 0) {

        int count = 1;

        double xMiddle = (a + b) / 2;
        double yMiddle = functionMethod(xMiddle);

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
            yMiddle = functionMethod(xMiddle);

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
    cout << "Ingrese a" << "\n";
    double a;
    cin >> a;

    cout << "Ingrese b" << "\n";
    double b;
    cin >> b;

    cout << "Ingrese tolerancia" << "\n";
    double tolerancia;
    cin >> tolerancia;

    cout << "Ingrese repeticiones" << "\n";
    int repeticiones;
    cin >> repeticiones;

    vector<vector<double>> tabla = biseccion(a, b, tolerancia, repeticiones);

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



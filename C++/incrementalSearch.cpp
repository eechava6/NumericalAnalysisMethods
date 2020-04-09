#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "function.h"

using namespace std;

vector<vector<double>> incrementalSearch(double start, double step, double stop) {
    vector<vector<double>> returnList;
    vector<double> row;
    
    double evaluated_f = f(start);
    row.push_back(start);
    row.push_back(evaluated_f);
    row.push_back(0);
    row.push_back(0);
    returnList.push_back(row);
    row.clear();

    for(double i = start+step; i <= stop; i += step){
        double mult = evaluated_f * f(i);
        double root;
        if(mult < 0){
            root = 1;
        }else{
            root = 0;
        }
        row.push_back(i);
        row.push_back(f(i));
        row.push_back(mult);
        row.push_back(root);
        returnList.push_back(row);
        row.clear();
        evaluated_f = f(i);
    }
    return returnList;
}

int main()
{
    cout << "Enter start" << "\n";
    double start;
    cin >> start;

    cout << "Enter step" << "\n";
    double step;
    cin >> step;

    cout << "Enter end" << "\n";
    double end;
    cin >> end;

    vector<vector<double>> tabla = incrementalSearch(start, step, end);
    cout << "| " << 'x' 
            << " | " << "f(x)"
            << " | " << "f(a)*f(b)" 
            << " | " << "root \n";

    for (int i = 0; i < tabla.size(); i++)
    {
        cout << "| " << tabla[i][0] 
            << " | " << tabla[i][1] 
            << " | " << tabla[i][2] 
            << " | " << tabla[i][3] << "\n";
    }
}



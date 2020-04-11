#ifndef utils   /* Include guard */
#define utils
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

vector<double> split(string &s, char delim);  /* An example function declaration */

vector<vector<double>> parseMatrix(string filename);

void writeTable(vector<vector<vector<double>>> matrix);

bool isSquared(vector<vector<double>> matrix);

int calcDeterminant(vector<vector<double>> matrix);

vector<double> getMultipliers(vector<vector<double>> matrix,int nCol);

vector<vector<double>> rowOps(vector<vector<double>> matrix, int nCol, vector<double> multipliers);

vector<vector<double>> transpose(vector<vector<double>> matrix);
#endif // function
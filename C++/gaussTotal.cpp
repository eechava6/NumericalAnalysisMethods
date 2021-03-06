#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "utils.h"


using namespace std;

vector<vector<vector<double>>> gaussTotal(vector<vector<double>> matrix){
  vector<vector<vector<double>>> pivots; 
  vector<double> indexes; 
  pivots.push_back(matrix);
  if(!isSquared(matrix)){
    cout << "Not square + 1 col matrix" << endl;
    return pivots;
  }
  if(calcDeterminant(matrix) == 0){
    cout << "Det 0!" << endl;
    return pivots;
  }
  int times = matrix.size()-1;
  for(int i = 0; i <= times; i++ ){
    indexes.push_back(i);
  }

  for(int nCol = 0; nCol < times; nCol++){
    int index;
    double max = 0;
    int maxRow = 0;
    int maxCol = 0;

    for(int i = nCol; i < matrix.size(); i++){
        for (int j = nCol; j < matrix.size(); j++){
            if (abs(matrix[i][j]) > abs(max)) {
                index = i;
                max = matrix[i][j];
                maxRow = i;
                maxCol = j;
            }
        }
    }
    cout << max << "\n";
    if(abs(max) > matrix[nCol][nCol]){
        matrix[nCol].swap(matrix[index]);
        int temInd = indexes[nCol];
        indexes[nCol] = indexes[index];
        indexes[index] = temInd;
        vector<vector<double>> temp =matrix; 
        pivots.push_back(temp);

        for (int i = 0; i < matrix.size(); i++)
        {
            double aux = matrix[i][nCol];
            matrix[i][nCol] = matrix[i][maxCol];

            matrix[i][maxCol] = aux;
        }
    }    
    vector<double> multipliers = getMultipliers(matrix, nCol);
    bool checkZero = true;
    for(int i = 0; i < multipliers.size(); i++){
        if(multipliers[i] != 0){
            checkZero = false;
        }
    }
    if(!checkZero){
        matrix = rowOps(matrix,nCol,multipliers);
        pivots.push_back(matrix);
    }
  }
  matrix = regressiveSust(matrix,times,indexes);
  pivots.push_back(matrix);
  return pivots;
}

int main (){
  string filename;
  cout << "Enter filename with matrix separated by spaces" <<endl; 
  cin >> filename;
  vector<vector<double>> matrix = parseMatrix(filename);
  vector<vector<vector<double>>> result = gaussTotal(matrix);
  writeTable(result);
}


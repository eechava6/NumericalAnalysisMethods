#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "utils.h"


using namespace std;

vector<vector<vector<double>>> gaussSimple(vector<vector<double>> matrix){
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
      if(matrix[nCol][nCol] == 0.0){
        int index;
        for(int i = nCol; i < matrix.size(); i++){
          if(matrix[i][nCol] != 0){
            index = i;
            break;
          }
        }
        matrix[nCol].swap(matrix[index]);
        //Needs validation ------------------------------------------------
        int temInd = indexes[nCol];
        indexes[nCol] = indexes[index];
        indexes[index] = temInd;
        vector<vector<double>> temp =matrix; 
        pivots.push_back(temp);
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
  /*string filename;
  cout << "Enter filename with matrix separated by spaces" <<endl; 
  cin >> filename;*/
  vector<vector<double>> matrix = parseMatrix("input.txt");
  vector<vector<vector<double>>> result = gaussSimple(matrix);
  writeTable(result);
}


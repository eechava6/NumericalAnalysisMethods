#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "utils.h"


using namespace std;

vector<vector<vector<double>>> gaussSimple(vector<vector<double>> matrix){
  vector<vector<vector<double>>> pivots; 
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
  for(int nCol = 0; nCol < 1; nCol++){//remember put again times
      if(matrix[nCol][nCol] == 0){
        //do something
        true;
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
  return pivots;
}

/*
  times = A[:,0].size-1
  indexes = np.arange(0,times+1)
*/

int main (){
  /*string filename;
  cout << "Enter filename with matrix separated by spaces" <<endl; 
  cin >> filename;*/
  vector<vector<double>> matrix = parseMatrix("input.txt");
  vector<vector<vector<double>>> result = gaussSimple(matrix);
  writeTable(result);
}


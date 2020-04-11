#include "utils.h"

vector<double> split(string &s, char delim) {
    vector<double> result;
    stringstream ss (s);
    string item;
    while (getline (ss, item, delim)) {
        result.push_back(stod(item));
    }
    return result;
}

vector<vector<double>> parseMatrix(string filename) {
  ifstream file(filename);
  string str;
  char delim = ' ';
  vector<vector<double>> matrix;
  while (getline(file, str)) {
    vector<double> row = split(str,delim);
    matrix.push_back(row);
  }
  return matrix;
}

void writeTable(vector<vector<vector<double>>> matrix){
  ofstream outfile;
  outfile.open("out.txt", ios::app);
  vector<vector<double> >::iterator row;
  vector<double>::iterator col;
  vector<vector<vector<double>>>::iterator step;
  
  for(step = matrix.begin(); step != matrix.end(); step++){
      for (row = step->begin(); row != step->end(); row++) {
        for (col = row->begin(); col != row->end(); col++) {
            outfile << *col << ' ';
        }
      outfile << endl;
    }
    outfile << endl;
  }

}

void helpWrite(vector<vector<double>> matrix){
  ofstream outfile;
  outfile.open("help.txt", ios::app);
  vector< vector<double> >::iterator row;
  vector<double>::iterator col;

      for (row = matrix.begin(); row != matrix.end(); row++) {
        for (col = row->begin(); col != row->end(); col++) {
            outfile << *col << ' ';
        }
      outfile << endl;
      }
}

void helpCout(vector<double> vect){
  for(int i = 0; i < vect.size(); i++){
    cout << vect[i] << endl;
  }
  cout << "end" <<endl;
}

bool isSquared(vector<vector<double>> matrix){
  int rows = matrix[0].size();
  int columns = matrix.size();
  if(rows == columns+1){
    return true;
  }
  return false;
}

vector<vector<double>> transpose(vector<vector<double>> matrix){
    vector<vector<double> > trans_vec(matrix[0].size(), vector<double>());
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[i].size(); j++){
            trans_vec[j].push_back(matrix[i][j]);
        }
    }
    return trans_vec;    // <--- reassign here
}

vector<vector<double>> regressiveSust(vector<vector<double>> matrix, int n, vector<double> indexes){
    vector<vector<double>> solutions;
    double sum; 
    double xi;
    for(int i  = n; i >= 0; i--){
      sum = 0;
      for(int y = i+1; y <= n; y++){
        sum = sum + matrix[i][y] * solutions[n-y][1];
      }
      xi = (matrix[i][n+1] - sum)/matrix[i][i];
      solutions.push_back({indexes[i],xi});
    }
    
    return solutions;
}

vector<double> getMultipliers(vector<vector<double>> matrix, int nCol){
    vector<vector<double>> mTrans = transpose(matrix);
    vector<double> col = mTrans[nCol];
    vector<double> multipliers;
    for(int i = nCol+1; i < col.size(); i++){
      double value = col[i]/col[nCol];
      multipliers.push_back(value);
    }
    return multipliers;
}

vector<vector<double>> getSubM(vector<vector<double>> matrix, int start, int stop){
  vector<vector<double>> result;
  for (int i = start; i < stop; i++){
     result.push_back(matrix[i]);
  }
  return result;
}

vector<vector<double>> broadcastOpt(vector<vector<double>> matrix, vector<double> values){
    vector<vector<double>> result;
    vector<double> temp;
    for(int i = 0; i < matrix.size(); i++){
      for(int y = 0; y < matrix[i].size(); y++){
            temp.push_back(matrix[i][y]*values[i]);  
      }
      result.push_back(temp);
      temp.clear();
    }
    return result;
}

vector<vector<double>> matrixSub(vector<vector<double>> matrix, vector<vector<double>> b){
    vector<vector<double>> result;
    vector<double> temp;
    for(int i = 0; i < matrix.size(); i++){
      for(int y = 0; y < matrix[i].size(); y++){
            temp.push_back(matrix[i][y]-b[i][y]);
      }
      result.push_back(temp);
      temp.clear();
    }
    return result;
}

vector<vector<double>> rowOps(vector<vector<double>> matrix, int nCol, vector<double> multipliers){
    vector<vector<double>> pivotM;
    for(int i = 0; i < matrix.size()-1-nCol; i++){
      pivotM.push_back(matrix[nCol]);
    }
    vector<vector<double>> mMatrix = broadcastOpt(pivotM, multipliers); //broadcast multipliers * pivtM
    vector<vector<double>> subM = getSubM(matrix,nCol+1,matrix.size());
    subM = matrixSub(subM,mMatrix);
    //Add upper part of matrix
    for(int i = nCol; i >= 0 ; i--){
      subM.insert(subM.begin(),matrix[i]);
    }
    return subM;
}


int calcDeterminant(vector<vector<double>> Matrix){
        int det = 0;
        if (Matrix.size() == 1){
            return Matrix[0][0]; // no calculation needed
        }
        else if (Matrix.size() == 2){
            //in this case we calculate the determinant of a 2-dimensional matrix in a 
            //default procedure
            det = (Matrix[0][0] * Matrix[1][1] - Matrix[0][1] * Matrix[1][0]);
            return det;
        }
        else{
            //order greater than 2
            for (int p = 0; p < Matrix[0].size(); p++){
                // form a matrix from the rest of the elements in the matrix
                vector<vector<double>> TempMatrix; // to hold the shaped matrix;
                for (int i = 1; i < Matrix.size(); i++){
                    // iteration will start from row one cancelling the first row values
                    vector<double> TempRow;
                    for (int j = 0; j < Matrix[i].size(); j++){
                        //value that match p column
                        if (j != p){
                           TempRow.push_back(Matrix[i][j]);//add current cell to TempRow 
                        }
                    }
                    if (TempRow.size() > 0)
                        TempMatrix.push_back(TempRow);
                    //after adding each row of the new matrix to the vector tempx
                    //we add it to the vector temp which is the vector where the new 
                    //matrix will be formed
                }
                det = det + Matrix[0][p] * pow(-1, p) * calcDeterminant(TempMatrix);
                //calculate the value of determinant by using a recursive way
            }
            return det;
        }
}

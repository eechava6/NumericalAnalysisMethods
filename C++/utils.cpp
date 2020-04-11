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
      outfile << endl << endl;
      }
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

vector<vector<double>> broadcastMul(vector<vector<double>> matrix, vector<double> values){
    vector<vector<double>> result;
    vector<double> temp;
    for(int i = 0; i < matrix.size(); i++){
      for(int y = 0; y < matrix[i].size(); y++){
          temp.push_back(matrix[i][y]*values[y]);
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
    vector<vector<double>> mMatrix = broadcastMul(pivotM, multipliers); //broadcast multipliers * pivtM
    helpWrite(mMatrix);
    vector<vector<double>> result; // Encajamos con la parte restante de la matriz
    return result;
}


int calcDeterminant(vector<vector<double>> Matrix){
        //this function is written in c++ to calculate the determinant of matrix
        // it's a recursive function that can handle matrix of any dimension
        int det = 0; // the determinant value will be stored here
        if (Matrix.size() == 1)
        {
            return Matrix[0][0]; // no calculation needed
        }
        else if (Matrix.size() == 2)
        {
            //in this case we calculate the determinant of a 2-dimensional matrix in a 
            //default procedure
            det = (Matrix[0][0] * Matrix[1][1] - Matrix[0][1] * Matrix[1][0]);
            return det;
        }
        else
        {
            //in this case we calculate the determinant of a squared matrix that have 
            // for example 3x3 order greater than 2
            for (int p = 0; p < Matrix[0].size(); p++)
            {
                //this loop iterate on each elements of the first row in the matrix.
                //at each element we cancel the row and column it exist in
                //and form a matrix from the rest of the elements in the matrix
                vector<vector<double>> TempMatrix; // to hold the shaped matrix;
                for (int i = 1; i < Matrix.size(); i++)
                {
                    // iteration will start from row one cancelling the first row values
                    vector<double> TempRow;
                    for (int j = 0; j < Matrix[i].size(); j++)
                    {
                        // iteration will pass all cells of the i row excluding the j 
                        //value that match p column
                        if (j != p)
                        {
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
                //then we calculate the value of determinant by using a recursive way
                //where we re-call the function by passing to it the new formed matrix
                //we keep doing this until we get our determinant
            }
            return det;
        }
}

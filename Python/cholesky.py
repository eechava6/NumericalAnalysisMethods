from math import sqrt
from pprint import pprint
import numpy as np


#Cholesky
def cholesky(A):
    rows = len(A)
    columns = len(A[0])
    Z = np.zeros((rows,1), float)
    X = np.zeros((rows, 1), float)
    #X = np.array([[1],[1],[1],[1]])
    #Z = np.array([[1,1,1,1],[1,1,1,1],[1,1,1,1],[1,1,1,1]])
    L = np.zeros((rows,columns), float)
    U = np.zeros((rows,columns), float)

    b = np.array([[1],[1],[1],[1]])
    
    #L = np.zeros((rows,columns), float)
    #print(L)

    for k in range(0, rows):
        suma = 0.0
        for p in range(0, k):
            suma = suma + L[k][p]*U[p][k]
        L[k][k] = sqrt(A[k][k] - suma)
        U[k][k] = L[k][k]

        for i in range(k, rows):
            suma = 0
            for p in range(0, k):
                suma = suma + L[i][p]*U[p][k]
            L[i][k] = (A[i][k] - suma)/L[k][k]

        for j in range(k, rows):
            suma = 0
            for p in range(0, k):
                suma = suma + L[k][p]*U[p][j]
            U[k][j] = (A[k][j] - suma)/L[k][k]
    
    Lb = np.concatenate([L, b], axis=1)

    for i in range(0, rows):
        suma = 0
        for p in range(0, i):
            suma = suma + Lb[i][p]*Z[p][0]
        Z[i][0] = (Lb[i][rows] - suma)/Lb[i][i]

    Lu = np.concatenate([U, Z], axis=1)

    for i in range(rows-1,-1, -1):
        suma = 0
        for p in range(i, rows):
            suma = suma + Lu[i][p]*X[p]
        X[i] = (Lu[i][rows] - suma)/Lu[i][i]

    

    return L, U, Z, X
 
if __name__ == "__main__":   
    A = [[4, -1, 0, 3], [1, 15.5, 3, 8], [0, -1.3, -4, 1.1],[14, 5, -2, 30]]
    C = [[5,4,3,2], [2,4,1,1], [3,4,5,1],[2,3,3,7]]
    #[4, -1, 0, 3; 1, 15.5, 3, 8; 0, -1.3, -4, 1.1; 14, 5, -2, 30]
    if((np.all(np.linalg.eigvals(C) > 0) == True)):
        L,U, Z, X = cholesky(C)
        print ("A:")
        pprint(C)

        print ("L:")
        pprint(L)
        print("U: ")
        pprint(U)
        print("X: ")
        print(X)
        print("Z: ")
        print(Z)
    else:
        print("La matriz no se puede operar, pues no esta definida positivamente.")


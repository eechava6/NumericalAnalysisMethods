import numpy as np

def doolittle(A, n, b):
    U = np.zeros((n,n))
    L = np.eye(n, dtype=float)
    diag=1
    Z = np.zeros((n,1), float)
    X = np.zeros((n,1), float)

#    L,U = inicializa(n,0)
    for k in range(n):
        suma1 = 0
        for p in range(0,k):
            suma1 += L[k][p]*U[p][k]
        U[k][k] = A[k][k]-suma1
        for i in range(k+1,n):
            suma2 = 0
            for p in range(k):
                suma2 += L[i][p]*U[p][k]
            L[i][k] = (A[i][k]-suma2)/float(U[k][k])
        for j in range(k+1,n):
            suma3 = 0
            for p in range(k):
                suma3 += L[k][p]*U[p][j]
            U[k][j]= (A[k][j]-suma3)/float(L[k][k])
        #imprimir L  U y k etapa
        print("Etapa: ", k)
        print("L: ")
        print(L)
        print("U: ")
        print(U)

    Lb = np.concatenate([L, b], axis=1)
    for i in range(0,n):
        diag = diag*U[i][i]
    if(diag != 0):
        for i in range(0, n):
            suma = 0
            for k in range(0, n):
                suma = suma+Lb[i][k]*Z[k][0]
            Z[i][0] = (Lb[i][n] - suma)/Lb[i][i]
        Uz = np.concatenate([U, Z], axis = 1)
        for i in range(n-1,-1, -1):
            suma = 0
            for k in range(0, n):
                suma = suma+Uz[i][k]*X[k][0]
            X[i][0] = (Uz[i][n] - suma)/Uz[i][i]       
    else:
        print("El sistema no tiene solucion o tiene infinitas soluciones pues det = 0")
    print("FInal -------------------------------------------")
    print("L:")
    print(L)
    print("=================================================")
    print("U:")
    print(U)
    print("X: ")
    print(X)
    print("Z: ")
    print(Z)

    return L,U

a = [[4, -1, 0, 3],
     [1, 15.5, 3, 8],
     [0, -1.3, -4, 1.1],
     [14, 5, -2, 30]]
n = len(a)
b = np.array([[1],[1],[1],[1]])
print(n)
doolittle(a, n, b)


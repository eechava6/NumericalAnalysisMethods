import numpy as np
import ast
import json
def gaussSeidel(A, b, x, norm, tol, iteMax):
    A = ast.literal_eval(A)
    b = ast.literal_eval(b)
    x = ast.literal_eval(x)
    result = {}
    iters = []
    D = np.diag(np.diag(A))
    L = (-1 * np.tril(A))+D
    U = (-1 * np.triu(A))+D
    if(0 in np.diag(A)): return {"status" : "diagonal has 0", "error" : True}
    ite = 0
    #Change here for jacobi, Sor and Gauss seidel
    T = np.dot(np.linalg.inv(D-L), U)
    C = np.dot(np.linalg.inv(D-L),b)
    #End changes
    spectRad = np.max(np.absolute(np.linalg.eigvals(T)))
    if(spectRad > 1): return {"status" : "spectral radious > 1", "error" : True}
    #Saving into result dict
    result['TMatrix'] = json.dumps(T.tolist())
    result['CMatrix'] = json.dumps(C.tolist())
    result['SpectRad'] = spectRad

    iters.append({ "iter" : ite, "E" : "n/a", "x" : x})
    #End savings
    while(norm > tol and ite < iteMax):
        xold = x
        x = np.dot(T,xold)+C
        norm = np.linalg.norm(xold-x)
        ite += 1
        #Saving into iters
        iters.append({"iter": ite, "E": float(norm), "x": x.tolist()})
        #End saving
    result['iters'] = iters
    result['error'] = False
    return result

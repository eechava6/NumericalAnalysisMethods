
import numpy as np
import pandas as pd
from utils import regresiveSustitution
from utils import rowOps
from utils import getMultipliers
from utils import swapRows

def partialPivot(A):
    pivots = []
    A = np.array(A).astype(float)
    times = A[:,0].size-1
    pivots.append(A.copy())
    indexes = np.arange(0,times+1)
    for nCol in range(0,times):
        absCol = np.absolute(A[nCol:,nCol])
        mVal = np.amax(absCol)
        if(mVal == 0):
            pivots.append({'status':'This matrix has no solution!'})
            return pivots
        #Validates if there a is biggest number than A[i][i] and swap rows
        if(A[nCol][nCol] < mVal):
            mInd = np.argmax(absCol)
            A,indexes = swapRows(A,nCol,mInd,indexes) 
            pivots.append(A)
        multipliers = getMultipliers(A,nCol)
        #Validates if any multiplier is different to zero
        if(not np.count_nonzero(multipliers) == 0):
            A = rowOps(A,nCol,multipliers)
            pivots.append(A)
    values = regresiveSustitution(pivots[-1],times,indexes)
    pivots.append(values)
    return pivots
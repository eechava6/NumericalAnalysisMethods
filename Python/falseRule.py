from function import f
import numpy as np
import math

def falseRule (xi,xs,tol,max_iter):
    xr = evaluateFunction(xi,xs)
    f_xr = f(xr)
    return_list = []
    return_list.append({
            'iter': 0,
            'xi': xi,
            'xs' : xs,
            'xr': xr,
            'f(xr)': f_xr,
            'error':'NA'
            })
    count = 1
    error = tol + 1 
    while error > tol and count <= max_iter:
        xi = xr if (f_xr < 0) else xi
        xs = xr if (f_xr > 0) else xs
        tempXr = xr
        xr = evaluateFunction( xi, xs)
        error = abs(xr - tempXr)
        f_xr = f(xr)
        
        row = {
            'iter' : count,
            'xi': xi,
            'xs' : xs,
            'xr': xr,
            'f(xr)': f_xr,
            'error': error
            }
        return_list.append(row)
        if(f_xr == 0):
            return_list.append({'status':'Root found! ;)'})
            return return_list
        elif(error < tol):
            return_list.append({'status':'Err lower than tolerance! :)'})
            return return_list
        elif(count >= max_iter):
            return_list.append({'status':'Overpassed max iteration! :('})
            return return_list
        count = count + 1

    return return_list

def evaluateFunction(xi,xs):
    return xi - ((f(xi)*(xs-xi))/(f(xs)-f(xi)))



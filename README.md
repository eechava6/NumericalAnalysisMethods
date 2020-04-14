# NumericalAnalysis
Numerical methods seen in the subject "Análisis númerico" 

## How to use

### C++

* Inside the folder C++, you have compile the source file for the method you want to use with the following command: 

**Note :** If you're using a method which uses matrix, you have to **add utils.cpp** to compilation, if you are using table methods, **add function.cpp**, for table methods remember to set the function in the **function.cpp** file.

`
g++ {method.cpp} {utils.cpp | function.cpp}
`
It will generate a file named `a.out`, to execute in Unix systems use: 

`
./a.out
`
### Python

* Inside the folder Python, there is a file named **Main.py**, this methods logs a user-friendly function to determine which method will you use and ask for the parameters, to run the main use the following code:

`
python3 main.py
`

**Note :** to set the function remember to change the file **function.py** where f(x) stands for the function, df(x), the first derivative, ddf(x) the second derivative and g(x) for the g used in newton method. 

**You must have installed python3 since we are using some fresh syntax sugars**


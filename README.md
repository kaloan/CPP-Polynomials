# CPP-Polynomials

A small class that implements polynomials in C++. <br>
Polynomial<CoefC, ValC> is considered a polynomial with coefficients of type CoefC and may be evaluated on values of type ValC. <br>
main is used for example usage. <br>
Assumes that the operator CoefC\*ValC is defined. <br>
For nonfloating values assumes that ValC(1) is a constructor for the unit of ValC. <br>
Horner's method is added, which is a quicker way to calculate than naively, although standard method could use memoization of lower powers. <br>

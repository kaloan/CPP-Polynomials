#include "Polynomial.cpp"
#include <math.h>
using namespace std;

int main()
{
	map<unsigned int, double> initP;
	initP[0] = 2.0;
	initP[1] = 1.0;
	Polynomial<double, double> p(initP);
	cout << p.at(1.0) << " " << p.at(50.0) << endl;

	Polynomial<int, int> intPoly;
	intPoly[2] = 4;
	intPoly[5] = 2;
	cout << intPoly.at(-2) << endl;

	for (const auto& c : intPoly.getCoeffs())
	{
		cout << "Pow " << c.first << ": " << c.second << endl;
	}

	intPoly.print();

	cout << intPoly.coeffOfPow(2) << endl;
	//The following would throw exception
	//cout << intPoly.coeffOfPow(5) << endl;
	
	cout << "Is p full coefficients? " << p.isFull() << endl;

	intPoly[4] = 3;
	cout << "Is intPoly full coefficients? " << intPoly.isFull() << endl; 
	
	intPoly.makeFull();
	cout << "After filling coeffs for intPoly: ";
	intPoly.print();
	
	cout << "intPoly(2) by horner: " << intPoly.horner(2) << endl;


	//You can define your own approximations to analytic functions
	Polynomial<double, double> myCos;
	double facts = 1;
	for (unsigned int i = 0; i < 20; i += 2)
	{
		myCos[i] = 1 / facts;
		facts *= - (int)((i + 1) * (i + 2));
	}
	cout << "Built in cos: " << cos(1) << " vs my cos: " << myCos.at(1) << endl;


	
	map<unsigned int, double> initProd;
	for (auto& monom : intPoly.getCoeffs())
	{
		initProd[monom.first] = static_cast<double>(monom.second);
	}
	Polynomial<double, double> doubleIntPoly(initProd);
	Polynomial<double, double> prod;
	prod = p * doubleIntPoly;

	cout << "The product of p and intPoly is: ";
	prod.print();

	cout << "Is the product equal to p?: " << (p == prod) << endl;
	cout << "Does p equal itself? " << (p == p) << endl;
	cout << "Does prod grow quicker than p? " << (p < prod) << endl;

	cout << "The sum of p and intPoly is: ";
	(p + doubleIntPoly).print();
	doubleIntPoly += p;
	doubleIntPoly.print();

	cout << "Negative p is equal to: ";
	(-p).print();

	//Results in compiler error and doesn't even throw exception
	/*Polynomial<string, int> showThrow;
	showThrow[4] = 15;
	showThrow[20] = 2;
	try
	{
		showThrow = -showThrow;
	}
	catch (domain_error& probWithCoeffType)
	{
		cout << probWithCoeffType.what() << endl;
	}*/

	cin.get();
	return 0;
}
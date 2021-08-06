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
	intPoly[1] = 4;
	intPoly[2] = 2;
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
	cout << "Build in cos: " << cos(1) << " vs my cos: " << myCos.at(1) << endl;

	cin.get();
	return 0;
}
#include "Polynomial.cpp"
using namespace std;

int main()
{
	map<unsigned int, double> initP;
	initP[0] = 2.0;
	initP[1] = 1.0;
	Polynomial<double, double> p(initP);
	cout << p.at(1.0) << " " << p.at(50.0);

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
	
	cout << intPoly.horner(2);

	cin.get();
	return 0;
}
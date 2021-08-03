#pragma once
#include <map>

template <class CoefC, class ValC>
class Polynomial
{
private:
	//Key is the power, value is the coefficient
	std::map<unsigned int, CoefC> coeffs;

public:
	Polynomial();
	Polynomial(const std::map<unsigned int, CoefC>&);

	std::map<unsigned int, CoefC> getCoeffs() const noexcept;

	//Calls coeffs.at() and copies the value so may throw exception
	constexpr CoefC coeffOfPow(const unsigned int&) const;

	//Requires a unitary constructor for the ValC class that creates a unit when passed the int value 1
	constexpr ValC at(const ValC&) const noexcept;
	void print() const noexcept;

	constexpr CoefC& operator[](const unsigned int&);
};
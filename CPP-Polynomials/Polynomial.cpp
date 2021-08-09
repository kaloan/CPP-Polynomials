#include "Polynomial.h"
#include <iostream>
#include <math.h>
#include <complex>
#include <type_traits>

template<class CoefC, class ValC>
inline Polynomial<CoefC, ValC>::Polynomial() noexcept
{
}

template<class CoefC, class ValC>
inline Polynomial<CoefC, ValC>::Polynomial(const std::map<unsigned int, CoefC>& givenCoeffs) noexcept : coeffs(givenCoeffs)
{
}

template<class CoefC, class ValC>
inline Polynomial<CoefC, ValC>::Polynomial(const Polynomial &otherPolynomial) noexcept : coeffs(otherPolynomial.coeffs)
{
}

template<class CoefC, class ValC>
inline Polynomial<CoefC, ValC>::Polynomial(Polynomial &&otherPolynomial) noexcept : coeffs(std::move(otherPolynomial.coeffs))
{
}

template<class CoefC, class ValC>
constexpr bool Polynomial<CoefC, ValC>::isFull() const noexcept
{
	if (!coeffs.size()) return true;
	const unsigned int maxPower = coeffs.rbegin()->first;
	for (unsigned int i = 0; i <= maxPower; ++i)
	{
		try
		{
			coeffs.at(i);
		}
		catch (const std::exception& noSuchPower)
		{
			return false;
		}
	}
	return true;
}

template<class CoefC, class ValC>
constexpr void Polynomial<CoefC, ValC>::makeFull() noexcept
{
	if (!coeffs.size()) return;
	const unsigned int maxPower = coeffs.rbegin()->first;

	//If the key didn't exist before it inserts it with value CoefC()
	for (unsigned int i = 0; i < maxPower; ++i)	coeffs[i];
}

template<class CoefC, class ValC>
inline constexpr std::map<unsigned int, CoefC> Polynomial<CoefC, ValC>::getCoeffs() const noexcept
{
	return std::map<unsigned int, CoefC>(coeffs);
}

template<class ValC>
ValC iter_pow(ValC base, unsigned int exponent)
{
	ValC res = ValC(1);

	//Allows logarithmic number of steps for exponentiation
	while (exponent)
	{
		//if exponent % 2
		if (exponent & 1) res *= base;
		//exponent = exponent / 2;
		exponent = exponent >> 1;
		base *= base;
	}

	return res;
}

template<class CoefC, class ValC>
inline constexpr CoefC Polynomial<CoefC, ValC>::coeffOfPow(const unsigned int& pow) const
{
	return coeffs.at(pow);
}


template<class CoefC, class ValC>
constexpr ValC Polynomial<CoefC, ValC>::at(const ValC& atVal) const noexcept
{
	ValC res = ValC();
	unsigned int lastPow = 0;
	ValC lastPowerValue = ValC(1);

	for (const auto& monom : coeffs)
	{
		if constexpr (std::is_floating_point_v<ValC> || std::is_same<ValC, std::complex<float>>::value || std::is_same<ValC, std::complex<double>>::value || std::is_same<ValC, std::complex<long double>>::value)
		{
			lastPowerValue = pow(atVal, monom.first - lastPow) * lastPowerValue;
			res += monom.second * lastPowerValue;
		}
		else
		{
			lastPowerValue = iter_pow(atVal, monom.first - lastPow) * lastPowerValue;
			res += monom.second * lastPowerValue;
		}
		lastPow = monom.first;
	}

	return res;
}

template<class CoefC, class ValC>
constexpr ValC Polynomial<CoefC, ValC>::horner(const ValC &atVal) const noexcept
{
	if (coeffs.size() == 0) return ValC();
	else if (coeffs.size() == 1) return at(atVal);
	
	//We utilise the fact that coeffs is an ordered map

	/*
	auto prevPower = coeffs.rbegin();
	ValC res = prevPower->second;
	++prevPower;

	for (auto monom = coeffs.rbegin(); prevPower != coeffs.rend(); )
	{
		//Not sure if the left one will be evaluated before the right one
		//res = monom->second*res + (++monom)->second;
		res = atVal*res + prevPower->second;
		monom = prevPower;
		++prevPower;
	}
	*/

	ValC res = coeffs.rbegin()->second;
	ValC unit = ValC(1);
	for (auto monom = coeffs.rbegin(); monom->first != 0; )
	{
		//Save a multiplication for the default arithmetics
		if constexpr (std::is_arithmetic_v<ValC>) res = atVal * res + (++monom)->second;
		else res = atVal * res + (++monom)->second * unit;
	}
	
	return res;
}

template<class CoefC, class ValC>
void Polynomial<CoefC, ValC>::print() const noexcept
{
	bool first = true;
	for (const auto& monom : coeffs)
	{
		if (!first)	std::cout << " + ";
		std::cout << monom.second;
		std::cout << "x^";
		std::cout << monom.first;
		first = false;
	}
	std::cout << std::endl;
}

template<class CoefC, class ValC>
inline constexpr CoefC & Polynomial<CoefC, ValC>::operator[](const unsigned int &pow)
{
	return coeffs[pow];
}

template<class CoefC, class ValC>
Polynomial<CoefC, ValC>& Polynomial<CoefC, ValC>::operator=(const Polynomial<CoefC, ValC>& otherPolynomial) noexcept
{
	if (this != &otherPolynomial) coeffs = otherPolynomial.coeffs;
	return *this;
}

template<class CoefC, class ValC>
Polynomial<CoefC, ValC>& Polynomial<CoefC, ValC>::operator=(Polynomial<CoefC, ValC>&& otherPolynomial) noexcept
{
	coeffs = std::move(otherPolynomial.coeffs);
	return *this;
}

template<class CoefC, class ValC>
Polynomial<CoefC, ValC> Polynomial<CoefC, ValC>::operator+(const Polynomial<CoefC, ValC>& otherPolynomial) const noexcept
{
	Polynomial<CoefC, ValC> res = *this;
	//Use [] on the coeffs, because we defined Polynomial[] by coeffs.at()
	for (auto& monom : otherPolynomial.coeffs) res.coeffs[monom.first] += monom.second;
	return res;
}

template<class CoefC, class ValC>
Polynomial<CoefC, ValC> Polynomial<CoefC, ValC>::operator-(const Polynomial<CoefC, ValC>& otherPolynomial) const noexcept
{
	Polynomial<CoefC, ValC> res = *this;
	//Use [] on the coeffs, because we defined Polynomial[] by coeffs.at()
	for (auto& monom : otherPolynomial.coeffs) res.coeffs[monom.first] -= monom.second;
	return res;
}

template<class CoefC, class ValC>
Polynomial<CoefC, ValC> Polynomial<CoefC, ValC>::operator*(const Polynomial<CoefC, ValC>& otherPolynomial) const noexcept
{
	std::map<unsigned int, ValC> resMap;

	for (auto& thisMonom : this->coeffs)
	{
		for (auto& otherMonom : otherPolynomial.coeffs)
		{
			resMap[thisMonom.first+otherMonom.first] += thisMonom.second*otherMonom.second;
		}
	}

	return Polynomial<CoefC, ValC>(resMap);
}

template<class CoefC, class ValC>
Polynomial<CoefC, ValC>& Polynomial<CoefC, ValC>::operator+=(const Polynomial<CoefC, ValC>& otherPolynomial) noexcept
{
	*this = std::move(*this + otherPolynomial);
	return *this;
}

template<class CoefC, class ValC>
Polynomial<CoefC, ValC>& Polynomial<CoefC, ValC>::operator*=(const Polynomial<CoefC, ValC>& otherPolynomial) noexcept
{
	*this = std::move(*this * otherPolynomial);
	return *this;
}

template<class CoefC, class ValC>
Polynomial<CoefC, ValC>& Polynomial<CoefC, ValC>::operator-()
{
	try
	{
		for (auto& monom : coeffs)
		{
			coeffs[monom.first] = -coeffs[monom.first];
		}
	}
	catch (const std::exception& unsignedException)
	{
		throw std::domain_error("Cannot change sign of unsigned coefficients or undeclared unary- for coefficient type.");
	}
	return *this;
}

template<class CoefC, class ValC>
constexpr bool Polynomial<CoefC, ValC>::operator==(const Polynomial<CoefC, ValC>& otherPolynomial) const noexcept
{
	if (this == &otherPolynomial) return true;
	return (coeffs == otherPolynomial.coeffs);
}

template<class CoefC, class ValC>
constexpr bool Polynomial<CoefC, ValC>::operator<(const Polynomial<CoefC, ValC>& otherPolynomial) const noexcept
{
	if (coeffs.empty()) return false;
	else if (otherPolynomial.coeffs.empty()) return true;

	unsigned int thisMaxPower = coeffs.rbegin()->first;
	unsigned int otherMaxPower = otherPolynomial.coeffs.rbegin()->first;
	return (thisMaxPower < otherMaxPower) || (thisMaxPower == otherMaxPower && coeffs.at(thisMaxPower) < otherPolynomial.coeffs.at(otherMaxPower));
}

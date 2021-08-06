#include "Polynomial.h"
#include <iostream>
#include <math.h>
#include <complex>
#include <type_traits>

template<class CoefC, class ValC>
inline Polynomial<CoefC, ValC>::Polynomial()
{
}

template<class CoefC, class ValC>
inline Polynomial<CoefC, ValC>::Polynomial(const std::map<unsigned int, CoefC>& givenCoeffs)
{
	coeffs = givenCoeffs;
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
inline std::map<unsigned int, CoefC> Polynomial<CoefC, ValC>::getCoeffs() const noexcept
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
	for (auto monom = coeffs.rbegin(); monom->first != 0; )
	{
		//Save a multiplication for the default arithmetics
		if constexpr (std::is_arithmetic_v<ValC>) res = atVal * res + (++monom)->second;
		else res = atVal * res + (++monom)->second * ValC(1);
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

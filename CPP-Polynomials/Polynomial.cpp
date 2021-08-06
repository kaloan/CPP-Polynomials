#include "Polynomial.h"
#include <iostream>
#include <math.h>

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
	// TODO: insert return statement here
	return coeffs.at(pow);
}

template<class CoefC, class ValC>
constexpr ValC Polynomial<CoefC, ValC>::at(const ValC& atVal) const noexcept
{
	ValC res = ValC();
	//For optimisation:
	//Can store last x^i and use it to quicken calculation for x^(i+j)
	for (const auto& monom : coeffs)
	{
		if constexpr (std::is_same<ValC, float>::value || std::is_same<ValC, double>::value) res += monom.second * pow(atVal, monom.first);
		else res += monom.second * iter_pow(atVal, monom.first);
	}
	return res;
}

template<class CoefC, class ValC>
constexpr ValC Polynomial<CoefC, ValC>::horner(const ValC &atVal) const noexcept
{
	if (coeffs.size() == 0) return ValC();
	else if (coeffs.size() == 1) return at(atVal);
	
	//We utilise the fact that coeffs is an ordered map

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

	//Probably better for types with quick != calculation
	/*ValC res = coeffs.rbegin()->second;
	for (auto monom = coeffs.rbegin(); *monom != *coeffs.begin(); )
	{
		//Not sure if the left one will be evaluated before the right one
		//res = monom->second*res + (--monom)->second;
		res = atVal * res + (++monom)->second;
	}
	*/

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

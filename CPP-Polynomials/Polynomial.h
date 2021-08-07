#pragma once
#include <map>

template <class CoefC, class ValC>
class Polynomial
{
private:
	//Key is the power, value is the coefficient
	std::map<unsigned int, CoefC> coeffs;

public:
	inline Polynomial() noexcept;
	inline Polynomial(const std::map<unsigned int, CoefC>&) noexcept;
	inline Polynomial(const Polynomial&) noexcept;

	//Checks if it has coefficients for all powers
	constexpr bool isFull() const noexcept;

	//Inserts 0 coefficients for missing powers
	constexpr void makeFull() noexcept;

	inline constexpr std::map<unsigned int, CoefC> getCoeffs() const noexcept;

	//Calls coeffs.at() and copies the value so may throw exception
	inline constexpr CoefC coeffOfPow(const unsigned int&) const;

	//Requires a unitary constructor for the ValC class that creates a unit when passed the int value 1
	constexpr ValC at(const ValC&) const noexcept;

	//Works only on polynomial with full coefficients
	constexpr ValC horner(const ValC&) const noexcept;

	void print() const noexcept;

	inline constexpr CoefC& operator[](const unsigned int&);

	Polynomial<CoefC, ValC>& operator=(const Polynomial<CoefC, ValC>&) noexcept;
	Polynomial<CoefC, ValC>& operator=(Polynomial<CoefC, ValC>&&) noexcept;
	Polynomial<CoefC, ValC> operator+(const Polynomial<CoefC, ValC>&) const noexcept;
	Polynomial<CoefC, ValC> operator-(const Polynomial<CoefC, ValC>&) const noexcept;
	Polynomial<CoefC, ValC> operator*(const Polynomial<CoefC, ValC>&) const noexcept;
	Polynomial<CoefC, ValC>& operator+=(const Polynomial<CoefC, ValC>&) noexcept;
	Polynomial<CoefC, ValC>& operator*=(const Polynomial<CoefC, ValC>&) noexcept;
	Polynomial<CoefC, ValC>& operator-();

	constexpr bool operator==(const Polynomial<CoefC, ValC>&) const noexcept;
	constexpr bool operator<(const Polynomial<CoefC, ValC>&) const noexcept;
};
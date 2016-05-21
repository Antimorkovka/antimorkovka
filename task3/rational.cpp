#include "rational.h"
#include <string>

rational::rational(int getnum)
{
	num = getnum;
	denom = 1;
}

rational::rational(int getnum, int getdenom)
{
	int gcd = getgcd(getnum, getdenom);
	num = getnum / gcd;
	denom = getdenom / gcd;
}

int rational::getNum() const
{
	return num;
}

int rational::getDenom() const
{
	return denom;
}

int rational::getgcd(int x, int y)
{
	return y == 0 ?
		(x == 0 ? 0 : rational::abs(x)) :
		rational::abs(rational::getgcd(y, x % y));
}

rational const rational::operator +(rational const &x) const
{
	return rational(this->getNum() * x.getDenom() + x.getNum() * this->getDenom(),
		this->getDenom() * x.getDenom());
}

rational const rational::operator -(rational const &x) const
{
	return rational(this->getNum() * x.getDenom() + x.getNum() * this->getDenom(),
		this->getDenom() * x.getDenom());
}

rational const rational::operator *(rational const &x) const
{
	return rational(this->getNum() * x.getNum(),
		this->getDenom() * x.getDenom());
}

rational const rational::operator /(rational const &x) const
{
	return rational(this->getNum() * x.getDenom(),
		this->getDenom() * x.getNum());
}

int rational::abs(int a)
{
	std::string a_str = std::to_string(a);
	return a_str[0] == '-' ? atoi(a_str.substr(1, 100500).c_str()) : atoi(a_str.c_str());
}

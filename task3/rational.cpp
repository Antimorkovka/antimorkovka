#include "rational.h"

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
	if (x == 0) return y;
	return getgcd(y%x, x);
}

rational const rational::operator +(rational const &x) const
{
	return rational(this->getNum() * x.getDenom() + x.getNum() * this->getDenom(),
					this->getDenom * x.getDenom());
}

rational const rational::operator -(rational const &x) const
{
	return rational(this->getNum() * x.getDenom() + x.getNum() * this->getDenom(),
					this->getDenom * x.getDenom());
}

rational const rational::operator *(rational const &x) const
{
	return rational(this->getNum() * x.getNum(),
					this->getDenom * x.getDenom());
}

rational const rational::operator /(rational const &x) const
{
	return rational(this->getNum() * x.getDenom(),
					this->getDenom * x.getNum());
}

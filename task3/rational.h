#ifndef RATIONAL_H
#define RATIONAL_H

class rational
{
	int num;
	int denom;
	int getgcd(int, int);
	int abs(int);

public:
	rational(int);
	rational(int, int);
	int getNum() const;
	int getDenom() const;

	rational const operator +(rational const &x) const;
	rational const operator -(rational const &x) const;
	rational const operator *(rational const &x) const;
	rational const operator /(rational const &x) const;
};

#endif

#include "computator.h"

monomio calc_sumand(monomio b)
{
	monomio sumand;

	sumand.value = b.value;
	sumand.sign = -1 * b.sign;
	return sumand;
}

monomio calc_num(monomio sumand, monomio radicand, bool sum)
{
	monomio num;
	
	num.value = sumand.value * sumand.sign + radicand.value * radicand.sign * (sum ? 1 : -1);
	num.sign = -1;
	if (num.value < 0)
		num.value *= -1;
	else
		num.sign = 1;
	return num;
}

monomio calc_den(monomio a)
{
	monomio den;

	den.sign = a.sign;
	den.value = 2 * a.value;
	return den;
}

static monomio radicandleft(monomio b)
{
	monomio radicandl;

	radicandl.sign = 1;
	radicandl.value = b.value * b.value;
	return radicandl;
}

static monomio radicandright(monomio a, monomio c)
{
	monomio radicandr;

	radicandr.sign = a.sign * c.sign;
	radicandr.value = 4 * a.value * c.value;
	return radicandr;
}

monomio calc_radicand(monomio a, monomio b, monomio c)
{
	monomio radicand;
	monomio l, r;

	l = radicandleft(b);
	r = radicandright(a, c);
	radicand.value = l.value - r.value * r.sign;
	radicand.sign = -1;
	if (radicand.value < 0)
		radicand.value *= -1;
	else
		radicand.sign = 1;
	return radicand;
}

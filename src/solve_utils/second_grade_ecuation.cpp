#include "computator.h"

monomio calc_sumand(monomio b)
{
	monomio sumand;

	sumand.value_type = b.value_type;
	if (b.value_type == 'l')
		sumand.value.l = b.value.l;
	else
		sumand.value.d = b.value.d;
	sumand.sign = -1 * b.sign;
	return sumand;
}

monomio calc_num(monomio sumand, monomio radicand, bool sum)
{
	int t = 0;
	monomio num;
	
	if (sumand.value_type == 'l')
		t |= 1 << 1;
	if (radicand.value_type == 'l')
		t |= 1;

	switch (t)
	{
	case 0:
		num.value.d = sumand.value.d * sumand.sign + radicand.value.d * radicand.sign * (sum ? 1 : -1);
		num.value_type = 'd';
		num.value = check_type(num.value, num.value_type);
		break;
	case 1:
		num.value.d = sumand.value.d * sumand.sign + radicand.value.l * radicand.sign * (sum ? 1 : -1);
		num.value_type = 'd';
		num.value = check_type(num.value, num.value_type);
		break;
	case 2:
		num.value.d = sumand.value.l * sumand.sign + radicand.value.d * radicand.sign * (sum ? 1 : -1);
		num.value_type = 'd';
		num.value = check_type(num.value, num.value_type);
		break;
	case 3:
		num.value.l = sumand.value.l * sumand.sign + radicand.value.l * radicand.sign * (sum ? 1 : -1);
		num.value_type = 'l';
	}
	num.sign = -1;
	if (num.value_type == 'l' && signbit(num.value.l))
		num.value.l *= -1;
	else if (num.value_type == 'd' && signbit(num.value.d))
		num.value.d *= -1;
	else
		num.sign = 1;
	return num;
}

monomio calc_den(monomio a)
{
	monomio den;

	den.value_type = a.value_type;
	den.sign = a.sign;
	if (a.value_type == 'l')
		den.value.l = 2 * a.value.l;
	else
		den.value.d = 2 * a.value.d;
	den.value = check_type(den.value, den.value_type);
	return den;
}

static monomio radicandleft(monomio b)
{
	monomio radicandl;

	radicandl.value_type = b.value_type;
	radicandl.sign = 1;
	if (b.value_type == 'l')
		radicandl.value.l = b.value.l * b.value.l;
	else
		radicandl.value.d = b.value.d * b.value.d;
	return radicandl;
}

static monomio radicandright(monomio a, monomio c)
{
	monomio radicandr;
	int t = 0;
	if (a.value_type == 'l')
		t |= 1 << 1;
	if (c.value_type == 'l')
		t |= 1;

	radicandr.sign = a.sign * c.sign;
	switch (t)
	{
	case 0:
		radicandr.value.d = 4 * a.value.d * c.value.d;
		radicandr.value_type = 'd';
		break;
	case 1:
		radicandr.value.d = 4 * a.value.d * c.value.l;
		radicandr.value_type = 'd';
		radicandr.value = check_type(radicandr.value, radicandr.value_type);
		break;
	case 2:
		radicandr.value.d = 4 * a.value.l * c.value.d;
		radicandr.value_type = 'd';
		radicandr.value = check_type(radicandr.value, radicandr.value_type);
		break;
	case 3:
		radicandr.value.l = 4 * a.value.l * c.value.l;
		radicandr.value_type = 'l';
		break;
	}
	return radicandr;
}

monomio calc_radicand(monomio a, monomio b, monomio c)
{
	int t = 0;
	monomio radicand;
	monomio l, r;

	l = radicandleft(b);
	r = radicandright(a, c);
	if (l.value_type == 'l')
		t |= 1 << 1;
	if (r.value_type == 'l')
		t |= 1;

	switch(t)
	{
	case 0:
		radicand.value.d = l.value.d - r.value.d * r.sign;
		radicand.value_type = 'd';
		radicand.value = check_type(radicand.value, radicand.value_type);
		break;
	case 1:
		radicand.value.d = l.value.d - r.value.l * r.sign;
		radicand.value_type = 'd';
		radicand.value = check_type(radicand.value, radicand.value_type);
		break;
	case 2:
		radicand.value.d = l.value.l - r.value.d * r.sign;
		radicand.value_type = 'd';
		radicand.value = check_type(radicand.value, radicand.value_type);
		break;
	case 3:
		radicand.value.l = l.value.l - r.value.l * r.sign;
		radicand.value_type = 'l';
	}
	radicand.sign = -1;
	if (radicand.value_type == 'l' && signbit(radicand.value.l))
		radicand.value.l *= -1;
	else if (radicand.value_type == 'd' && signbit(radicand.value.d))
		radicand.value.d *= -1;
	else
		radicand.sign = 1;
	return radicand;
}

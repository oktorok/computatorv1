#include "computator.h"

static double myAbs(double num)
{
	if (num < 0)
		return (-1) * num;
	else
		return num;
}

long check_fast_sol(long num)
{
	long res = 1;

	while (res * res < num)
		res++;
	if (res * res == num)
		return res;
	return 0;
}

value_u mySqrt(value_u num, char &value_type)
{
	value_u res;
	double res_sqr;

	if (value_type == 'l' && (res.l = check_fast_sol(num.l)))
		return res;
	else
		res.d = 1;
	if (value_type == 'l')
	{
		while (res.d * res.d < num.l)
			res.d += 1;
		if (res.d * res.d > num.l)
			res.d -=1;
		while (myAbs(num.l - (res.d * res.d)) > SQR_ERR)
		{
			res_sqr = myPow(res.d, 2);
			res.d = (res_sqr * (6 * num.l + res_sqr) + num.l * num.l)/(4 * res.d * (res_sqr + num.l));
		}
	}
	else
	{
		while (res.d * res.d < num.d)
			res.d += 1;
		if (res.d * res.d > num.d)
			res.d -=1;
		while (myAbs(num.d - (res.d * res.d)) > SQR_ERR)
		{
			res_sqr = myPow(res.d, 2);
			res.d = (res_sqr * (6 * num.d + res_sqr) + myPow(num.d, 2))/(4 * res.d * (res_sqr + num.d));
		}		
	}
	value_type = 'd';
	return res;
}

#include "computator.h"

static double myAbs(double num)
{
	if (num < 0)
		return (-1) * num;
	else
		return num;
}

double check_fast_sol(double num)
{
	double res = 1;

	while (res * res < num)
		res++;
	return res;
}

double mySqrt(double num)
{
	double res;
	double res_sqr;

	res = check_fast_sol(num);
	if (res * res == num)
		return res;
	if (res * res > num)
		res -=1;
	if (!res)
	{
		while (res * res < num)
			res += 0.1;
		if (res * res > num)
			res -=0.1;
	}
	while (myAbs(num - (res * res)) > SQR_ERR)
	{
		res_sqr = res * res;
		res = (res_sqr * (6 * num + res_sqr) + num * num)/(4 * res * (res_sqr + num));
	}		
	return res;
}

#include "computator.h"

static float myAbs(float num)
{
	if (num < 0)
		return (-1) * num;
	else
		return num;
}
	
float mySqrt(float num)
{
	float res = 1;
	float res_sqr;

	while (res * res < num)
		res += 1;
	if (res * res > num)
		res -=1;
	while (myAbs(num - (res*res)) > SQR_ERR)
	{
		res_sqr = myPow(res, 2);
		res = (res_sqr * (6 * num + res_sqr) + myPow(num, 2))/(4 * res * (res_sqr + num));
	}
	return res;
}

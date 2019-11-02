#include "computator.h"

float myPow(float base, int exponent)
{
	float result = 1;
	if (base == 0)
		return (0);
	else if (exponent == 0)
		return (1);
	for (int i = 0; i < exponent; i++)
		result *= base;
	return (result);
}

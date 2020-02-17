#include "computator.h"

double take_value(int &i, string expresion)
{
	double val;
	size_t i2;
	
	val = stod(expresion.substr(i), &i2);
	i += (int)i2;
	return val;
}

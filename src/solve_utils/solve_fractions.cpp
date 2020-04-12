#include "computator.h"

vector<monomio> solve_fractions(vector<monomio> expresiones)
{
	vector<monomio>::iterator it1, it2;
	monomio num, *den;
	
	for (size_t i=1; i < expresiones.size(); i++)
	{
		if (expresiones[i].get_variable() == "/")
		{
			num = expresiones[i - 1];
			den = &expresiones[i + 1];
			den->value = num.value/den->value;
			if (num.value)
				den->sign *= num.sign;
			else
				den->sign = 1;
			it1 = expresiones.begin() + i - 1;
			it2 = it1 + 2;
			expresiones.erase(it1, it2);
			i--;
		}
	}
	return expresiones;
}

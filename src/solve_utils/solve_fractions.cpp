#include "computator.h"

vector<monomio> solve_fractions(vector<monomio> expresiones)
{
	vector<monomio>::iterator it1;
	monomio num, *den;

	for (size_t i=1; i < expresiones.size(); i++)
	{
		if (expresiones[i].get_variable() == "/")
		{
			num = expresiones[i - 1];
			den = &expresiones[i + 1];
			if (!den->value)
			{
				cout << "Division by zero not allowed" << endl;
				exit(-1);
			}
			den->value = num.value/den->value;
			if (num.value)
				den->sign *= num.sign;
			else
				den->sign = 1;
			it1 = expresiones.begin() + i - 1;
			expresiones.erase(it1);
			expresiones.erase(it1);
			i--;
		}
	}
	
	return expresiones;
}

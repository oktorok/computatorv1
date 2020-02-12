#include "computator.h"

vector<monomio> solve_fractions(vector<monomio> expresiones)
{
	vector<monomio>::iterator it1, it2;
	monomio num, *den;
	string t = "00";
	
	for (int i=1; i < expresiones.size(); i++)
	{
		if (expresiones[i].get_variable() == "/")
		{
			num = expresiones[i - 1];
			den = &expresiones[i + 1];
			t[0] = num.value_type;
			t[1] = den->value_type;
			den->value = check_division(num.value, num.value_type, den->value, den->value_type);
			if (num.value.l)
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

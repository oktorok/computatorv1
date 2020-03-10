#include "computator.h"

complex_solution_t create_complex(vector<monomio> complex)
{
	complex_solution_t res;

	if (complex.size() == 2)
	{
		res.real = complex[0].value * complex[0].sign;
		res.imaginary = complex[1].value * complex[1].sign;
		return res;
	}
	res.imaginary = complex[0].value * complex[0].sign;
	res.real = 0;
	return res;
}

#include "computator.h"

complex_solution_t create_complex(vector<monomio> complex)
{
	complex_solution_t res;

	res.imaginary_type = complex[0].value_type;
	res.imaginary = complex[0].value;
	if (complex.size() == 2)
	{
		res.real_type = complex[1].value_type;
		res.real = complex[1].value;
	}
	return res;
}

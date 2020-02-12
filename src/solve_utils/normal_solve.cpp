#include "computator.h"

output_t normal_solve(vector<monomio> ecuacion, output_t solution)
{
	value_u a, b, c;
	value_u sumand, radicand, den;
	
	ecuacion = move_indepterm(ecuacion);
	solution.steps.push_back(printer(ecuacion, NULL));
	return solution;

	
}

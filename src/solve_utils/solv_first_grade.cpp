#include "computator.h"

output_t solv_first_grade(vector<monomio> ecuacion, output_t solution, int flags)
{
	solution_t sol;

	if (ecuacion[0].value != 1)
	{
		ecuacion = go_div(ecuacion);		
		if (flags & STEPS)
			solution.steps.push_back(printer(ecuacion,NULL));
		ecuacion = solve_fractions(ecuacion);
		if (flags & STEPS)
			solution.steps.push_back(printer(ecuacion, NULL));
	}
	if (ecuacion[0].sign == -1)
	{
		ecuacion[2].sign *= -1;
		ecuacion[0].sign = 1;
        }
	sol.imaginary = false;
	sol.sol.real = ecuacion.back().value;
	solution.solutions.push_back(sol);
	return solution;
}



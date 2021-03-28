#include "computator.h"

output_t solv_first_grade(vector<monomio> ecuacion, output_t solution, int flags)
{
	solution_t sol;

	if (ecuacion[0].value != 1)
	{
		ecuacion = go_div(ecuacion);		
		if (flags & STEPS)
		{
			solution.guide.push_back("Solving Fractions:");
			solution.steps.push_back(printer(ecuacion));
		}
		ecuacion = solve_fractions(ecuacion);
		if (flags & STEPS)
		{
			solution.guide.push_back("Solution:");
			solution.steps.push_back(printer(ecuacion));
		}
	}
	if (ecuacion[0].sign == -1)
	{
		ecuacion[2].sign *= -1;
		ecuacion[0].sign = 1;
    }
	sol.imaginary = false;
	sol.sol.real = ecuacion.back().value;
	if (sol.sol.real)
		sol.sol.real *= ecuacion.back().sign;
	solution.solutions.push_back(sol);
	return solution;
}



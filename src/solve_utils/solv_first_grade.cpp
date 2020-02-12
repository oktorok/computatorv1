#include "computator.h"

output_t solv_first_grade(vector<monomio> ecuacion, output_t solution)
{
	solution_t sol;

	if (ecuacion[0].value.l != 1)
	{
		ecuacion = go_div(ecuacion);
		solution.steps.push_back(printer(ecuacion,NULL));
		ecuacion = solve_fractions(ecuacion);
		solution.steps.push_back(printer(ecuacion, NULL));
	}
	if (ecuacion[0].sign == -1)
	{
		ecuacion[2].sign *= -1;
		ecuacion[0].sign = 1;
        }
	sol.imaginary = false;
	sol.value_type = ecuacion.back().value_type;
	sol.sol.real = ecuacion.back().value;
	solution.solutions.push_back(sol);
	return solution;
}



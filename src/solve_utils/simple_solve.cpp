#include "computator.h"

output_t simple_solve(vector<monomio> ecuacion, output_t solution)
{
	solution_t sol;
	vector<monomio> img_vec;
	
	if (ecuacion[0].value.l != 1)
	{
		ecuacion = go_div(ecuacion);
		solution.steps.push_back(printer(ecuacion,NULL));
		ecuacion = solve_fractions(ecuacion);
		solution.steps.push_back(printer(ecuacion, NULL));
	}
	if (ecuacion[0].sign == -1)
	{
		if (ecuacion[2].value.l)
			ecuacion[2].sign *= -1;
		ecuacion[0].sign = 1;
	}
	ecuacion[2].value = mySqrt(ecuacion[2].value, ecuacion[2].value_type);
	ecuacion[0].set_grade(1);
	sol.value_type = ecuacion[2].value_type;
	if (ecuacion[2].sign < 0)
	{
		ecuacion[2].set_variable("i");
		solution.steps.push_back(printer(ecuacion, NULL));
		sol.imaginary = true;
		img_vec = sub_vector(ecuacion, 2, 2);
		sol.sol.imaginary = create_complex(img_vec);
		solution.solutions.push_back(sol);
		ecuacion[2].sign *= -1;
		solution.steps.push_back(printer(ecuacion, NULL));
		img_vec = sub_vector(ecuacion, 2, 2);
		sol.sol.imaginary = create_complex(img_vec);
		solution.solutions.push_back(sol);
	}
	else
	{
		solution.steps.push_back(printer(ecuacion, NULL));
		sol.imaginary = false;
		sol.sol.real = ecuacion[2].value;
		solution.solutions.push_back(sol);
		if (sol.value_type == 'l')
			ecuacion[2].value.l *= -1;
		else
			ecuacion[2].value.d *= -1;
		solution.steps.push_back(printer(ecuacion, NULL));
		sol.sol.real = ecuacion[2].value;
		solution.solutions.push_back(sol);
	}
	return solution;
}

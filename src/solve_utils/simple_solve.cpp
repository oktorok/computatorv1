#include "computator.h"


static output_t complex_sol(vector<monomio> ecuacion, output_t solution, int flags)
{
	solution_t sol;
	string var;
	
	ecuacion[2].set_variable("i");
	ecuacion[2].sign = 1;
	ecuacion[2].value = mySqrt(ecuacion[2].value);
	var = ecuacion[0].get_variable();
	ecuacion[0].set_variable(var + "₁");
	if (flags & STEPS)
		solution.steps.push_back(printer(ecuacion, NULL));
	sol.imaginary = true;
	sol.sol.imaginary.imaginary = ecuacion[2].value * ecuacion[2].sign;
	solution.solutions.push_back(sol);
	ecuacion[2].sign *= -1;
	ecuacion[0].set_variable(var + "₂");
	if (flags & STEPS)
		solution.steps.push_back(printer(ecuacion, NULL));
	sol.sol.imaginary.imaginary = ecuacion[2].value * ecuacion[2].sign;
	solution.solutions.push_back(sol);
	return solution;
}

static output_t real_sol(vector<monomio> ecuacion, output_t solution, int flags)
{
	solution_t sol;
	string var;
	
	ecuacion[2].value = mySqrt(ecuacion[2].value);
	var = ecuacion[0].get_variable();
	ecuacion[0].set_variable(var + "₁");
	if (flags & STEPS)
		solution.steps.push_back(printer(ecuacion, NULL));
	sol.imaginary = false;
	sol.sol.real = ecuacion[2].value;	
	solution.solutions.push_back(sol);
	ecuacion[2].value *= -1;
	if (ecuacion[2].value == sol.sol.real)
		return solution;
	ecuacion[0].set_variable(var + "₂");
	if (flags & STEPS)
		solution.steps.push_back(printer(ecuacion, NULL));
	sol.sol.real = ecuacion[2].value;
	solution.solutions.push_back(sol);
	return solution;
}

output_t simple_solve(vector<monomio> ecuacion, output_t solution, int flags)
{
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
		if (ecuacion[2].value)
			ecuacion[2].sign *= -1;
		ecuacion[0].sign = 1;
	}
	ecuacion[0].set_grade(1);
	if (ecuacion[2].sign < 0)
		solution = complex_sol(ecuacion, solution, flags);
	else
		solution = real_sol(ecuacion, solution, flags);
	return solution;
}

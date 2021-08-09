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
	{
		solution.guide.push_back("First Solution:");
		solution.steps.push_back(printer(ecuacion));
	}
	sol.imaginary = true;
	sol.sol.imaginary.real = 0;
	sol.sol.imaginary.imaginary = ecuacion[2].value * ecuacion[2].sign;
	solution.solutions.push_back(sol);
	ecuacion[2].sign *= -1;
	ecuacion[0].set_variable(var + "₂");
	if (flags & STEPS)
	{
		solution.guide.push_back("Second Solution:");
		solution.steps.push_back(printer(ecuacion));
	}
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
	{
		if (ecuacion[2].value)
			solution.guide.push_back("First Solution:");
		else
			solution.guide.push_back("Double Root Solution");
		solution.steps.push_back(printer(ecuacion));
	}
	sol.imaginary = false;
	sol.sol.real = ecuacion[2].value;
	solution.solutions.push_back(sol);
	ecuacion[2].value *= -1;
	if (ecuacion[2].value == sol.sol.real)
	{
		solution.solutions.push_back(sol);
		return solution;
	}
	ecuacion[0].set_variable(var + "₂");
	if (flags & STEPS)
	{
		solution.guide.push_back("Second Solution:");
		solution.steps.push_back(printer(ecuacion));
	}
	sol.sol.real = ecuacion[2].value;
	solution.solutions.push_back(sol);
	return solution;
}

output_t simple_solve(vector<monomio> ecuacion, output_t solution, int flags)
{
	ecuacion[3].value = ecuacion[1].value;
	ecuacion[3].sign = ecuacion[1].sign * -1;
	ecuacion.erase(ecuacion.begin() + 1);
	if (ecuacion[0].value != 1)
	{
		ecuacion = go_div(ecuacion);
		if (flags & STEPS)
		{
			solution.guide.push_back("Isolating Incognite:");
			solution.steps.push_back(printer(ecuacion));
		}
		ecuacion = solve_fractions(ecuacion);
		if (flags & STEPS)
		{
			solution.guide.push_back("Solving Fractions:");
			solution.steps.push_back(printer(ecuacion));
		}
	}
	if (ecuacion[0].sign == -1)
	{
		if (ecuacion[2].value)
			ecuacion[2].sign *= -1;
		ecuacion[0].sign = 1;
		if (flags & STEPS)
		{
			solution.guide.push_back("Changing Signs");
			solution.steps.push_back(printer(ecuacion));
		}
	}
	ecuacion[0].set_grade(1);
	if (flags & STEPS)
	{
		stringstream ss;
		solution.guide.push_back("Moving Square to Square Root:");
		ss << ecuacion[0].get_variable() << "=√" << (ecuacion[2].sign == 1 ? "" : "-") << ecuacion[2].value;
		solution.steps.push_back(ss.str());
	}
	if (ecuacion[2].sign < 0)
		solution = complex_sol(ecuacion, solution, flags);
	else
		solution = real_sol(ecuacion, solution, flags);
	return solution;
}

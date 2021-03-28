#include "computator.h"

static monomio create_zero_sol(string var)
{
	monomio zero_sol;

	zero_sol.ini_monomio(var, 1, -1, 1);
	return zero_sol;
}

output_t no_indepterm(vector<monomio> ecuacion, output_t solution, int flags)
{
	monomio equal_zero;
	stringstream ss;
	string var;
	output_t tmp;
	solution_t sol;
	int grade_one;

	
	var = ecuacion[0].get_variable();
	ecuacion[0].set_grade(1);
	ecuacion[1].set_grade(0);
	ecuacion[1].set_variable("");
	equal_zero = create_zero_sol(ecuacion[0].get_variable());
	ss << var << "(" << printer(sub_vector(ecuacion, 0, 2)) << ")" << printer(sub_vector(ecuacion, 2, 4));
	if (flags & STEPS)
	{
		solution.guide.push_back("Taking out Incognite as Commun Factor:");
		solution.steps.push_back(ss.str());
	}
	ss.str("");
	ss << var + "₁" << "=0";
	sol.imaginary = false;
	sol.sol.real = 0;
	solution.solutions.push_back(sol);
	if (flags & STEPS)
	{
		solution.guide.push_back("First Solution:");
		solution.steps.push_back(ss.str());
	}
	ecuacion[0].set_variable(var + "₂");
	if (flags & STEPS)
	{
		solution.guide.push_back("Ecuation for Second Solution:");
		solution.steps.push_back(printer(ecuacion));
	}
	grade_one = 1;
	tmp = computatorv1(ecuacion, grade_one, STEPS);
	solution.solutions.insert(solution.solutions.end(), tmp.solutions.begin(), tmp.solutions.end());
	if (flags & STEPS)
	{
		solution.guide.insert(solution.guide.end(), tmp.guide.begin() + 1, tmp.guide.end() - 1);
		solution.steps.insert(solution.steps.end(), tmp.steps.begin() + 1, tmp.steps.end());
		solution.guide.push_back("Second Solution:");
	}
	
	return solution;
}

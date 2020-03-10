#include "computator.h"

static monomio create_zero_sol(string var)
{
	monomio zero_sol;

	zero_sol.ini_monomio(var, 1, -1, 1, 1);
	return zero_sol;
}

output_t no_indepterm(vector<monomio> ecuacion, output_t solution, int flags)
{
	monomio equal_zero;
	stringstream ss;
	string var;
	output_t tmp;
	solution_t sol;
	
	var = ecuacion[0].get_variable();
	ecuacion[0].set_grade(1);
	ecuacion[1].set_grade(0);
	ecuacion[1].set_variable("");
	equal_zero = create_zero_sol(ecuacion[0].get_variable());
	ss << var << "(" << printer(sub_vector(ecuacion, 0, 2), NULL) << ")" << printer(sub_vector(ecuacion, 2, 4), NULL);
	if (flags & STEPS)
		solution.steps.push_back(ss.str());
	ss.str("");
	ss << var + "₁" << "=0";
	sol.imaginary = false;
	sol.sol.real = 0;
	solution.solutions.push_back(sol);
	if (flags & STEPS)
		solution.steps.push_back(ss.str());

	ecuacion[0].set_variable(var + "₂");
	if (flags & STEPS)
		solution.steps.push_back(printer(ecuacion, NULL));
	tmp = computatorv1(ecuacion, 1, STEPS);


	solution.solutions.insert(solution.solutions.end(), tmp.solutions.begin(), tmp.solutions.end());
	if (flags & STEPS)
		solution.steps.insert(solution.steps.end(), tmp.steps.begin(), tmp.steps.end());
	
	return solution;
}

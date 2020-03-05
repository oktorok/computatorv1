#include "computator.h"

static monomio create_zero_sol(string var)
{
	monomio zero_sol;

	zero_sol.ini_monomio(var, 1, -1, 1, 1);
	return zero_sol;
}

output_t no_indepterm(vector<monomio> ecuacion, output_t solution)
{
	monomio equal_zero;
	stringstream ss;
	output_t tmp;
	solution_t sol;
	
	ecuacion[0].set_grade(1);
	ecuacion[1].set_grade(0);
	ecuacion[1].set_variable("");
	tmp = computatorv1(ecuacion, 1);
	
	equal_zero = create_zero_sol(ecuacion[0].get_variable());
	ss << ecuacion[0].get_variable() << "(" << printer(sub_vector(ecuacion, 0, 2), NULL) << ")" << printer(sub_vector(ecuacion, 2, 4), NULL);
	solution.steps.push_back(ss.str());
	ss.str("");
	ss << ecuacion[0].get_variable() << "=0";
	sol.imaginary = false;
	sol.sol.real = 0;
	solution.solutions.push_back(sol);
	solution.steps.push_back(ss.str());
	solution.steps.push_back("or");
	solution.steps.push_back(printer(ecuacion, NULL));

	solution.solutions.insert(solution.solutions.end(), tmp.solutions.begin(), tmp.solutions.end());
	solution.steps.insert(solution.steps.end(), tmp.steps.begin(), tmp.steps.end());
	
	return solution;
}

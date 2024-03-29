#include "computator.h"

static output_t solv_second_grade(vector<monomio> ecuacion, output_t solution, int flags)
{
	if (ecuacion.size() == 5)
		solution = normal_solve(ecuacion, solution, flags);
	else if ((ecuacion[1].get_grade() == 0 || ecuacion[1].get_variable() == "=") && ecuacion[0].get_grade() == 2)
		solution = simple_solve(ecuacion, solution, flags);
	else
		solution = no_indepterm(ecuacion, solution, flags);

	return solution;
}

output_t solve(vector<monomio> ecuacion, output_t solution, int flags)
{
	switch (ecuacion[0].get_grade())
	{
	case 0:
		cout << "grade 0" << endl;
		break;
	case 1:
		solution = solv_first_grade(ecuacion, solution, flags);
		break;
	case 2:
		solution = solv_second_grade(ecuacion, solution, flags);
		break;
	default:
		//cout << "Error grade more than 2" << endl;
		break;
	}
	return (solution);
}

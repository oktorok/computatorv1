#include "computator.h"

static output_t solv_second_grade(vector<monomio> ecuacion, output_t solution)
{
	if (ecuacion.size() == 3)
		solution = simple_solve(ecuacion, solution);
	else if (ecuacion[2].value && !ecuacion[2].get_grade())
		solution = normal_solve(ecuacion, solution);
	else
		solution = no_indepterm(ecuacion, solution);

	return solution;
}

output_t solve(vector<monomio> ecuacion, output_t solution)
{
	switch (ecuacion[0].get_grade())
	{
	case 0:
		cout << "grade 0" << endl;
		break;
	case 1:
		solution = solv_first_grade(ecuacion, solution);
		break;
	case 2:
		solution = solv_second_grade(ecuacion, solution);
		break;
	default:
		//result = (value_u){0};
		//printf("Grade more than 2, expression not solvable in computator-v1");
		break;
	}
	return (solution);
}

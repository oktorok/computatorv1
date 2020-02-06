#include "computator.h"

static solution_t solv_first_grade(vector<monomio> ecuacion, vector<string> steps)
{
	solution_t sol;

	ecuacion = go_div(ecuacion);
	steps.push_back(printer(ecuacion,NULL));
	ecuacion = solve_fractions(ecuacion);
	steps.push_back("SOLUTION:");
	steps.push_back(printer(ecuacion, NULL));
	sol.imaginary = false;
	sol.value_type = ecuacion.back().value_type;
	sol.real.push_back(ecuacion.back().value);
	sol.steps = steps;
	
	return sol;
}


static solution_t solv_second_grade(vector<monomio> ecuacion, vector<string> steps)
{
	solution_t sol;
	monomio tmp;
	vector<monomio> img_vec;
	
	switch (ecuacion.size())
	{
	case 3:
		ecuacion[2].value = mySqrt(ecuacion[2].value, ecuacion[2].value_type);
		ecuacion[0].set_grade(1);
		sol.value_type = ecuacion[2].value_type;
		steps.push_back("SOLUTION 1:");
		if (ecuacion[2].sign < 0)
		{
			ecuacion[2].set_variable("i");
			steps.push_back(printer(ecuacion, NULL));
			sol.imaginary = true;
			img_vec = sub_vector(ecuacion, 2, 2);
			sol.imaginary_sol.push_back(printer(img_vec, NULL));
			ecuacion[2].sign *= -1;
			steps.push_back("SOLUTION 2:");
			steps.push_back(printer(ecuacion, NULL));
			img_vec = sub_vector(ecuacion, 2, 2);
			sol.imaginary_sol.push_back(printer(img_vec, NULL));
		}
		else
		{
			steps.push_back(printer(ecuacion, NULL));
			sol.imaginary = false;
			sol.real.push_back(ecuacion[2].value);
			if (sol.value_type == 'l')
				ecuacion[2].value.l *= -1;
			else
				ecuacion[2].value.d *= -1;
			steps.push_back("SOLUTION 2:");
			steps.push_back(printer(ecuacion, NULL));
			sol.real.push_back(ecuacion[2].value);
		}
		sol.steps = steps;
		break;
	case 4:
		sol = no_indepterm(ecuacion, steps);
		break;

	case 5:
		sol.steps = steps;
		break;
	}
	return sol;
}

solution_t solve(vector<monomio> ecuacion, vector<string> steps)
{
	solution_t sol;

	switch (ecuacion[0].get_grade())
	{
	case 0:
		cout << "grade 0" << endl;
		break;
	case 1:
		sol = solv_first_grade(ecuacion, steps);
		break;
	case 2:
		sol = solv_second_grade(ecuacion, steps);
		break;
	default:
		//result = (value_u){0};
		//printf("Grade more than 2, expression not solvable in computator-v1");
		break;
	}
	return (sol);
}

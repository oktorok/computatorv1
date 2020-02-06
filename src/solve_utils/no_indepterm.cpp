#include "computator.h"

solution_t no_indepterm(vector<monomio> ecuacion, vector<string> steps)
{
	monomio tmp;
	stringstream ss;
	solution_t sol;
	
	ecuacion[0].set_grade(1);
	ecuacion[1].set_grade(0);
	ecuacion[1].set_variable("");
	ss << ecuacion[0].get_variable() << "(" << printer(sub_vector(ecuacion, 0, 3), NULL) << printer(sub_vector(ecuacion, 2, 3), NULL) << endl;
	cout << ss.str() << endl;

	sol.steps = steps;
	return sol;
}

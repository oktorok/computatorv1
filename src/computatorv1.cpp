#include "computator.h"

static bool compareGrades(monomio a, monomio b)
{
	return (a.get_grade() > b.get_grade());
}

static vector<monomio> sort_expresion(vector<monomio> expresiones, int max_grade)
{
	vector<monomio> sorted;
	monomio zero;
	monomio equal;
	int grade, equal_set = 1;
	vector<int> watched;
	
	equal.ini_monomio("=", 0, -1, 0, 0);
	if (max_grade > 1)
		equal_set = expresiones.size() - 2;
	while (max_grade > -1)
	{
		if ((!max_grade && !equal_set) || (equal_set && sorted.size() == equal_set))
			sorted.push_back(equal);
		for (int i=0; i <= expresiones.size(); i++)
		{
			if (i == expresiones.size())
			{
				max_grade--;
				break;
			}

			grade = expresiones[i].get_grade();
			if (grade == max_grade && find(watched.begin(), watched.end(), i) == watched.end())
			{
				if (!expresiones[i].value)
					continue;
				if ((equal_set || !max_grade) && i >= equal_set)
					expresiones[i].sign *= -1;
				sorted.push_back(expresiones[i]);
				watched.push_back(i);
				break;
			}
		}
	}
	if (!equal_set)
		sorted.push_back(equal);
	if (sorted.back().get_grade() == -1)
	{
		zero.ini_monomio("", 0, 0, 1, 1);
		sorted.push_back(zero);
	}
	return sorted;
}

static vector<monomio> simplify_expresion(vector<monomio> expresiones)
{
	monomio *actual, tmp;
	int max_grade = 0, grade_act;
	string t = "00";
	
	for (int i=0; i < expresiones.size(); i++)
	{
		actual = &expresiones[i];
		grade_act = actual->get_grade();
		for (int j=i + 1; j < expresiones.size(); j++)
		{
 			tmp = expresiones[j];
			if (grade_act > max_grade)
				max_grade = grade_act;
			if (!tmp.value || grade_act != tmp.get_grade())
				continue;
			if (grade_act == tmp.get_grade())
			{
				actual->value = actual->value * actual->sign + tmp.value * tmp.sign;
				expresiones.erase(expresiones.begin() + j);
				if (!actual->value)
				{
					expresiones.erase(expresiones.begin() + i--);
					break;
				}
				else if (signbit(actual->value))
					actual->value *= (actual->sign = -1);
				else
					actual->sign = 1;
				j = i;
			}
			else
				break;
		}
	}
	return expresiones;
}

output_t computatorv1(vector<monomio> expresiones, int max_grade)
{
	output_t sol;
	string result;
	int mon_cuant;

	//sol = new solution_t();
	
	vector<string> steps;
	//expresiones = parsing3(ecuacion);
	steps.push_back(printer(expresiones, NULL));

	expresiones = solve_fractions(expresiones);
	steps.push_back(printer(expresiones, NULL));
	
	expresiones = sort_expresion(expresiones, max_grade);
	steps.push_back(printer(expresiones, NULL));

	//expresiones = simplify_expresion(expresiones);
	steps.push_back(printer(expresiones, NULL));
	//cout << expresiones.size() << endl;
	//cout << printer(expresiones, NULL) << endl;
	sol.steps = steps;
	sol = solve(expresiones, sol);
	//cout << "AFTER SIMP" << endl;
	//for (int i = 0; i < mon_cuant; i++)
	//{
	//	cout << "VS: " << expresiones[i].value_string << " VAR: " << expresiones[i].get_variable() <<" G: " << expresiones[i].get_grade() << " VAL: " << expresiones[i].value.l << endl;
	//}
	//steps.push_back(printer(expresiones, NULL));
	return sol;
}

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
	int grade, equal_set = -1;
	vector<int> watched;
	
	equal.ini_monomio("=", 0, -1, 0, 0);
	switch (max_grade)
	{
	case 1:
		equal_set = 1;
		break;
	case 2:
		if (expresiones.size() == 3)
			equal_set = 1;
		else if  (expresiones.size() == 4 && expresiones[1].get_variable() == "")
		 	equal_set = 1;
		else
			equal_set = 3;
		break;
	}
	cout << equal_set << endl;
	//if (max_grade > 1 || max_grade )
	//	equal_set = expresiones.size() - 2;
	while (max_grade > -1)
	{
		if (sorted.size() == equal_set)
		{
			sorted.push_back(equal);
			equal_set = -1;
		}
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
	if (equal_set == (sorted.size() + 1))
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
			if (grade_act != tmp.get_grade())
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
	if (expresiones.back().get_grade() == -1)
	{
		tmp.ini_monomio("", 0, 0, 1, 1);
		expresiones.push_back(tmp);
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

	expresiones = simplify_expresion(expresiones);
	steps.push_back(printer(expresiones, NULL));

	expresiones = sort_expresion(expresiones, max_grade);
	steps.push_back(printer(expresiones, NULL));

	sol.steps = steps;
	sol = solve(expresiones, sol);
	return sol;
}

#include "computator.h"

static vector<monomio> sort_expresion(vector<monomio> expresiones, int max_grade)
{
	vector<monomio> sorted;
	monomio zero;
	monomio equal;
	int grade, side=1;
	size_t equal_set = 0;
	vector<int> watched;

	
	equal.ini_monomio("=", 0, -1, 0);
	switch (max_grade)
	{
	case 1:
		equal_set = 1;
		break;
	case 2:
		if (expresiones.size() - 1 == 2 && (expresiones.back().get_variable() == "" || expresiones.front().get_variable() == ""))
			equal_set = 1;
		//else if  (expresiones.size() - 1 == 2 && expresiones[1].get_variable() == "")
		// 	equal_set = 1;
		else
			equal_set = 3;
		break;
	default:
		equal_set = expresiones.size() - 1;
	}
	while (max_grade > -1)
	{
		if (sorted.size() == equal_set)
		{
			sorted.push_back(equal);
			equal_set = 0;
		}
		side = 1;
		for (size_t i=0; i <= expresiones.size(); i++)
		{
			if (i == expresiones.size())
			{
				max_grade--;
				break;
			}
			if (expresiones[i].get_variable() == "=")
				side = -1;
			grade = expresiones[i].get_grade();
			if (grade == max_grade && find(watched.begin(), watched.end(), i) == watched.end())
			{
				if (!expresiones[i].value)
					continue;
				//if (grade > 1)
				expresiones[i].sign *= side * (equal_set > 0 ? 1 : -1);
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
		zero.ini_monomio("", 0, 0, 1);
		sorted.push_back(zero);
	}
	return sorted;
}

static vector<monomio> simplify_expresion(vector<monomio> expresiones, int &max_grade)
{
	monomio *actual, tmp;
	int grade_act, sideA = 1, sideT = 1;
	string t = "00";
	
	for (size_t i=0; i < expresiones.size(); i++)
	{
		actual = &expresiones[i];
		if (!actual->value && actual->get_grade() > 0)
		{
			if (actual->get_grade() == max_grade)
			{
				max_grade = 0;
				for (size_t j=0; j < expresiones.size(); j++)
				{
					if (j == i)
						continue;
					if (expresiones[j].get_grade() > max_grade)
						max_grade = expresiones[j].get_grade();
				}
			}
			expresiones.erase(expresiones.begin() + i--);
					
			continue;
		}
		grade_act = actual->get_grade();
		if (actual->get_variable() == "=")
			sideA = -1;
		sideT = 1;
		for (size_t j=i + 1; j < expresiones.size(); j++)
		{
 			tmp = expresiones[j].copy_monomio();
			if (tmp.get_variable() == "=" || sideA < 0)
				sideT = -1;
			if (grade_act > max_grade)
				max_grade = grade_act;
			if (grade_act != tmp.get_grade())
				continue;
			if (grade_act == tmp.get_grade() && actual->get_variable() == tmp.get_variable())
			{
				if (sideA != sideT)
					actual->value = actual->value * actual->sign - tmp.value * tmp.sign;
				else
					actual->value = actual->value * actual->sign + tmp.value * tmp.sign;
				expresiones.erase(expresiones.begin() + j);
				if (!actual->value)
				{
					if (actual->get_grade() == max_grade)
						max_grade = 0;
					expresiones.erase(expresiones.begin() + i);
					i = -1;
					break;
				}
				else if (signbit(actual->value))
					actual->value *= (actual->sign = -1);
				else
					actual->sign = 1;
				j = i;
			}
		}
	}
	if (expresiones.back().get_grade() == -1)
	{
		tmp.ini_monomio("", 0, 0, 1);
		expresiones.push_back(tmp);
	}
	if (expresiones[0].get_grade() == -1)
	{
		tmp.ini_monomio("", 0, 0, 1);
		expresiones.insert(expresiones.begin(), tmp);
	}
	return expresiones;
}

output_t computatorv1(vector<monomio> &expresiones, int &max_grade, int flags)
{
	output_t sol, othersols;
	vector<monomio> reduced;
	//sol = new solution_t();
	vector<string> legends;
	vector<string> steps;
	//expresiones = parsing3(ecuacion);
	if (flags & STEPS)
	{
		legends.push_back("Polinomyal Expression:");
		steps.push_back(printer(expresiones));
	}
	expresiones = solve_fractions(expresiones);
	if (flags & STEPS)
	{
		legends.push_back("Solving Fractions:");
		steps.push_back(printer(expresiones));
	}
	expresiones = simplify_expresion(expresiones, max_grade);
	if (flags & STEPS)
	{
		legends.push_back("Simplifying Expression:");
		steps.push_back(printer(expresiones));
	}
	if (printer(expresiones) == "0=0")
	{
		sol.guide = legends;
		sol.steps = steps;
		return sol;
	}
	expresiones = sort_expresion(expresiones, max_grade);
	if (flags & STEPS)
	{
		legends.push_back("Reordering monomies:");
		steps.push_back(printer(expresiones));
	}
	// cout << printer(expresiones) << endl;
	reduced = expresiones;
	sol.guide = legends;
	sol.steps = steps;
	sol = solve(expresiones, sol, flags);
	expresiones = reduced;
	return sol;
}

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
	int grade;
	vector<int> watched;
	equal.ini_monomio("=", (value_u){0}, -1, 'l', 0, 0);
	while (max_grade > -1)
	{
		if (!max_grade && equal.value.l == 0)
		{
			sorted.push_back(equal);
			equal.value.l = 1;
			continue;
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
				if (expresiones[i].value.l == 0)
					continue;
				if (!grade && i < expresiones.size() - 2)
					expresiones[i].sign *= -1;
				sorted.push_back(expresiones[i]);
				watched.push_back(i);
				break;
			}
		}
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
		for (int j=i + 1; j < expresiones.size(); j++)
		{
 			tmp = expresiones[j];
			grade_act = actual->get_grade();
			if (grade_act > max_grade)
				max_grade = grade_act;
			if (!tmp.value.l || grade_act != tmp.get_grade())
				continue;
			if (grade_act == tmp.get_grade())
			{
				t[0] = actual->value_type;
				t[1] = tmp.value_type;
				if (t == "ll")
				{
					cout << actual->value.l << endl;
					cout << actual->sign << endl;
					cout << tmp.value.l << endl;
					cout << tmp.sign << endl;
					actual->value.l = actual->value.l * actual->sign + tmp.value.l * tmp.sign;
					cout << actual->value.l << endl;
					cout << actual->sign << endl;
				}
				else if (t == "dd")
					actual->value.d = actual->value.d * actual->sign + tmp.value.d * tmp.sign;
				else if (t == "ld")
				{
					actual->value.d = actual->value.l * actual->sign + tmp.value.d * tmp.sign;
					actual->value_type = 'd';
				}
				else if (t == "dl")
					actual->value.d = actual->value.d * actual->sign + tmp.value.l * tmp.sign;
				expresiones.erase(expresiones.begin() + j);
				if (!actual->value.l)
				{
					expresiones.erase(expresiones.begin() + i--);
					break;
				}
				else if (actual->value_type == 'l' && actual->value.l < 0)
					actual->value.l *= (actual->sign *= -1);
				else if (actual->value_type == 'd' && actual->value.d < 0)
					actual->value.d *= (actual->sign *= -1);
				else
					actual->sign = 1;
				
				j = i;
			}
			else
				break;
		}
	}
	if (max_grade == 2 && expresiones.size() == 4)
		expresiones = move_indepterm(expresiones);
	
	return expresiones;
}

solution_t computatorv1(vector<monomio> expresiones, int max_grade)
{
	solution_t sol;
	string result;
	int mon_cuant;

	//sol = new solution_t();
	
	vector <string> steps;
	//expresiones = parsing3(ecuacion);
	steps.push_back(printer(expresiones, NULL));
	
	expresiones = sort_expresion(expresiones, max_grade);
	steps.push_back(printer(expresiones, NULL));

	expresiones = solve_fractions(expresiones);
	steps.push_back(printer(expresiones, NULL));

	expresiones = simplify_expresion(expresiones);
	steps.push_back(printer(expresiones, NULL));

	sol = solve(expresiones, steps);
	//cout << "AFTER SIMP" << endl;
	//for (int i = 0; i < mon_cuant; i++)
	//{
	//	cout << "VS: " << expresiones[i].value_string << " VAR: " << expresiones[i].get_variable() <<" G: " << expresiones[i].get_grade() << " VAL: " << expresiones[i].value.l << endl;
	//}
	//steps.push_back(printer(expresiones, NULL));
	return sol;
}

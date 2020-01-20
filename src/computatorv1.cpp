#include "computator.h"

static bool compareGrades(monomio a, monomio b)
{
	return (a.get_grade() > b.get_grade());
}

static vector<monomio> sort_expresion(vector<monomio> expresiones)
{
	vector<monomio> sorted;
	monomio zero;
	int grade;
	struct to_sort {
		int max_grade;
		int idx;
	};
	to_sort tmp;
	vector<monomio>::iterator it1, it2;
	while (expresiones.size())
	{
		tmp = (to_sort){-2, 0};
		for (int i=0; i < expresiones.size(); i++)
		{
			grade = expresiones[i].get_grade();
			if (grade > tmp.max_grade)
			{
				tmp.max_grade = grade;
				tmp.idx = i;
			}		
		}

		if (tmp.idx > 1 && expresiones[tmp.idx - 1].get_variable() == "/")
		{
			expresiones[tmp.idx - 2].sign *= expresiones[tmp.idx].side;
			sorted.push_back(expresiones[tmp.idx - 2]);
			sorted.push_back(expresiones[tmp.idx - 1]);
			sorted.push_back(expresiones[tmp.idx]);
			it1 = expresiones.begin() + tmp.idx - 2;
			it2 = expresiones.begin() + tmp.idx + 1;
			expresiones.erase(it1, it2);
		}
		else
		{
			expresiones[tmp.idx].sign *= expresiones[tmp.idx].side;
			it1 = expresiones.begin() + tmp.idx;
			sorted.push_back(expresiones[tmp.idx]);
			expresiones.erase(it1);
		}
	}
	zero.ini_monomio("", (value_u){0}, 1, 'l', 1, -1);
	sorted.push_back(zero);
	return sorted;
}

static vector<monomio> simplify_expresion(vector<monomio> expresiones)
{
	vector<monomio>::iterator it1;
	monomio *actual, tmp;
	string t = "00";
	
	for (int i=0; i < expresiones.size(); i++)
	{
		actual = &expresiones[i];
		for (int j=i + 1; j < expresiones.size(); j++)
		{
			tmp = expresiones[j];
			if (!tmp.value.l)
				continue;
			if (actual->get_grade() == tmp.get_grade())
			{
				t[0] = actual->value_type;
				t[1] = tmp.value_type;
				if (t == "ll")
				{
					actual->value.l = actual->value.l * actual->sign + tmp.value.l * tmp.sign;
				}
				else if (t == "dd") //caso especial cuando dos double de un long por ejemplo 0.8 + 0.2 = 1 
					actual->value.d = actual->value.d * actual->sign + tmp.value.d * tmp.sign;
				else if (t == "ld")
				{
					actual->value.d = actual->value.l * actual->sign + tmp.value.d * tmp.sign;
					actual->value_type = 'd';
				}
				else if (t == "dl")
					actual->value.d = actual->value.d * actual->sign + tmp.value.l * tmp.sign;
				it1 = expresiones.begin() + j;
				expresiones.erase(it1);
				if (!actual->value.l)
				{
					it1 = expresiones.begin() + i;
					expresiones.erase(it1);
					i = i - 1;
					break;
				}
				else if (actual->value_type == 'l' && actual->value.l < 0)
				{
					actual->sign = -1;
					actual->value.l *= -1;
				}
				else if (actual->value_type == 'd' && actual->value.d < 0)
				{
					actual->sign = -1;
					actual->value.d *= -1;
				}
				j = i;
			}
		}
	}
	return expresiones;
}

static value_u check_division(value_u a, char &type_a, value_u b, char type_b)
{
	value_u ret;
 	if (type_a == type_b)
	{
		if (type_a == 'd')
		{
			if (fmod(a.d, b.d))
			{
				type_a = 'd';
				ret.d = a.d/b.d;
			}
			else
			{
				type_a = 'l';
				ret.l = a.d/b.d;
			}
		}
		else
		{
			if (a.l % b.l)
			{
				type_a = 'd';
				ret.d = a.l/b.l;
			}
			else
			{
				type_a = 'l';
				ret.l = a.l/b.l;
			}
		}
	}
	else if (type_a == 'l')
	{
		if (fmod(a.l, b.d))
	       	{
			type_a = 'd';
			ret.d = a.l/b.d;
		}
		else
		{
			type_a = 'l';
			ret.l = a.l/b.d;
		}
	}
	else if (fmod(a.d, b.l))
	{
		type_a = 'd';
		ret.d = a.d/b.l;
	}
	else
	{
		type_a = 'l';
		ret.l = a.d/b.l;
	}
	return ret;
	
}

static vector<monomio> solve_fractions(vector<monomio> expresiones, vector<string> &steps)
{
	vector<monomio>::iterator it1, it2;
	value_u *num, den;
	string t = "00";
	
	for (int i=1; i < expresiones.size(); i++)
	{
		if (expresiones[i].get_variable() == "/")
		{
			num = &expresiones[i - 1];
			den = expresiones[i + 1];
			t[0] = num->value_type;
			t[1] = den.value_type;
			num->value = check_division(num->value, &num->value_type, den.value, den.value_type);
			it1 = expresiones.begin() + i;
			it2 = it1 + 2;
			expresiones.remove(it1, it2);
			i--;
		}
	}
	steps->push_back(printer(expresiones), NULL);
	return expresiones;
}

solution_t computatorv1(string ecuacion)
{
	vector <monomio> expresiones;
	//vector <string> steps;
	solution_t sol;
	vector <wstring> result;
	int mon_cuant;

	//sol = new solution_t();
	
	vector <string> &steps = sol.steps;
	expresiones = parsing3(ecuacion);
	steps.push_back(printer(expresiones, NULL));

	expresiones = sort_expresion(expresiones);
	steps.push_back(printer(expresiones, NULL));

	expresiones = solve_fractions(expresiones, steps);
	
	expresiones = simplify_expresion(expresiones);
	steps.push_back(printer(expresiones, NULL));
	//cout << "AFTER SIMP" << endl;
	//for (int i = 0; i < mon_cuant; i++)
	//{
	//	cout << "VS: " << expresiones[i].value_string << " VAR: " << expresiones[i].get_variable() <<" G: " << expresiones[i].get_grade() << " VAL: " << expresiones[i].value.l << endl;
	//}
	//steps.push_back(printer(expresiones, NULL));
	return sol;
}

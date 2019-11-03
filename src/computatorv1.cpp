#include "computator.h"

static bool compareGrades(monomio a, monomio b)
{
	return (a.get_grade() > b.get_grade());
}

static vector<monomio> simplify_expresion(vector<monomio> expresiones)
{
	int mon_cuant;
	
	mon_cuant = expresiones.size();
	for (int i = 0; i < mon_cuant; i++)
	{
		for (int j = 1 + i ; j < mon_cuant; j++)
		{
			if (expresiones[i].is_compt(expresiones[j]))
			{
				expresiones[i].sum_monomios(expresiones[j]);
				expresiones.erase(expresiones.begin() + j);
				mon_cuant = expresiones.size();
				j--;
			}
		}
	}
	sort(expresiones.begin(), expresiones.end(), compareGrades);
	return expresiones;
}


solution_t computatorv1(string ecuacion)
{
	vector <monomio> expresiones;
	//vector <string> steps;
	solution_t *sol;
	vector <wstring> result;

	sol = new solution_t();
	vector <string> &steps = sol->steps;
	expresiones = parsing(ecuacion);
	steps.push_back(printer(expresiones, NULL));
	expresiones = simplify_expresion(expresiones);
	steps.push_back(printer(expresiones, NULL));
	return *sol;
}

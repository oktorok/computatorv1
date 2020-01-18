#include "computator.h"

static bool compareGrades(monomio a, monomio b)
{
	return (a.get_grade() > b.get_grade());
}

static vector<monomio> simplify_expresion(vector<monomio> expresiones)
{
	int mon_cuant;
	short side = 1, tmp_side = 1;
	monomio back_zero;
	mon_cuant = expresiones.size();
	for (int i = 0; i < mon_cuant; i++)
	{
		if (expresiones[i].get_variable() == "=")
		{
			side = -1;
			continue;
		}
		for (int j = 1 + i ; j < mon_cuant; j++)
		{
			if (expresiones[j].get_variable() == "=")
				tmp_side = -1;
			else if (expresiones[i].is_compt(expresiones[j]))
			{
				expresiones[i].sum_monomios(expresiones[j], tmp_side);
				expresiones.erase(expresiones.begin() + j);
				mon_cuant = expresiones.size();
				j--;
			}
		}
		if (side == -1)
		{
			expresiones[i].value.l = ~expresiones[i].value.l | (1l << (sizeof(long) * 8 - 1)) + 1;
			if (expresiones[i].value_string[0] == '-')
				expresiones[i].value_string.erase(0,1);
			else
				expresiones[i].value_string[0] = '-';
			}
	}
	sort(expresiones.begin(), expresiones.end(), compareGrades);
	back_zero.ini_monomio('\0',(value_u){0},0,'l',"0");
	expresiones.push_back(back_zero);
	return expresiones;
}


solution_t computatorv1(string ecuacion)
{
	vector <monomio> expresiones;
	//vector <string> steps;
	solution_t *sol;
	vector <wstring> result;
	int mon_cuant;

	sol = new solution_t();
	
	vector <string> &steps = sol->steps;
	//expresiones = parsing(ecuacion);
	expresiones = parsing2(ecuacion);
	mon_cuant = expresiones.size();
	cout << "BEFORE SIMP" << endl;    
	for (int i = 0; i < mon_cuant; i++)
	{
		cout << "VS: " << expresiones[i].value_string << " VAR: " << expresiones[i].get_variable() <<" G: " << expresiones[i].get_grade() << " VAL: " << expresiones[i].value.l << endl;
	}

	steps.push_back(printer(expresiones, NULL));
	expresiones = simplify_expresion(expresiones);
	cout << "AFTER SIMP" << endl;
	for (int i = 0; i < mon_cuant; i++)
	{
		cout << "VS: " << expresiones[i].value_string << " VAR: " << expresiones[i].get_variable() <<" G: " << expresiones[i].get_grade() << " VAL: " << expresiones[i].value.l << endl;
	}
	steps.push_back(printer(expresiones, NULL));
	return *sol;
}

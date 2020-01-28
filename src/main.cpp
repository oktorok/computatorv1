#include "computator.h"


int main(int argc, char **argv) {

	vector<monomio> expresiones;
	vector<string> steps;
	int mon_cuant;
	string *result;
	solution_t sol;

	setlocale(LC_ALL, "");
	if (argc < 2)
	{
		cout << "No expression found" << endl;
		return (0);
	}
	sol = computatorv1(argv[1]);
	cout << "Solving Steps:" << endl;
	sol.steps.erase( unique( sol.steps.begin(), sol.steps.end() ), sol.steps.end() );
	for (int i=0; i < sol.steps.size(); i++)
		cout << sol.steps[i] << endl;
	return 0;
	/*
	expresiones = parsing(argv[1]);
	mon_cuant = expresiones.size();
	//printf("tengo %i monomios\n", mon_cuant);
	//for (int i = 0; i < mon_cuant; i++)
	//{
	//	if (expresiones[i].get_variable() != "")
	//		printf("Monomio %i: %i%s^%i\n", i, expresiones[i].value, expresiones[i].get_variable().c_str(), expresiones[i].get_grade());
	//	else
	//		printf("Monomio %i: %i\n", i, expresiones[i].value);
	//}
	printf("Expresion inicial\n");
	printer(expresiones, NULL);	
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
	result = solve(&expresiones, &steps);
	cout << "Expresion reducida" << endl;
	printer(expresiones, NULL);
	printer2(expresiones[0].get_variable(), result[0], "Solucion 1: ");
	if (expresiones[0].get_grade() == 2)
		printer2(expresiones[0].get_variable(), result[1], "Solucion 2: ");
	for (int i = 0; i < steps.size(); i++)
		printer2("X", steps[i], "");
	//if (result)
	//	delete(result);*/
}

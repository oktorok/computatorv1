#include "computator.h"

//using namespace std;

static bool compareGrades(monomio a, monomio b)
{
	return (a.get_grade() > b.get_grade());
}

int main(int argc, char **argv) {

	vector<monomio> expresiones;
	int mon_cuant;
	string *result;

	setlocale(LC_ALL, "");
	if (argc < 2)
	{
		cout << "No expression found" << endl;
		return (0);
	}
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
	result = solve(&expresiones);
	printf("Expresion reducida\n");
	printer(expresiones, result);
	//if (result)
	//	delete(result);
}

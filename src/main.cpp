#include "computator.h"

//using namespace std;

static bool compareGrades(monomio a, monomio b)
{
	return (a.get_grade() > b.get_grade());
}


void printer2(vector<monomio> ecuacion, string result, string type_answer)
{
	int frac_pos, res_length, denominator_length, radicand = 0, written_characters;
	res_length = result.length();
	frac_pos = result.find("/");
	if (frac_pos)
	{
		cout << endl << string(type_answer.length(), ' ');
		denominator_length = res_length - frac_pos - 1;
		for (int i = 0; i < frac_pos; i++)
		{
			if (result[i] == '|')
			{
				cout << "√";
				radicand = i + 1;
			}
			else
				cout << result[i];
		}
		cout << endl;
		written_characters = (radicand - 1) + (frac_pos + 1 - radicand) ;
		cout << type_answer;
		for (int i = 0; i < written_characters; i++)
			cout << "―";
		cout << endl << string(type_answer.length(), ' ');
		cout << string(written_characters / 2 - denominator_length / 2, ' ') << result.substr(frac_pos + 1, res_length) << endl;
	}
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
	printer2(expresiones, result[0], "Solucion 1: ");
	printer2(expresiones, result[1], "Solucion 2: ");
	//if (result)
	//	delete(result);
}

#include "computator.h"

int set_flags(int argc, char **argv)
{
	int j = 0,flags = 0;
	
	for (int i = 0; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			while (argv[i][j] == '-')
				j++;
			flags |= 1 << argv[i][j] - 97;
		}
	}
	return flags;
}

vector<monomio> reduce_form(vector<monomio> ecuacion)
{
	if (ecuacion[0].get_grade() == 1)
		ecuacion = move_indepterm(ecuacion);
	reverse(ecuacion.begin(), ecuacion.end() - 2);
	return ecuacion;
}

int main(int argc, char **argv) {

	vector<monomio> expresiones;
	vector<string> steps;
	int mon_cuant, max_grade, flags = 0;
	string var;
	output_t sol;
	

	setlocale(LC_ALL, "");
	if (argc == 1)
	{
		cout << "No expression found" << endl;
		return (0);
	}
	
	flags = set_flags(argc, argv);
	if (flags & HELP)
	{
		cout << "Usage: ./computator [OPTIONS] [EXPRESSION]" << endl << "\t-s Show steps." << endl; 
		return 1;
	}
	expresiones = parsing3(argv[argc - 1], max_grade);
	if (!expresiones.size())
	{
		cout << "The expression \"" << argv[argc - 1] <<"\" is not a well formed polynomial expression" << endl;
		return -1;
	}
	sol = computatorv1(expresiones, max_grade, flags);
	for (int i = 0; i < expresiones.size(); i++)
	{
		var = expresiones[i].get_variable();
		if (var != "")
			break;
	}
	if (flags & STEPS)
		cout << "Solving Steps:" << endl;
	sol.steps.erase( unique( sol.steps.begin(), sol.steps.end() ), sol.steps.end() );
	for (int i=0; i < sol.steps.size(); i++)
		cout << sol.steps[i] << endl << endl;

	if (printer(expresiones, NULL) == "0=0")
	{
		cout << "All real numbers are solution for the ecuation" << endl;
		return 0;
	}
	cout << "Reduced form: " << printer(reduce_form(expresiones), NULL) << endl;
	cout << "Polynomial degree: " << max_grade << endl;
	if (max_grade == 2)
	{
		if (sol.solutions[0].imaginary)
		{
			cout << "Discriminant is strictly negative, the two complex solutions are:" << endl;
			cout << var << "₁" << "=" << sol.solutions[0].sol.imaginary.real << (sol.solutions[0].sol.imaginary.imaginary < 0 ? "" : "+") << sol.solutions[0].sol.imaginary.imaginary << "i" << endl;
		
			cout << var << "₂" << "=" << sol.solutions[1].sol.imaginary.real << (sol.solutions[1].sol.imaginary.imaginary < 0 ?"" : "+") << sol.solutions[1].sol.imaginary.imaginary << "i" << endl;
		}
		else
		{
			cout << "Discriminant is strictly positive, the two real solutions are:" << endl;
			cout << var << "₁" << "=" << sol.solutions[0].sol.real << endl;
			cout << var << "₂" << "=" << sol.solutions[1].sol.real << endl;
		}
	}
	else if (max_grade == 1)
	{
		cout << "The solution is:" << endl;
		cout << var << "=" << sol.solutions[0].sol.real << endl;
	}
	else
		cout << "The polynomial degree is strictly grater than 2, I can't solve." << endl;
	return 0;
}

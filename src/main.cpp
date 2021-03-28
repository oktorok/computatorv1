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
			flags |= 1 << (argv[i][j] - 97);
		}
	}
	return flags;
}

vector<monomio> reduce_form(vector<monomio> ecuacion)
{
	if (ecuacion[0].get_grade() == 1)
		ecuacion = move_indepterm(ecuacion);
	reverse(ecuacion.begin(), ecuacion.end() - 2);
	for (size_t i = 0; i < ecuacion.size(); i++)
	{
		if (ecuacion[i].get_grade() == -1)
			break;
		else if (!ecuacion[i].value)
			ecuacion.erase(ecuacion.begin() + i);
	}
	return ecuacion;
}

void pretty_print_sols(int flags, output_t sol, vector<monomio> expresiones, int max_grade)
{
	string var, tmp = "";
	double r,i;
	
	for (size_t i = 0; i < expresiones.size(); i++)
	{
		var = expresiones[i].get_variable();
		if (var != "")
			break;
	}
	if (flags & STEPS)
	{
		cout << "Solving Steps:" << endl;
		//sol.steps.erase( unique( sol.steps.begin(), sol.steps.end() ), sol.steps.end() );
		for (size_t i=0; i < sol.steps.size(); i++)
		{
			if (sol.steps[i] == tmp)
				continue;
			tmp = sol.steps[i];
			//if (i < sol.guide.size())
			cout << sol.guide[i] << endl;
			cout << tmp << endl << endl;
		}
	}
	if (printer(expresiones) == "0=0")
	{
		cout << "All real numbers are solution for the ecuation" << endl;
		return;
	}
	else if (expresiones[0].get_variable() == "")
	{
		cout << "Does not exist solution for the ecuation" << endl;
		return;
	}
	cout << "Reduced form: " << printer(reduce_form(expresiones)) << endl;
	cout << "Polynomial degree: " << max_grade << endl;
	if (max_grade == 2)
	{
		if (sol.solutions[0].imaginary)
		{
			r = sol.solutions[0].sol.imaginary.real;
			i = sol.solutions[0].sol.imaginary.imaginary;
			cout << "Discriminant is strictly negative, the two complex solutions are:" << endl;
			cout << var << "₁" << "=";
			if (r)
				cout << r << (i < 0 ? "" : "+");
			cout << i << "i" << endl;
			r = sol.solutions[1].sol.imaginary.real;
			i = sol.solutions[1].sol.imaginary.imaginary;
			cout << var << "₂" << "=";
			if (r)
				cout << r << (i < 0 ? "" : "+");
			cout << i << "i" << endl;
		}
		else
		{
			if (sol.solutions[0].sol.real == sol.solutions[1].sol.real)
				cout << "Discriminant is zero, the two real solutions are:" << endl;
			else
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
}

int main(int argc, char **argv) {

	vector<monomio> expresiones;
	vector<string> steps;
	int  max_grade, flags = 0;
	string var;
	output_t sol;
	

	setlocale(LC_ALL, "");
	setlocale(LC_NUMERIC, "C");
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
	for (size_t i=0; i < expresiones.size();i++)
	{
		for (size_t j=i; j < expresiones.size();j++)
		{
			if (isalpha(expresiones[i].get_variable()[0]) && isalpha(expresiones[j].get_variable()[0]) && expresiones[i].get_variable() != expresiones[j].get_variable())
			{
				cout << "Multiple variables, i can't solve this" << endl;
				return 1;
			}
			
		}
	}
	if (!expresiones.size())
	{
		cout << "The expression \"" << argv[argc - 1] <<"\" is not a well formed polynomial expression" << endl;
		return -1;
	}
	sol = computatorv1(expresiones, max_grade, flags);
	pretty_print_sols(flags, sol, expresiones, max_grade);

	return 0;
}

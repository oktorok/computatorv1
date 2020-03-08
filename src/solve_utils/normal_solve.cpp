#include "computator.h"

static vector<monomio> prepare_final_expresion(string var, monomio numerator, monomio denominator)
{
	vector<monomio> expresion;
	monomio tmp;
	short sign;

	tmp.ini_monomio(var, 1, 0, 1, 1);
	expresion.push_back(tmp);
	tmp.ini_monomio("=", 0, -1, 1, 1);
	expresion.push_back(tmp);
	expresion.push_back(numerator);
	tmp.ini_monomio("/", 0, -1, 1, 1);
	expresion.push_back(tmp);
	expresion.push_back(denominator);
	return expresion;
}

static output_t real_solution(vector<monomio> ecuacion, output_t solution)
{
	solution_t sol;
	monomio num;
	string tmp;

	sol.imaginary = false;
	if (solution.solutions.size() && solution.solutions.back().sol.real == ecuacion.back().value)
		return solution;
	solution.steps.push_back(printer(ecuacion, NULL));
	ecuacion = solve_fractions(ecuacion);
	solution.steps.push_back(printer(ecuacion, NULL));
	sol.sol.real = ecuacion.back().value;
	solution.solutions.push_back(sol);
	return solution;
}

static output_t imaginary_solution(vector<monomio> ecuacion, output_t solution)
{
	solution_t sol;
	string var;
	
	sol.imaginary = true;
	solution.steps.push_back(printer(ecuacion, NULL));
	ecuacion = solve_fractions(ecuacion);
	var = ecuacion[0].get_variable();
	ecuacion[0].set_variable(var + "₁");
	solution.steps.push_back(printer(ecuacion, NULL));
	sol.sol.imaginary = create_complex(sub_vector(ecuacion, 2, 4));
	solution.solutions.push_back(sol);
	ecuacion[3].sign *= -1;
	ecuacion[0].set_variable(var + "₂");
	solution.steps.push_back(printer(ecuacion, NULL));
	sol.sol.imaginary = create_complex(sub_vector(ecuacion, 2, 4));
	solution.solutions.push_back(sol);
	return solution;
	
}

static vector<monomio> prepare_complex_expresion(monomio sumand, monomio radicand, monomio den)
{
	monomio tmp, slash, equal;
	vector<monomio> complex_expresion;

	tmp.ini_monomio("x", 1, 1, 1, 1);
	equal.ini_monomio("=", 0, -1, 1, 1);
	slash.ini_monomio("/", 0, -1, 1, 1);
	complex_expresion.push_back(tmp);
	complex_expresion.push_back(equal);
	complex_expresion.push_back(sumand);
	complex_expresion.push_back(slash);
	complex_expresion.push_back(den);
	radicand.set_variable("");
	den.set_variable("i");
	complex_expresion.push_back(radicand);
	complex_expresion.push_back(slash);
	complex_expresion.push_back(den);
	return complex_expresion;
}

static string print_numerator(vector<monomio> ecuacion, int &num_length, int var_length, int phase)
{
	stringstream tmpstrm, num;
	string numl, numr;
	int l;
	
	for (int i = 0; i < var_length; i++)
		tmpstrm << " ";
	tmpstrm << ecuacion[1].value * ecuacion[1].sign * -1;
	numl = tmpstrm.str();
	tmpstrm.str("");
	l = numl.length();
	for (int i = 0; i < l; i++)
		num << " ";
	if (phase == 2)
	{
		tmpstrm << "±i√";
	}
	else
		tmpstrm << "±√";
	if (phase == 1)
		tmpstrm << ecuacion[1].value * ecuacion[1].value - 4 * ecuacion[0].value * ecuacion[0].sign * ecuacion[2].value * ecuacion[2].sign;
	else if (phase == 2)
	{
		tmpstrm << -1 * (ecuacion[1].value * ecuacion[1].value - 4 * ecuacion[0].value * ecuacion[0].sign * ecuacion[2].value * ecuacion[2].sign);
		num << " ";
		phase = 0;
	}
	else
		tmpstrm << ecuacion[1].value << SUPERINDEX_2 << "-4*" << ecuacion[0].value * ecuacion[0].sign << "*" << ecuacion[2].value * ecuacion[2].sign;
	numr = tmpstrm.str();
	l = numr.length();
	for (int i = 0; i < l - 6 + phase; i++)
		num << "_";
	num_length = numr.length() + numl.length();
	num << "\n" << numl << numr;
	return num.str();
}

static string print_denominator(vector<monomio> ecuacion, int num_length, int phase)
{
	int j = 0, l;
	stringstream den, tmpstrm;
	string tmp;

	if (phase)
		tmpstrm << 2 * ecuacion[0].value * ecuacion[0].sign;
	else
		tmpstrm << "2*" << ecuacion[0].value * ecuacion[0].sign;
	tmp = tmpstrm.str();
	l = tmp.length();
	while (j < num_length)
	{
		if (j == (num_length - l)/2)
		{
			den << tmp;
			j += l;
		}
		else
		{
			den << " ";
			j += 1;
		}
	}
	return den.str();
}

static string printer2grade(vector<monomio> ecuacion, int phase)
{
	stringstream full, tmpstrm;
	string var, den, num, tmp;
	int  num_length, l;

	tmpstrm << ecuacion[0].get_variable() << "=";
	tmp = tmpstrm.str();
	l = tmp.length();
	num = print_numerator(ecuacion, num_length, l, phase);
	den = print_denominator(ecuacion, num_length, phase);
	for (int i = 0; i < l; i++)
		full << " ";
	full << num << "\n";
	full << tmp;
	l = num.length() / 2 - 3;
	for (int i = 0; i < l; i++)
		full << "―";
	full << "\n" << den;
	return full.str();
}

output_t normal_solve(vector<monomio> ecuacion, output_t solution)
{
	monomio sumand, radicand, den, num;
	string tmp;
	
	solution.steps.push_back(printer(ecuacion, NULL));

	sumand = calc_sumand(ecuacion[1]);
	radicand = calc_radicand(ecuacion[0], ecuacion[1], ecuacion[2]);
	den = calc_den(ecuacion[0]);

	solution.steps.push_back(printer2grade(ecuacion, 0));
	radicand.value = mySqrt(radicand.value);
	if (radicand.sign == -1)
	{
		radicand.sign = 1;
		solution.steps.push_back(printer2grade(ecuacion, 1));
		solution.steps.push_back(printer2grade(ecuacion, 2));
		ecuacion = prepare_complex_expresion(sumand, radicand, den);
		solution = imaginary_solution(ecuacion, solution);
	}
	else
	{

		num = calc_num(sumand, radicand, true);
		solution.steps.push_back(printer2grade(ecuacion, 1));
		ecuacion = prepare_final_expresion(ecuacion[0].get_variable(), num, den);
		solution = real_solution(ecuacion, solution);
		num = calc_num(sumand, radicand, false);
		ecuacion = prepare_final_expresion(ecuacion[0].get_variable(), num, den);
		solution = real_solution(ecuacion, solution);
	}

	return solution;
}

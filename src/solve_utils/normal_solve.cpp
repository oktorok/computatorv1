#include "computator.h"

static vector<monomio> prepare_final_expresion(string var, monomio numerator, monomio denominator)
{
	vector<monomio> expresion;
	monomio tmp;

	tmp.ini_monomio(var, 1, 0, 1);
	expresion.push_back(tmp);
	tmp.ini_monomio("=", 0, -1, 1);
	expresion.push_back(tmp);
	expresion.push_back(numerator);
	tmp.ini_monomio("/", 0, -1, 1);
	expresion.push_back(tmp);
	expresion.push_back(denominator);
	return expresion;
}

static output_t real_solution(vector<monomio> ecuacion, output_t solution, int flags, string sol_num)
{
	solution_t sol;
	monomio num;
	string tmp;

	sol.imaginary = false;
	if (solution.solutions.size() && solution.solutions.back().sol.real == ecuacion.back().value)
		return solution;
	if (flags & STEPS)
	{
		tmp = "Solving Numerator Solution " + sol_num;
		solution.guide.push_back(tmp);
		solution.steps.push_back(printer(ecuacion));
	}
	ecuacion = solve_fractions(ecuacion);
	if (flags & STEPS)
	{
		tmp = "Solution " + sol_num;
		solution.guide.push_back(tmp);
		solution.steps.push_back(printer(ecuacion));
	}
	sol.sol.real = ecuacion.back().value * ecuacion.back().sign;
	solution.solutions.push_back(sol);
	return solution;
}

static output_t imaginary_solution(vector<monomio> ecuacion, output_t solution, int flags)
{
	solution_t sol;
	monomio tmp;
	string var;
	
	sol.imaginary = true;
	if (flags & STEPS)
	{
		tmp.ini_monomio("±", 0, -1, 0);
		ecuacion.insert(ecuacion.begin()+5, tmp);
		solution.guide.push_back("Spliting in Real and Complex Part:");
		solution.steps.push_back(printer(ecuacion));
		//		ecuacion.erase(ecuacion.begin()+5);
	}
	ecuacion = solve_fractions(ecuacion);
	var = ecuacion[0].get_variable();
	if (flags & STEPS)
	{
		solution.guide.push_back("Solving Fractions:");
		solution.steps.push_back(printer(ecuacion));
		ecuacion.erase(ecuacion.begin() + 3);
	}
	ecuacion[0].set_variable(var + "₁");
	if (flags & STEPS)
	{
		solution.guide.push_back("First Solution:");
		solution.steps.push_back(printer(ecuacion));
	}
	sol.sol.imaginary = create_complex(sub_vector(ecuacion, 2, 4));
	solution.solutions.push_back(sol);
	ecuacion[3].sign *= -1;
	ecuacion[0].set_variable(var + "₂");
	if (flags & STEPS)
	{
		solution.guide.push_back("Second Solution");
		solution.steps.push_back(printer(ecuacion));
	}
	sol.sol.imaginary = create_complex(sub_vector(ecuacion, 2, 4));
	solution.solutions.push_back(sol);
	return solution;
	
}

static vector<monomio> prepare_complex_expresion(monomio sumand, monomio radicand, monomio den)
{
	monomio tmp, slash, equal;
	vector<monomio> complex_expresion;

	tmp.ini_monomio("x", 1, 1, 1);
	equal.ini_monomio("=", 0, -1, 1);
	slash.ini_monomio("/", 0, -1, 1);
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

static string print_numerator(vector<monomio> ecuacion, int var_length, int phase)
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
		num << "   ";
	}
	else
	{
		tmpstrm << "±√";
		num << "  ";
	}
	if (phase == 1)
		tmpstrm << ecuacion[1].value * ecuacion[1].value - 4 * ecuacion[0].value * ecuacion[0].sign * ecuacion[2].value * ecuacion[2].sign;
	else if (phase == 2)
	{
		tmpstrm << -1 * (ecuacion[1].value * ecuacion[1].value - 4 * ecuacion[0].value * ecuacion[0].sign * ecuacion[2].value * ecuacion[2].sign);
		phase = 0;
	}
	else
		tmpstrm << ecuacion[1].value << SUPERINDEX_2 << "-4*" << ecuacion[0].value * ecuacion[0].sign << "*" << ecuacion[2].value * ecuacion[2].sign;
	numr = tmpstrm.str();
	l = numr.length();
	for (int i = 0; i < l - 6 + phase; i++)
		num << "_";
	num << "\n" << numl << numr;
	return num.str();
}

static string print_denominator(vector<monomio> ecuacion, int num_length, int var_length, int phase)
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
	for (int i = 0; i < var_length; i++)
		den << " ";
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
	num = print_numerator(ecuacion, l, phase);
	num_length = num.length() / 2 - l - 2;
	den = print_denominator(ecuacion, num_length, l, phase);
	full << num << "\n";
	full << tmp;
	for (int i = 0; i < num_length; i++)
		full << "―";
	full << "\n" << den;
	return full.str();
}

output_t normal_solve(vector<monomio> ecuacion, output_t solution, int flags)
{
	monomio sumand, radicand, den, num;
	string tmp;
	
	//if (flags & STEPS)
	//{
	//	solution.guide.push_back("Seconddddd Grade Solving Formula:");
	//	solution.steps.push_back(printer(ecuacion));
	//}
	sumand = calc_sumand(ecuacion[1]);
	radicand = calc_radicand(ecuacion[0], ecuacion[1], ecuacion[2]);
	den = calc_den(ecuacion[0]);

	if (flags & STEPS)
	{
		solution.guide.push_back("Second Grade Solving Formula:");
		solution.steps.push_back(printer2grade(ecuacion, 0));
	}
	radicand.value = mySqrt(radicand.value);
	if (flags & STEPS)
	{
		solution.guide.push_back("Solving Radicand:");
		solution.steps.push_back(printer2grade(ecuacion, 1));
	}
	if (radicand.sign == -1)
	{
		radicand.sign = 1;
		if (flags & STEPS)
		{
			solution.guide.push_back("Changing Sign to Radicand to i");
			solution.steps.push_back(printer2grade(ecuacion, 2));
		}
		ecuacion = prepare_complex_expresion(sumand, radicand, den);
		solution = imaginary_solution(ecuacion, solution, flags);
	}
	else
	{
		tmp = ecuacion[0].get_variable();
		num = calc_num(sumand, radicand, true);
		//if (flags & STEPS)
		//	solution.steps.push_back(printer2grade(ecuacion, 1));
		ecuacion = prepare_final_expresion(ecuacion[0].get_variable(), num, den);
		ecuacion[0].set_variable(tmp + "₁");
		solution = real_solution(ecuacion, solution, flags, "1");
		num = calc_num(sumand, radicand, false);
		ecuacion = prepare_final_expresion(ecuacion[0].get_variable(), num, den);
		ecuacion[0].set_variable(tmp + "₂");
		solution = real_solution(ecuacion, solution, flags, "2");
	}

	return solution;
}

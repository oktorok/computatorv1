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

output_t normal_solve(vector<monomio> ecuacion, output_t solution)
{
	monomio sumand, radicand, den, num;
	solution_t sol;
	string tmp;
	
	solution.steps.push_back(printer(ecuacion, NULL));

	sumand = calc_sumand(ecuacion[1]);
	radicand = calc_radicand(ecuacion[0], ecuacion[1], ecuacion[2]);
	den = calc_den(ecuacion[0]);

	//PRINT
	sol.imaginary = false;
	if (radicand.sign == -1)
		sol.imaginary = true;
	radicand.value = mySqrt(radicand.value);
	num = calc_num(sumand, radicand, true);
	//PRINT
	ecuacion = prepare_final_expresion(ecuacion[0].get_variable(), num, den);
	solution.steps.push_back(printer(ecuacion, NULL));
	ecuacion = solve_fractions(ecuacion);
	solution.steps.push_back(printer(ecuacion, NULL));
	sol.sol.real = ecuacion.back().value;
	solution.solutions.push_back(sol);

	num = calc_num(sumand, radicand, false);
	ecuacion = prepare_final_expresion(ecuacion[0].get_variable(), num, den);
	tmp = printer(ecuacion, NULL);
	ecuacion = solve_fractions(ecuacion);
	if (ecuacion.back().value == sol.sol.real)
		return solution;
	solution.steps.push_back(tmp);
	solution.steps.push_back(printer(ecuacion, NULL));
	sol.sol.real = ecuacion.back().value;
	solution.solutions.push_back(sol);
	return solution;
}

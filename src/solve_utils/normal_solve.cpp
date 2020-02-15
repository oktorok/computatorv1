#include "computator.h"

static value_u check_type(value_u value, char &value_type)
{
	double trash;

	if (value_type == 'd')
	{
		if (!modf(value.d, &trash))
		{
			value.l = (long)value.d;
			value_type = 'l';
		}
	}
	return value;
}

static vector<monomio> prepare_final_expresion(string var, monomio numerator, monomio denominator)
{
	vector<monomio> expresion;
	monomio tmp;
	short sign;

	tmp.ini_monomio("", numerator, 0, numerator_type, 1, 1);
	expresion.push_back(tmp);
	tmp.ini_monomio("/", (value_u){0}, -1, 'l', 1, 1);
	expresion.push_back(tmp);
	tmp.ini_monomio(var, denominator, 0, denominator_type, 1, 1);
	expresion.push_back(tmp);
	tmp.ini_monomio("=", (value_u){0}, -1, 'l', 1, 1);
	expresion.push_back(tmp);
	tmp.ini_monomio("", (value_u){0}, 0, 'l', 1, 1);
	expresion.push_back(tmp);
	return expresion;
}

output_t normal_solve(vector<monomio> ecuacion, output_t solution)
{
	monomio sumand, radicand, den, num;
	//char sumand_type, radicand_type, den_type, num_type;
	int t = 0;
	value_u tmp;
	solution_t sol;

	
	ecuacion = move_indepterm(ecuacion);
	solution.steps.push_back(printer(ecuacion, NULL));
	if (ecuacion[0].value_type == 'l')
		t |= 1 << 2;
	if (ecuacion[1].value_type == 'l')
		t |= 1 << 1;
	if (ecuacion[2].value_type == 'l')
		t |= 1;

	switch (t)
	{
	case 0:
		sumand.value.d = ecuacion[1].value.d;
		sumand.sign = -1 * ecuacion[1].sign;
		sumand.value_type = 'd';
		den.value.d = 2 * ecuacion[0].value.d;
		den.sign = ecuacion[0].sign;
		den.value_type = 'd';
		radicand.value.d = ecuacion[1].value.d * ecuacion[1].value.d - 4 * ecuacion[0].value.d * ecuacion[2].value.d;
		radicand.sign = 1;
		if (signbit(radicand.value.d)
		{
		    radicand.value.d *= -1;
		    radicand.sign = -1;
		}
		radicand.value_type = 'd';
		break;

	case 4:
		sumand.value.d = -1 * ecuacion[1].value.d * ecuacion[1].sign;
		sumand.value_type = 'd';
		den.value.l = 2 * ecuacion[0].value.l;
		den.value_type = 'l';
		radicand.value.d = ecuacion[1].value.d * ecuacion[1].value.d - 4 * ecuacion[0].value.l * ecuacion[2].value.d;
		radicand.value_type = 'd';
		break;

	case 2:
		sumand.value.l = -1 * ecuacion[1].value.l * ecuacion[1].sign;
		sumand.value_type = 'l';
		den.value.d = 2 * ecuacion[0].value.d;
		den.value_type = 'd';
		radicand.value.d = ecuacion[1].value.l * ecuacion[1].value.l - 4 * ecuacion[0].value.d * ecuacion[2].value.d;
		radicand.value_type = 'd';
		break;
	case 1:
		sumand.value.d = -1 * ecuacion[1].value.d * ecuacion[1].sign;
		sumand.value_type = 'd';
		den.value.d = 2 * ecuacion[0].value.d;
		den.value_type = 'd';
		radicand.value.d = ecuacion[1].value.d * ecuacion[1].value.d - 4 * ecuacion[0].value.d * ecuacion[2].value.l;
		radicand.value_type = 'd';
		break;
		
	case 3:
		sumand.value.l = -1 * ecuacion[1].value.l * ecuacion[1].sign;
		sumand.value_type = 'l';
		den.value.d = 2 * ecuacion[0].value.d;
		den.value_type = 'd';
		radicand.value.d = ecuacion[1].value.l * ecuacion[1].value.l - 4 * ecuacion[0].value.d * ecuacion[2].value.l;
		radicand.value_type = 'd';
		break;
	case 5:
		sumand.value.d = -1 * ecuacion[1].value.d * ecuacion[1].sign;
		sumand.value_type = 'd';
		den.value.l = 2 * ecuacion[0].value.l;
		den.value_type = 'l';
		radicand.value.d = ecuacion[1].value.d * ecuacion[1].value.d - 4 * ecuacion[0].value.l * ecuacion[2].value.l;
		radicand.value_type = 'd';
		break;
	case 6:
		sumand.value.l = -1 * ecuacion[1].value.l * ecuacion[1].sign;
		sumand.value_type = 'l';
		den.value.l = 2 * ecuacion[0].value.l;
		den.value_type = 'l';
		radicand.value.d = ecuacion[1].value.l * ecuacion[1].value.l - 4 * ecuacion[0].value.l * ecuacion[2].value.d;
		radicand.value_type = 'd';
		break;

	case 7:
		sumand.value.l = -1 * ecuacion[1].value.l * ecuacion[1].sign;
		sumand.value_type = 'l';
		den.value.l = 2 * ecuacion[0].value.l;
		den.value_type = 'l';
		radicand.value.l = ecuacion[1].value.l * ecuacion[1].value.l - 4 * ecuacion[0].value.l * ecuacion[2].value.l;
		radicand.value_type = 'l';
		break;
	}
	den = check_type(den, den.value_type);
	radicand = check_type(radicand, radicand.value_type);
	//PRINT
	sol.imaginary = false;
	if ((radicand.value_type == 'd' && radicand.value.d < 0) || (radicand.value_type == 'l' && radicand.value.l < 0))
		sol.imaginary = true;

		
	
	radicand = mySqrt(radicand, radicand.value_type);
	switch(t)
	{
	case 0:
	case 1:
		num.value_type = 'd';
		num.value.d = sumand.value.d + radicand.value.d;
		num = check_type(num, num.value_type);
		//PRINT
		ecuacion = prepare_final_expresion(ecuacion[0].get_variable(), num, num.value_type, den, den_type);
		solution.steps.push_back(printer(ecuacion, NULL));
		ecuacion = solve_fractions(ecuacion);
		solution.steps.push_back(printer(ecuacion, NULL));
		return solution;

		num.d = sumand.value.d - radicand.value.d;
		num = check_type(num, num.value_type);
		//PRINT
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		num.value_type = 'l';
		num.value.l = sumand.value.l + radicand.value.l;
		ecuacion = prepare_final_expresion(ecuacion[0].get_variable(), num, den);
		solution.steps.push_back(printer(ecuacion, NULL));
		ecuacion = solve_fractions(ecuacion);
		solution.steps.push_back(printer(ecuacion, NULL));
		return solution;
		break;
	}
	cout << t << endl;
	
	return solution;	
}

#include "computator.h"

static value_u check_division(value_u a, char type_a, value_u b, char &type_b)
{
	value_u ret;
 	if (type_a == type_b)
	{
		if (type_a == 'd')
		{
			if (fmod(a.d, b.d))
			{
				type_b = 'd';
				ret.d = a.d/b.d;
			}
			else
			{
				type_b = 'l';
				ret.l = (long)a.d/b.d;
			}
		}
		else
		{
			if (a.l % b.l)
			{
				type_b = 'd';
				ret.d = (double)a.l/b.l;
			}
			else
			{
				type_b = 'l';
				ret.l = a.l/b.l;
			}
		}
	}
	else if (type_a == 'l')
	{
		if (fmod(a.l, b.d))
	       	{
			type_b = 'd';
			ret.d = a.l/b.d;
		}
		else
		{
			type_b = 'l';
			ret.l = a.l/b.d;
		}
	}
	else if (fmod(a.d, b.l))
	{
		type_b = 'd';
		ret.d = a.d/b.l;
	}
	else
	{
		type_b = 'l';
		ret.l = a.d/b.l;
	}
	return ret;
	
}

static void go_div(vector<monomio> &ecuacion)
{
	vector<monomio>::iterator it1;
	monomio tmp;

	it1 = ecuacion.begin() + ecuacion.size() - 1;
	ecuacion.insert(it1, ecuacion.back());
	ecuacion.back().value = ecuacion[0].value;
	ecuacion.back().value_type = ecuacion[0].value_type;
	tmp.ini_monomio("/", (value_u){0}, -1, 'l', 0, 0);
	ecuacion.insert(it1 + 1, tmp);
	ecuacion[0].value.l = 1;
	ecuacion[0].value_type = 'l';
	//return ecuacion;
}

static void move_indepterm(vector<monomio> &ecuacion)
{
	vector<monomio>::iterator it1;

	it1 = ecuacion.begin() + ecuacion.size() - 3;
	ecuacion.back() = ecuacion[ecuacion.size() - 3];
	ecuacion.back().side = -1;
	ecuacion.back().sign *= -1;
	ecuacion.erase(it1);	
}

static value_u solv_first_grade(vector<monomio> ecuacion, vector<string> &steps, char &value_type)
{
	value_u solution;
	stringstream ss;

	move_indepterm(ecuacion);
	steps.push_back(printer(ecuacion, NULL));
	go_div(ecuacion);
	steps.push_back(printer(ecuacion,NULL));
	value_type = ecuacion[0].value_type;
	solution = check_division(ecuacion[2].value, ecuacion[2].value_type, ecuacion[0].value, value_type);
	ss << ecuacion[0].get_variable() << "=";
	if (value_type == 'l')
	{
		solution.l *= ecuacion[2].sign * ecuacion[0].sign;
		ss << solution.l;
	}
	else
	{
		solution.d *= ecuacion[2].sign * ecuacion[0].sign;
		ss << solution.d;
	}
	steps.push_back(ss.str());	
	return solution;
}


static solution_t * solv_second_grade(vector<monomio> ecuacion, vector<string> &steps)
{
	stringstream ss;
	string t = "00";
	vector<monomio>::iterator it1;
	monomio tmp;
	int i = -1;
	solution_t *solution = new solution_t[2];
	switch (ecuacion.size())
	{
	case 4:
		move_indepterm(ecuacion);
		steps.push_back(printer(ecuacion, NULL));
		go_div(ecuacion);
		steps.push_back(printer(ecuacion, NULL));
		//////////////////////////////////////////////////
		solution[0].real = check_division(ecuacion[2].value, ecuacion[2].value_type, ecuacion[0].value, (solution[0].value_type = ecuacion[0].value_type));
		if (!ecuacion[2].get_grade())
		{
			
			if (ecuacion[0].sign * ecuacion[2].sign < 0)
				cout << "IMAGINARIO" << endl;
			else
			{
				solution[0].real = mySqrt(solution[0].real, solution[0].value_type);
				solution[1].real = solution[0].real;
				solution[1].value_type = solution[0].value_type;
				if (solution[0].value_type == 'l')
				{
					solution[0].real.l *= ecuacion[2].sign * ecuacion[0].sign;
					solution[1].real.l *= ecuacion[2].sign * ecuacion[0].sign * -1;
					ss << ecuacion[0].get_variable() << "=";
					ss << solution[0].real.l;
					steps.push_back(ss.str());
					ss.str("");
					ss << ecuacion[0].get_variable() << "=";
					ss << solution[1].real.l;
					steps.push_back(ss.str());
				}
				else
				{
					solution[0].real.d *= ecuacion[2].sign * ecuacion[0].sign;
					solution[1].real.d *= ecuacion[2].sign * ecuacion[0].sign * -1;
					ss << ecuacion[0].get_variable() << "=";
					ss << solution[0].real.d;
					steps.push_back(ss.str());
					ss.str("");
					ss << ecuacion[0].get_variable() << "=";
					ss << solution[1].real.d;
					steps.push_back(ss.str());
				}
			}
		}
		else
		{
			solution[0].real.l = 0;
			solution[1].real = solv_first_grade(ecuacion, steps, solution[1].value_type);
		}	
		break;
	}
	return solution;
}

value_u solve(vector<monomio> ecuacion, vector<string> &steps, char &value_type)
{
	value_u result;

	switch (ecuacion[0].get_grade())
	{
	case 0:
		result = (value_u){0};
		break;
	case 1:
		result = solv_first_grade(ecuacion, steps, value_type);
		break;
	case 2:
		solv_second_grade(ecuacion, steps);
		break;
	default:
		result = (value_u){0};
		printf("Grade more than 2, expression not solvable in computator-v1");
		break;
	}
	return (result);
}

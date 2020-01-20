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

static value_u solv_first_grade(vector<monomio> ecuacion, vector<string> &steps, char &value_type)
{
	value_u solution;
	stringstream ss;
	string t = "00";
	vector<monomio>::iterator it1;

	it1 = ecuacion.begin() + ecuacion.size() - 3;
	ecuacion.back() = ecuacion[ecuacion.size() - 3];
	ecuacion.back().side = -1;
	ecuacion.back().sign *= -1;
	ecuacion.erase(it1);
	steps.push_back(printer(ecuacion, NULL));
	t[0] = ecuacion[2].value_type;
	t[1] = ecuacion[0].value_type;
	ss << ecuacion[0].get_variable() << "=";
	if (t == "ll")
		ss << ecuacion[2].value.l << "/" << ((ecuacion[0].sign < 0) ? "-" : "") << ecuacion[0].value.l;
	else if (t == "dd")
		ss << ecuacion[2].value.d << "/" << ((ecuacion[0].sign < 0) ? "-" : "") << ecuacion[0].value.d;
	else if (t == "ld")
		ss << ecuacion[2].value.l << "/" << ((ecuacion[0].sign < 0) ? "-" : "") << ecuacion[0].value.d;
	else
		ss << ecuacion[2].value.d << "/" << ((ecuacion[0].sign < 0) ? "-" : "") << ecuacion[0].value.l;
	steps.push_back(ss.str());
	ss.str("");
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

// static float float_mod(float a, float b)
// {
// 	float mod; 
// 	if (a < 0) 
// 		mod = -a; 
// 	else
// 		mod = a; 
// 	if (b < 0) 
// 		b = -b; 
// 	while (mod >= b) 
// 		mod = mod - b; 
// 	if (a < 0) 
// 		return -mod; 

// 	return mod; 
// } 

// static void reduce_fraction(float *numerador, float *denominador)
// {
// 	int prime = 2;
// 	int sign1 = 1, sign2 = 1; 

// 	if (*numerador < 0)
// 	{
// 		*numerador *= -1;
// 		sign1 = -1;
// 	}
// 	if (*denominador < 0)
// 	{
// 		*denominador *= -1;
// 		sign2 = -2;
// 	}
// 	while (*numerador >= prime * prime && *denominador >= prime * prime)
// 	{
// 		if (!float_mod(*numerador, prime) && !float_mod(*denominador, prime))
// 		{
// 			*numerador /= prime;
// 			*denominador /= prime;
// 		}
// 		else
// 			prime++;
// 	}
// 	*numerador *= sign1;
// 	*denominador *= sign2;
// }

// static void solv_second_grade(vector<monomio> *ecuacion, string **result, vector<string> *steps)
// {
// 	float a, b, c, radicando, numerador, denominador;
// 	stringstream ss;
// 	int i = -1;
// 	switch (ecuacion->size())
// 	{
// 	case 2:
// 		if (!(a = (*ecuacion)[0].value))
// 			a = (*ecuacion)[0].frac_value;
// 		if (!(b = (*ecuacion)[1].value))
// 			b = (*ecuacion)[1].frac_value;

// 		if ((*ecuacion)[1].get_grade() == 0)
// 		{
// 			if (-b / a < 0)
// 			{
// 				if (-b / a == -1)
// 					ss << "i";
// 				else
// 					ss << "i|" << b / a ;
// 			}
// 			else
// 				ss << mySqrt(-b / a);
// 			(*result)[0] = ss.str();
// 			(*result)[1] =  "-" + (*result)[0];
// 		}
// 		else
// 		{
// 			(*result)[0] = "0";
// 			solv_first_grade(ecuacion, *result + 1, steps);
// 		}	
// 		break;
		
// 	case 3:
// 		if (!(a = (*ecuacion)[0].value))
// 			a = (*ecuacion)[0].frac_value;
// 		if (!(b = (*ecuacion)[1].value))
// 			b = (*ecuacion)[1].frac_value;
// 		if (!(c = (*ecuacion)[2].value))
// 			c = (*ecuacion)[2].frac_value;
		
// 		radicando = myPow(b, 2) - 4 * a * c;
		
// 		if (radicando < 0)
// 		{
// 			radicando *= -1;
// 			ss << -b << "+i|" << radicando << "/" << 2 * a;
// 			(*result)[0] = ss.str();
// 			ss.str("");
// 			ss << -b << "-i|" << radicando << "/" << 2 * a;
// 			(*result)[1] = ss.str();
// 		}
// 		else
// 		{
// 			c = mySqrt(radicando);
// 			denominador = 2 * a;
// 			/*if (c == radicando)
// 			{
// 					ss << -b << "+" << "|" << radicando << "/" << 2 * a;
// 					(*result)[0] = ss.str();
// 					ss.str("");
// 					ss << -b << "-" << "|" << radicando << "/" << 2 * a;
// 					(*result)[1] = ss.str();
// 					break;
// 					}*/
// 			while (++i < 2)
// 			{							
// 				numerador = -b + c;
// 				if (!(float_mod(numerador, denominador)))
// 					ss << numerador / denominador;
// 				else
// 				{
// 					reduce_fraction(&numerador, &denominador);
// 					ss << numerador << "/" << denominador;
// 				}
// 				(*result)[i] = ss.str();
// 				ss.str("");
// 				c *= -1;
// 			}
// 		}
// 		break;
// 	default:
// 		cout << "Not solvable ecuation" << endl;
// 		delete [] *result;
// 		*result = NULL;
// 		exit(-1);
// 	}
// }

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
		//result = solv_second_grade(ecuacion, steps);
		break;
	default:
		result = (value_u){0};
		printf("Grade more than 2, expression not solvable in computator-v1");
		break;
	}
	return (result);
}

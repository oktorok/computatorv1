#include "computator.h"

static void solv_first_grade(vector<monomio> *ecuacion, string *result)
{
	float a, b;
	stringstream ss;

	a = (*ecuacion)[0].value;
	if (!a)
			a = (*ecuacion)[0].frac_value;
	b = (*ecuacion)[1].value;
	if (!b)
			b = (*ecuacion)[1].frac_value;
	if (b / a)
		ss << (-1) * b / a;
	else
		ss << b / a;
	result[0] = ss.str();
}

static void reduce_fraction(int *numerador, int *denominador)
{
	int prime = 2;
	int sign1 = 1, sign2 = 1; 

	if (*numerador < 0)
	{
		*numerador *= -1;
		sign1 = -1;
	}
	if (*denominador < 0)
	{
		*denominador *= -1;
		sign2 = -2;
	}
	while (*numerador >= prime * prime && *denominador >= prime * prime)
	{
		if (!(*numerador % prime) && !(*denominador % prime))
		{
			*numerador /= prime;
			*denominador /= prime;
		}
		else
			prime++;
	}
	*numerador *= sign1;
	*denominador *= sign2;
}

static void solv_second_grade(vector<monomio> *ecuacion, string **result)
{
	float a, b, c, radicando;
	stringstream ss;
	int numerador, denominador, i = -1;
	switch (ecuacion->size())
	{
	case 2:
		if (!(a = (*ecuacion)[0].value))
			a = (*ecuacion)[0].frac_value;
		if (!(b = (*ecuacion)[1].value))
			b = (*ecuacion)[1].frac_value;

		if ((*ecuacion)[1].get_grade() == 0)
		{
			if (-b / a < 0)
			{
				if (-b / a == -1)
					ss << "i";
				else
					ss << "i|" << b / a ;
			}
			else
				ss << mySqrt(-b / a);
			(*result)[0] = ss.str();
			(*result)[1] =  "-" + (*result)[0];
		}
		else
		{
			(*result)[0] = "0";
			solv_first_grade(ecuacion, *result + 1);
		}	
		break;
		
	case 3:
		if (!(a = (*ecuacion)[0].value))
			a = (*ecuacion)[0].frac_value;
		if (!(b = (*ecuacion)[1].value))
			b = (*ecuacion)[1].frac_value;
		if (!(c = (*ecuacion)[2].value))
			c = (*ecuacion)[2].frac_value;
		
		radicando = myPow(b, 2) - 4 * a * c;
		if (radicando < 0)
		{
			radicando *= -1;
			ss << -b << "+i|" << radicando << "/" << 2 * a;
			(*result)[0] = ss.str();
			ss.str("");
			ss << -b << "-i|" << radicando << "/" << 2 * a;
			(*result)[1] = ss.str();
		}
		else
		{
			c = mySqrt(radicando);
			denominador = 2 * a;
			if (c == radicando)
			{
					ss << -b << "+" << "|" << radicando << "/" << 2 * a;
					(*result)[0] = ss.str();
					ss.str("");
					ss << -b << "-" << "|" << radicando << "/" << 2 * a;
					(*result)[1] = ss.str();
					break;
			}
			while (++i < 2)
			{							
				numerador = -b + c;
				if (!(numerador % denominador))
					ss << numerador / denominador;
				else
				{
					reduce_fraction(&numerador, &denominador);
					ss << numerador << "/" << denominador;
				}
				(*result)[i] = ss.str();
				ss.str("");
				c *= -1;
			}
		}
		break;
	default:
		cout << "Not solvable ecuation" << endl;
		delete [] *result;
		*result = NULL;
		exit(-1);
	}
}

string *solve(vector<monomio> *ecuacion)
{
	string *result;

	switch ((*ecuacion)[0].get_grade())
	{
	case 0:
		result = NULL;
		break;
	case 1:
		result = new string[1];
		solv_first_grade(ecuacion, result);
		break;
	case 2:
		result = new string[2];
		solv_second_grade(ecuacion, &result);
		break;
	default:
		result = NULL;
		printf("Grade more than 2, expression not solvable in computator-v1");
		exit(-1);
		break;
	}
	return (result);
}

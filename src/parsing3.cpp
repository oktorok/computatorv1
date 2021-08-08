#include "computator.h"
#include <stdio.h>

#define NUMBER 0
#define OPERATION 2
#define CHAR 1
#define EQUAL 3
#define SLASH 4
#define POTENCE 5
#define SPACE 7
#define ERROR 6
#define PRODUCT 8

static int class_character(char a)
{
	if (isdigit(a))
		return NUMBER;
	else if (isalpha(a))
		return CHAR;
	else if (a == '-' || a == '+')
		return OPERATION;
	else if (a == '=')
		return EQUAL;
	else if (a == '/')
		return SLASH;
	else if (a == '^')
		return POTENCE;
	else if (isspace(a))
		return SPACE;
	else if (a == '*')
		return PRODUCT;
	else
		return ERROR;
}

vector<monomio> parsing3(string expresion, int &max_grade)
{
	vector<monomio> ecuacion;
	int i = 0, expresion_l = expresion.length(), t, old_t, grade = 0;
	short sign = 1;
	string var = "";
	double value = 1;
	bool value_set = false, equal_set = false;
	short add = 0, exist_equal = 0;
	monomio tmp;

	max_grade = 1;
	while(i < expresion_l)
	{
		t = class_character(expresion[i]);
		switch (t)
	       	{
		case SLASH:
		case EQUAL:
		case OPERATION:
			if (i && !add)
			{
				if (!value_set && var == "")
				{
					cout << "No value neither variable detected" << endl;
					return vector<monomio>();
				}
				tmp.ini_monomio(var, value, grade, sign);
				ecuacion.push_back(tmp);
				value_set = false;
			}
			if (t == EQUAL)
			{
				if (!i)
				{
					cout << "No left side found" << endl;
					return vector<monomio>();
				}
				else if (old_t == PRODUCT)
				{
					cout << "Missing product" << endl;
					return vector<monomio>();
				}
				exist_equal += 1;
				add = 2;
				tmp.ini_monomio("=", 0, -1, 0);
				ecuacion.push_back(tmp);
			}
			else if (t == SLASH)
			{
				if (var != "")
				{
					cout << "Variable on fraction not implemented" << endl;
					return vector<monomio>();
				}
				add = 2;
				tmp.ini_monomio("/", 0, -1, 0);
				ecuacion.push_back(tmp);	
			}			
			sign = 1;
			if (expresion[i++] == '-')
				sign = -1;
			grade = 0;
			var = "";
			value = 1;
			break;
		case NUMBER:
			if (value_set)
			{
				cout << "Coefficient as expression not implemented" << endl;
				return vector<monomio>();
			}
			if (exist_equal > 0)
				equal_set = true;
			value = take_value(i, expresion);
			value_set = true;
			break;
		case CHAR:
			if (exist_equal > 0)
				equal_set = true;
			if (var != "")
			{
				cout << "No product between variables allowed" << endl;
				return vector<monomio>();
			}
			var = take_var(i, expresion);
			grade = 1;
			break;
		case SPACE:
			i++;
			add++;
			break;
		case POTENCE:
			if (var == "")
			{
				cout << "No variable for exponent available" << endl;
				return vector<monomio>();
			}
			if (!isdigit(expresion[i + 1]))
			{
				cout << "No value for exponent available" << endl;
				return vector<monomio>();
			}
			grade = take_grade(i, expresion);
			if (!grade)
				var = "";
			if (grade > max_grade)
				max_grade = grade;
			break;
		case PRODUCT:
			// if (var != "" || !value_set)
			// {
			// 	cout << "Product only available for coefficients" << endl;
			// 	return vector<monomio>();
			// }
			i++;
			break;
		default:

			return vector<monomio>();
		}
		add = (add ? add - 1 : 0);
		if (t != SPACE)
			old_t = t;
	}
	if (exist_equal != 1)
	{
		if (exist_equal == 0)
			cout << "Missing equality" << endl;
		else if (exist_equal > 1)
			cout << "Multiple equalities" << endl;
		return vector<monomio>();
	}
	else if (!equal_set)
	{
		cout << "Missing right equal side" << endl;
		return vector<monomio>();
	}
	tmp.ini_monomio(var, value, grade, sign);
	ecuacion.push_back(tmp);
	return ecuacion;
}

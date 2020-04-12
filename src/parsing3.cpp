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
	int i = 0, expresion_l = expresion.length(), t, grade = 0;
	short sign = 1;
	string var = "";
        double value = 1;
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
				tmp.ini_monomio(var, value, grade, sign);
				ecuacion.push_back(tmp);
			}
    			sign = 1;
			if (expresion[i++] == '-')
				sign = -1;
			grade = 0;
			var = "";
			value = 1;
			if (t == EQUAL)
			{
				exist_equal += 1;
				add = 2;
				tmp.ini_monomio("=", 0, -1, 0);
				ecuacion.push_back(tmp);
			}
			else if (t == SLASH)
			{
				add = 2;
				tmp.ini_monomio("/", 0, -1, 0);
				ecuacion.push_back(tmp);	
			}
			break;
		case NUMBER:
			value = take_value(i, expresion);
			break;
		case CHAR:
			var = take_var(i, expresion);
			grade = 1;
			break;
		case SPACE:
			i++;
			add++;
			break;
		case POTENCE:
			grade = take_grade(i, expresion);
			if (!grade)
				var = "";
			if (grade > max_grade)
				max_grade = grade;
			break;
		case PRODUCT:
			i++;
			break;
		default:

			return (vector<monomio>){};
		}
		add = (add ? add - 1 : 0);
	}
	if (exist_equal != 1)
		return (vector<monomio>){};
	tmp.ini_monomio(var, value, grade, sign);
	ecuacion.push_back(tmp);
	return ecuacion;
}

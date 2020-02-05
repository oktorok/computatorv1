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
	else
		return ERROR;
}

vector<monomio> parsing3(string expresion)
{
	vector<monomio> ecuacion;
	int i = 0, expresion_l = expresion.length(), t, grade = 0;
	short sign = 1;
	char type_var = 'l';
	string var = "";
        value_u value = (value_u){1};
	short side = 1, add = 0;
	monomio tmp;
	
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
				tmp.ini_monomio(var, value, grade, type_var, sign, side);       
				ecuacion.push_back(tmp);
			}
    			sign = 1;
			if (expresion[i++] == '-')
				sign = -1;
			grade = 0;
			var = "";
			value = (value_u){1};
			if (t == EQUAL)
			{
				side = -1;
				add = 2;
				tmp.ini_monomio("=", (value_u){0}, -1, 'l', 0, 0);
				ecuacion.push_back(tmp);
			}
			else if (t == SLASH)
			{
				add = 2;
				tmp.ini_monomio("/", (value_u){0}, -1, 'l', 0, 0);
				ecuacion.push_back(tmp);	
			}
			break;
		case NUMBER:
			value = take_value(i, expresion, type_var);
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
			break;
		}
		add = (add ? add - 1 : 0);
	}
	tmp.ini_monomio(var, value, grade, type_var, sign, side);
	ecuacion.push_back(tmp);
	return ecuacion;
}

// int main(void)
// {
// 	vector<monomio> a;
// 	a = parsing3("x^2 + 2.2x - 3.003/23 = 0.23");
// 	cout << a.size() << endl;
// 	for(int i=0; i<a.size(); ++i)
// 	{
// 		cout << ((a[i].sign == 1) ? '+' : '-');
// 		cout << ((a[i].value_type == 'l') ? a[i].value.l : a[i].value.d);
// 		cout << a[i].get_variable();
// 		cout << '^' << a[i].get_grade();
// 	}
// }
       

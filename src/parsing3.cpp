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

static value_u take_value(int &i, string expresion, char &type_var)
{
	int j = i;
	value_u val;
	size_t i2;
	bool _float = false;
	
	while (isdigit(expresion[j]) || expresion[j] == '.')
	{
		j++;
		if (expresion[j] == '.')
			_float = true;
				   
	}
	if (_float)
	{
		val.d = stod(expresion.substr(i), &i2);
		type_var = 'd';
	}
	else
	{
		val.l = stol(expresion.substr(i), &i2, 10);
		type_var = 'l';
	}
	//if (expresion[j] == '/')
	i += (int)i2;
	//cout << val.l << endl;
	return val;
}

static string take_var(int &i, string expresion)
{
	string var;
	int j = i-1;

	while (isalpha(expresion[++j]));
	var = expresion.substr(i, j - i);
	//cout << "[" << i << "]" << "[" << j << "]";
	//cout << var << endl;
	i = j;
	return var;
}

static int take_grade(int &i, string expresion)
{
	int grade;
	size_t i2;
	
	i++;
	grade = stoi(expresion.substr(i), &i2, 10);
	i = i + (int)i2;
	//cout << grade << endl;
	return grade;
}

vector<monomio> parsing3(string expresion)
{
	vector<monomio> ecuacion;
	int i = 0, expresion_l = expresion.length(), t, grade = 0;
	short sign = 1;
	char type_var = 'l';
	string var = "";
        value_u value = (value_u){1};
	short side = 1;
	monomio tmp;
	
	while(i < expresion_l)
	{
		t = class_character(expresion[i]);
		switch (t)
	       	{
		case SLASH:
		case EQUAL:
		case OPERATION:
			if (i)
			{
				tmp.ini_monomio(var, value, grade, type_var, sign, side);       
				ecuacion.push_back(tmp);
			}
			sign = 1;
			if (expresion[i++] == '-')
				sign = -1;
			grade = 0;
			var = "";
			if (t == EQUAL)
			{
				side = -1;				
				tmp.ini_monomio("=", (value_u){0}, -1, 'l', 0, 0);
				ecuacion.push_back(tmp);
			}
			else if (t == SLASH)
			{
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
			break;
		case POTENCE:
			grade = take_grade(i, expresion);
			break;
		}
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
       

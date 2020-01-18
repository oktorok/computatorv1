#include "computator.h"
#include <stdio.h>

#define NUMBER 0
#define OPERATION 2
#define CHAR 1
#define EQUAL 3
#define SLASH_DOT 4
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
	else if (a == '/' || a == '.')
		return SLASH_DOT;
	else if (a == '^')
		return POTENCE;
	else if (isspace(a))
		return SPACE;
	else
		return ERROR;
}

static value_u take_value(int &i, string expresion, char &type_var)
{
	int j = i - 1;
	value_u val;
	size_t i2;
	//while (isdigit(expresion[++j]));
	//if (expresion[j] == '.')
	//if (expresion[j] == '/')
	type_var = 'l';
	val.l = stol(expresion.substr(i), &i2, 10);
	i += (int)i2;
	cout << val.l << endl;
	return val;
}

static string take_var(int &i, string expresion)
{
	string var;
	int j = i-1;

	while (isalpha(expresion[++j]));
	var = expresion.substr(i, j - i);
	//cout << "[" << i << "]" << "[" << j << "]";
	cout << var << endl;
	i = j + 1;
	return var;
}

static int take_grade(int &i, string expresion)
{
	int grade;
	size_t i2;

	grade = stoi(expresion.substr(i), &i2, 10);
	i = (int)i2;
	cout << grade << endl;
	return grade;
}

vector<monomio> parsing3(string expresion)
{
	vector<monomio> ecuacion;
	int i = 0, expresion_l = expresion.length(), t, grade;
	stringstream ss;
	char sign, type_var;
	string var;
        value_u value;
	bool side;
	
	
	while(i < expresion_l)
	{
		t = class_character(expresion[i]);
		switch (t)
	       	{
		case OPERATION:
			//if (i)
			//	ecuacion.push_back(monomio().ini_monomio(var, value, grade, type, sign, side));
			sign = expresion[i++];
			if (sign != '-')
				sign = '+';
			break;
		case NUMBER:
			value = take_value(i, expresion, type_var);
			break;
		case CHAR:
			var = take_var(i, expresion);
			break;
		case SPACE:
			i++;
			break;
		case POTENCE:
			grade = take_grade(i, expresion);
			break;
		}
	}
	return ecuacion;
}

int main(void)
{
	vector<monomio> a;
	a = parsing3("34x^2");
	for(int i=0; i<a.size(); ++i)
	{
		cout << a[i].sign;
		cout << a[i].value.l;
		cout << a[i].get_variable();
	}
}
       

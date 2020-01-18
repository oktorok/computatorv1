#include "computator.h"

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
	
	//while (isdigit(expresion[++j]));
	//if (expresion[j] == '.')
	//if (expresion[j] == '/')
	type_var = 'l';
	val.l = stop(expresion, &i);
	cout << val.l << endl;
}

vector<monomio> parsing3(string expresion)
{
	vector<monomio> ecuacion;
	int i = 0, expresion_l = expresion.length(), t;
	stringstream ss;
	char sign, var, type_var;
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
			sign = expresion[i];
			if (sign != '-')
				sign = '+';
			break;
		case NUMBER:
			value = take_value(i, expresion, type_var);
		}
	}
}

int main(void)
{
	parsing3("34x");
}
       

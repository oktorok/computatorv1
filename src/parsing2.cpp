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

static value_u check_double_long(string str, char &type_var, size_t &j)
{
	value_u val;
	if (str[j] == '.')
	{
		val.d = stod(str, &j);
		type_var = 'd';
	}
	else if (!type_var)
	{
		type_var = 'l';
		if (isdigit(str[0]) || isdigit(str[1]))
			val.l = stol(str, &j);
		else
		{
			val.l = 1;
			j += 1;
		}
		cout << str << endl;

	}
	return val;
}

static value_u check_division(value_u a, char &type_a, value_u b, char type_b)
{
	value_u ret;
	if (type_a == type_b)
	{
		if (type_a == 'd')
		{
			if (fmod(a.d, b.d))
			{
				type_a = 'd';
				ret.d = a.d/b.d;
			}
			else
			{
				type_a = 'l';
				ret.l = a.d/b.d;
			}
		}
		else
		{
			if (a.l % b.l)
			{
				type_a = 'd';
				ret.d = a.l/b.l;
			}
			else
			{
				type_a = 'l';
				ret.l = a.l/b.l;
			}
		}
	}
	else if (type_a == 'l')
	{
		if (fmod(a.l, b.d))
	       	{
			type_a = 'd';
			ret.d = a.l/b.d;
		}
		else
		{
			type_a = 'l';
			ret.l = a.l/b.d;
		}
	}
	else if (fmod(a.d, b.l))
	{
		type_a = 'd';
		ret.d = a.d/b.l;
	}
	else
	{
		type_a = 'l';
		ret.l = a.d/b.l;
	}
	return ret;
	
}
			    

static monomio create_monomy(string str)
{
	monomio ret;

	if (str == "=")
	{
		ret.ini_monomio('=', (value_u){0}, -1, '\0', "");
		return ret;
	}
		
	size_t j = 0, i = 0;
	int grade = 0;
	char variable = '\0', type_val, type_val_tmp;
	string value_string;
	value_u val, tmp;
	if (isdigit(str[0]) || str[0] == '-' || str[0] == '+')
		val = check_double_long(str, type_val, j);
	else
	{
		val = (value_u){1};
		type_val = 'l';
	}	
	if (str[j] == '/')
	{
		i = j;
		tmp = check_double_long(str.substr(j + 1), type_val_tmp, j);
		val = check_division(val, type_val, tmp, type_val_tmp);
		j += i + 1;
	}
	value_string = str.substr(0, j);
	if (isalpha(str[j]))
		variable = str[j++];
	if (str[j] == '^')
	{
		grade = stoi(str.substr(j + 1), &j);
		cout << grade << endl;
	}
	else if (variable)
		grade = 1;
	else if (!grade)
		grade = 0;
	ret.ini_monomio(variable, val, grade, type_val, value_string);
	return ret;
}

vector<monomio> parsing2(string expresion)
{
	int t, i = 0, expresion_l = expresion.length();
	stringstream ss;
	vector<monomio> ecuacion;
	
	while(i < expresion_l)
	{
		t = class_character(expresion[i]);
		switch (t)
		{
		case NUMBER:
		case CHAR:
		case SLASH_DOT:
		case POTENCE:
			ss << expresion[i++];
			break;
		case OPERATION:
			if (ss.str().length())
			{
				ecuacion.push_back(create_monomy(ss.str()));
				ss.str("");
			}
			ss << expresion[i++];
			break;
		case EQUAL:
			if (ss.str().length())
			{
				ecuacion.push_back(create_monomy(ss.str()));
				ss.str("");
			}
			ecuacion.push_back(create_monomy("="));
			i++;
			break;
		case ERROR:
			cout << "ERROR WITH CHARACTER: <" << expresion[i] << "> IN POSS " << i << endl;
			exit(-1);
		case SPACE:
		default:
			i++;
			break;
		}
	}
	ecuacion.push_back(create_monomy(ss.str()));
	return ecuacion;
}

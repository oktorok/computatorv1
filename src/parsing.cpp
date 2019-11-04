#include "computator.h"

static int search_value(int &integer, float &fraction, string expresion, int sign, int equal_side)
{
		int j = 0;
		int dot = 0;
		while (isdigit(expresion[j]) || expresion[j] == '.')
		{
				if (expresion[j] == '.')
						dot = 1;
				j++;
		}
		if (dot)
				fraction = stof(expresion) * sign * equal_side;
		else
				integer = stoi(expresion) * sign * equal_side;
		return (j);
}

vector<monomio> parsing(string expresion)
{
	int value = 0, grade = 0, sign = 1, equal_side = 1, tmp_inter = 0;
	float value_frac = 0, tmp_frac = 0;

	char variable = '\0', last_variable = '\0';
	int expresion_len = expresion.length(), i = 0;
	vector<monomio> ecuacion;
	monomio nuevo;

	while (i < expresion_len)
	{
		if (!value && isdigit(expresion[i]))
		{
			i += search_value(value, value_frac, expresion.substr(i), sign, equal_side);
			sign = 1;
			if (expresion[i] == '/')
			{
				i++;
				tmp_inter = 0;
				tmp_frac = 0;
				i += search_value(tmp_inter, tmp_frac, expresion.substr(i), 1, 1);
				if (tmp_inter && value && !(value % tmp_inter))
				{
					value /= tmp_inter;
					value_frac = 0;
				}
				else if (tmp_frac)
				{
					value_frac /= tmp_frac;
					value = 0;
				}
				else
				{
					value_frac = float(value) / float(tmp_inter);
					value = 0;
				}
			}
		}
		else if (isalpha(expresion[i]))
		{
			if (!value && !value_frac)
				value = 1 * sign * equal_side;
			variable = toupper(expresion[i]);
			if (variable != last_variable && last_variable)
			{
				cout << "Different variables, if you want to solve over one of them use the flag -v <variable>" << endl;
				exit(-1);
			}
			last_variable = variable;
			while (expresion[i] && (isalpha(expresion[i]) || expresion[i] == '^'))
				i++;
			if (!expresion[i] || isspace(expresion[i]) || expresion[i] == '+' || expresion[i] == '-' || expresion[i] == '=')
				grade = 1;
			else
			{
				grade = stoi(expresion.substr(i));
				while (isdigit(expresion[i]))
					i++;
			}
		}
		else if (expresion[i] == '-' || expresion[i] == '+' || expresion[i] == '=')
		{
			if (expresion[i] == '-')
				sign *= -1;
			else if (expresion[i] == '=')
				equal_side = -1;
			nuevo.ini_monomio(variable, value, grade, value_frac);
			ecuacion.push_back(nuevo);
			value = 0;
			variable = '\0';
			grade = 0;
			value_frac = 0;
			i++;
		}
		else
			i++;
	}
	if (equal_side != -1)
	{
		cout << "ERROR not ecuality in the ecuation" << endl;
		exit(-1);
	}
	nuevo.ini_monomio(variable, value, grade, value_frac);
	ecuacion.push_back(nuevo);
	return (ecuacion);
}

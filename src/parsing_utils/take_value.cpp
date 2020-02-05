#include "computator.h"

value_u take_value(int &i, string expresion, char &type_var)
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

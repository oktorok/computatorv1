#include "computator.h"

value_u check_division(value_u a, char type_a, value_u b, char &type_b)
{
	value_u ret;
 	if (type_a == type_b)
	{
		if (type_a == 'd')
		{
			if (fmod(a.d, b.d) && (type_b = 'd'))
				ret.d = a.d/b.d;
			else
			{
				type_b = 'l';
				ret.l = (long)a.d/b.d;
			}
		}
		else
		{
			if (a.l % b.l && (type_b = 'd'))
				ret.d = (double)a.l/b.l;
			else
			{
				type_b = 'l';
				ret.l = a.l/b.l;
			}
		}
	}
	else if (type_a == 'l')
	{
		if (fmod(a.l, b.d) && (type_b = 'd'))
			ret.d = a.l/b.d;
		else
		{
			type_b = 'l';
			ret.l = a.l/b.d;
		}
	}
	else if (fmod(a.d, b.l) && (type_b = 'd'))
		ret.d = a.d/b.l;
	else
	{
		type_b = 'l';
		ret.l = a.d/b.l;
	}
	return ret;
	
}

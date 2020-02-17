#include "computator.h"

value_u check_type(value_u value, char &value_type)
{
	double trash;

	if (value_type == 'd')
	{
		if (!modf(value.d, &trash))
		{
			value.l = (long)value.d;
			value_type = 'l';
		}
	}
	return value;
}

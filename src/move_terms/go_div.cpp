#include "computator.h"

vector<monomio> go_div(vector<monomio> ecuacion)
{
	monomio tmp;

	if (ecuacion[0].value_type == 'l' && ecuacion[0].value.l == 1)
		return ecuacion;
	tmp.ini_monomio("/", (value_u){0}, -1, 'l', 0, 0);
	ecuacion.push_back(tmp);
	ecuacion.push_back(ecuacion[ecuacion.size() - 2]);
	ecuacion.back().value = ecuacion[0].value;
	ecuacion.back().value_type = ecuacion[0].value_type;
	ecuacion.back().sign = ecuacion[0].sign;
	ecuacion[0].value.l = 1;
	ecuacion[0].value_type = 'l';
	ecuacion[0].sign = 1;
	return ecuacion;
}

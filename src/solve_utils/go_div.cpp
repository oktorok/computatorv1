#include "computator.h"

vector<monomio> go_div(vector<monomio> ecuacion)
{
	monomio tmp;

	if (ecuacion[0].value == 1)
		return ecuacion;
	tmp.ini_monomio("/", 0, -1, 0, 0);
	ecuacion.push_back(tmp);
	ecuacion.push_back(ecuacion[ecuacion.size() - 2]);
	ecuacion.back().value = ecuacion[0].value;
	ecuacion.back().sign = ecuacion[0].sign;
	ecuacion[0].value = 1;
	ecuacion[0].sign = 1;
	return ecuacion;
}

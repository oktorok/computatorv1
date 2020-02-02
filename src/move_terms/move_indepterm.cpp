#include "computator.h"

vector<monomio> move_indepterm(vector<monomio> ecuacion)
{
	vector<monomio>::iterator it1;

	if (ecuacion[ecuacion.size() - 3].get_grade() != 0)
		return ecuacion;
	it1 = ecuacion.begin() + ecuacion.size() - 3;
	ecuacion.back() = ecuacion[ecuacion.size() - 3];
	ecuacion.back().side = -1;
	ecuacion.back().sign *= -1;
	ecuacion.erase(it1);
	return (ecuacion);
}

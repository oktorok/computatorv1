#include "computator.h"

vector<monomio> move_indepterm(vector<monomio> ecuacion)
{
	vector<monomio>::iterator it1;
	monomio zero;

	zero.ini_monomio("", 0, 0, 0);
	it1 = ecuacion.end() - 2;
	ecuacion.back().sign *= -1;
	ecuacion.insert(it1, ecuacion.back());
	ecuacion.erase(ecuacion.end() - 1);
	ecuacion.push_back(zero);
	return (ecuacion);
}

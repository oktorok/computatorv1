#include "computator.h"

output_t normal_solve(vector<monomio> ecuacion, output_t solution)
{
	value_u sumand, radicand, den;
	short t = 0;
	
	ecuacion = move_indepterm(ecuacion);
	solution.steps.push_back(printer(ecuacion, NULL));
	if (ecuacion[0].value_type == 'l')
		t |= 1 << 2;
	if (ecuacion[1].value_type == 'l')
		t |= 1 << 1;
	if (ecuacion[2].value_type == 'l')
		t |= 1;

	switch (t)
	{
	case 0:
		sumand.d = -1 * ecuacion[1].value.d * ecuacion[1].sign;
		den.d = 2 * ecuacion[0].value.d;
		radicand.d = ecuacion[1].value.d * ecuacion[1].value.d - 4 * ecuacion[0].value.d * ecuacion[2].value.d;
		break;

	case 4:
		sumand.d = -1 * ecuacion[1].value.d * ecuacion[1].sign;
		den.l = 2 * ecuacion[0].value.l;
		radicand.d = ecuacion[1].value.d * ecuacion[1].value.d - 4 * ecuacion[0].value.l * ecuacion[2].value.d;
		break;

	case 2:
		sumand.l = -1 * ecuacion[1].value.l * ecuacion[1].sign;
		den.d = 2 * ecuacion[0].value.d;
		radicand.d = ecuacion[1].value.l * ecuacion[1].value.l - 4 * ecuacion[0].value.d * ecuacion[2].value.d;
		break;
		
	case 1:
		sumand.d = -1 * ecuacion[1].value.d * ecuacion[1].sign;
		den.d = 2 * ecuacion[0].value.d;
		radicand.d = ecuacion[1].value.d * ecuacion[1].value.d - 4 * ecuacion[0].value.d * ecuacion[2].value.l;
		break;
		
	case 3:
		sumand.l = -1 * ecuacion[1].value.l * ecuacion[1].sign;
		den.d = 2 * ecuacion[0].value.d;
		radicand.d = ecuacion[1].value.l * ecuacion[1].value.l - 4 * ecuacion[0].value.d * ecuacion[2].value.l;
		break;
	case 5:
		sumand.d = -1 * ecuacion[1].value.d * ecuacion[1].sign;
		den.l = 2 * ecuacion[0].value.l;
		radicand.d = ecuacion[1].value.d * ecuacion[1].value.d - 4 * ecuacion[0].value.l * ecuacion[2].value.l;
		break;
	case 6:
		sumand.l = -1 * ecuacion[1].value.l * ecuacion[1].sign;
		den.l = 2 * ecuacion[0].value.l;
		radicand.d = ecuacion[1].value.l * ecuacion[1].value.l - 4 * ecuacion[0].value.l * ecuacion[2].value.d;
		break

	case 7:
		sumand.l = -1 * ecuacion[1].value.l * ecuacion[1].sign;
		den.l = 2 * ecuacion[0].value.l;		
		radicand.l = ecuacion[1].value.l * ecuaion[1].value.l - 4 * ecuacion[0].value.l * ecuacion[2].value.l;
		break;

	}
	cout << t << endl;
	return solution;
	if (ecuacion[1].value_type == 'l')
		sumand.l = -1 * ecuacion[1].value.l * ecuacion[1].sign;
	else
		sumand.d = -1 * ecuacion[1].value.d * ecuacion[1].sign;

	if (ecuacion[0].value_type == 'l')
		den.l = 2 * ecuacion[0].value.l;
	else
		den.d = 2 * ecuacion[0].value.d;

	
	return solution;

	
}

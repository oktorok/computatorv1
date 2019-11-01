#include "computator.h"

void printer (vector<monomio> ecuacion, string *result)
{
	int mon_cuant = ecuacion.size();
	int grade;
	for (int i = 0; i < mon_cuant; i++)
	{
		grade = ecuacion[i].get_grade();
		if ((ecuacion[i].value > 0 || ecuacion[i].frac_value > 0) && i != 0)
			printf("+");
		if (ecuacion[i].get_variable() != "")
		{
			if (ecuacion[i].frac_value)
					printf("%g%s", ecuacion[i].frac_value, ecuacion[i].get_variable().c_str());
			else if (ecuacion[i].value == -1)
				printf("-%s",ecuacion[i].get_variable().c_str());
			else if (ecuacion[i].value != 1)
				printf("%i%s", ecuacion[i].value,ecuacion[i].get_variable().c_str());
			else
				printf("%s", ecuacion[i].get_variable().c_str());
			if (grade > 1 && grade < 4)
				wprintf(L"%lc", 0x00B2 + grade - 2);
			else if (grade >= 4)
				wprintf(L"%lc", 0x2074 + grade - 4);
		}
		else if (ecuacion[i].value != 0)
			printf("%i", ecuacion[i].value);
	}
	printf("=0\n");
	if (!result)
		return;
	if (ecuacion[0].get_grade() == 2)
		printf("Result 1 %s = %s\nResult 2 %s = %s\n", ecuacion[0].get_variable().c_str(), result[0].c_str(), ecuacion[0].get_variable().c_str(), result[1].c_str());
	else
		printf("Result %s = %s\n", ecuacion[0].get_variable().c_str(), result[0].c_str());
}

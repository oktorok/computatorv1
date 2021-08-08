#include "computator.h"

int take_grade(int &i, string expresion)
{
	int grade;
	size_t i2;
	string subst;
	
	i++;
	subst = expresion.substr(i);
	for (unsigned long j = 0; j < subst.length(); j++)
	{
		if (subst[j] != ' ')
		{
			if (!isdigit(subst[j]))
				return (-1);
			else
				break;
		}
	}
	grade = stoi(subst, &i2, 10);
	i = i + (int)i2;
	
	return grade;
}

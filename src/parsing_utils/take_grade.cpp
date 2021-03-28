#include "computator.h"

int take_grade(int &i, string expresion)
{
	int grade;
	size_t i2;
	string subst;
	
	i++;
	subst = expresion.substr(i);
	grade = stoi(subst, &i2, 10);
	i = i + (int)i2;
	//cout << grade << endl;
	return grade;
}

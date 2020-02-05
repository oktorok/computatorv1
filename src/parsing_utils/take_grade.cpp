#include "computator.h"

int take_grade(int &i, string expresion)
{
	int grade;
	size_t i2;
	
	i++;
	grade = stoi(expresion.substr(i), &i2, 10);
	i = i + (int)i2;
	//cout << grade << endl;
	return grade;
}

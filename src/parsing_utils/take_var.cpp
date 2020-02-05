#include "computator.h"

string take_var(int &i, string expresion)
{
	string var;
	int j = i-1;

	while (isalpha(expresion[++j]));
	var = expresion.substr(i, j - i);
	//cout << "[" << i << "]" << "[" << j << "]";
	//cout << var << endl;
	i = j;
	return var;
}

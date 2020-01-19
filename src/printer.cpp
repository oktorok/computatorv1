#include "computator.h"

string printer (vector<monomio> ecuacion, string *result)
{
	int mon_cuant = ecuacion.size();
	int grade;
	stringstream ss;
	string tmp;
	bool sign = false;
	for (int i = 0; i < mon_cuant; i++)
	{
		tmp = ecuacion[i].get_variable();
		if (tmp == "=" || tmp == "/")
		{
			ss << tmp;
			sign = false;
			continue;
		}
		if (sign || ecuacion[i].sign < 0)
		{
			if (ecuacion[i].sign < 0)
				ss << '-';
			else
				ss << '+';
		}
		sign = true;
		if (ecuacion[i].value_type == 'l')
		{
			if (ecuacion[i].value.l != 1)
				ss << ecuacion[i].value.l;
		}
		else if ((long)ecuacion[i].value.d != 1)
		{
			ss << ecuacion[i].value.d;
		}
		ss << tmp;
		grade = ecuacion[i].get_grade();
		if (grade > 1 && grade < 4)
		{
			tmp = SUPERINDEX_2;
			tmp[1] += grade - 2;
			ss << tmp;
		}
		else if (grade >= 4)
		{
			tmp = SUPERINDEX_4;
			tmp[2] += grade - 4;
			ss << tmp;
		}
		
	}
		/*
		grade = ecuacion[i].get_grade();
		if ((ecuacion[i].value.l > 0  && i != 0)
			ss << "+";
			//printf("+");
		if (ecuacion[i].get_variable() != "")
		{
			if (ecuacion[i].frac_value)
				//printf("%g%s", ecuacion[i].frac_value, ecuacion[i].get_variable().c_str());
				ss << ecuacion[i].frac_value << ecuacion[i].get_variable().c_str();
			else if (ecuacion[i].value == -1)
				//printf("-%s",ecuacion[i].get_variable().c_str());
				ss << "-" << ecuacion[i].get_variable().c_str();
			else if (ecuacion[i].value != 1)
				//printf("%i%s", ecuacion[i].value,ecuacion[i].get_variable().c_str());
				ss << ecuacion[i].value << ecuacion[i].get_variable().c_str();
			else
				//printf("%s", ecuacion[i].get_variable().c_str());
				ss << ecuacion[i].get_variable().c_str();
			if (grade > 1 && grade < 4)
			{
				//wprintf(L"%lc", 0x00B2 + grade - 2);
				//ss << wchar_t(0x00B2 + grade - 2);
				tmp = SUPERINDEX_2;
				tmp[1] += grade - 2;
				ss << tmp;
			}
			else if (grade >= 4)
			{
				//wprintf(L"%lc", 0x2074 + grade - 4);
				//ss << wchar_t(0x2074 + grade - 4);
				tmp = SUPERINDEX_4;
				tmp[2] += grade - 4;
				ss << tmp;
			}
		}
		else if (ecuacion[i].value != 0)
			//printf("%i", ecuacion[i].value);
			ss << ecuacion[i].value;
	}
	ss << "=0" << endl;
	//printf("=0\n");*/
	return ss.str();
}

void printer2(string variable, string result, string type_answer)
{
	int frac_pos, res_length, denominator_length, radicand = 0, written_characters;
	stringstream ss;
	res_length = result.length();
	frac_pos = result.find("/");
	if (!variable.empty())
	{
		ss << type_answer << variable << " = ";
		type_answer = ss.str();
		ss.str("");
	}
	if (frac_pos > 0)
	{
		ss << endl << string(type_answer.length(), ' ');
		denominator_length = res_length - frac_pos - 1;
		for (int i = 0; i < frac_pos; i++)
		{
			if (result[i] == '|')
			{
				ss << "√";
				radicand = i + 1;
			}
			else
				ss << result[i];
		}
		ss << endl;
		written_characters = (radicand - 1) + (frac_pos + 1 - radicand) ;
		ss << type_answer;
		for (int i = 0; i < written_characters; i++)
			ss << "―";
		ss << endl << string(type_answer.length(), ' ');
		ss << string(written_characters / 2 - denominator_length / 2, ' ') << result.substr(frac_pos + 1, res_length) << endl;
		cout << ss.str();
	}
	else
		printf("Solucion %s = %s\n", variable.c_str(), result.c_str());
	
}

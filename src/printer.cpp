#include "computator.h"

static fraction_str_t print_fraction(vector<monomio> ecuacion, int slash, bool sign, fraction_str_t &last, bool reset_cuant)
{
	fraction_str_t fraction;
	stringstream tmpss;
	int num_length, den_length, longer;
	static int cuant_write = 0;

	if (reset_cuant)
		cuant_write = 0;
	fraction.up << last.up.str();
	fraction.middle << last.middle.str();
	fraction.down << last.down.str();
	if (sign && ecuacion[slash - 1].sign < 0)
		fraction.middle << '-';
	else if (sign)
		fraction.middle << '+';
	num_length = fraction.middle.str().size() - fraction.up.str().size() - cuant_write * 2;
	den_length = fraction.middle.str().size() - fraction.down.str().size() - cuant_write * 2;
	cout << num_length << " ---- " << den_length << endl;
	if ((ecuacion.size() > 5 && ecuacion[5].get_variable().find("±") != (size_t)-1 )|| ecuacion[0].get_grade() == 2)
	{
		num_length -= 1;
		den_length -= 1;
	}
	if (ecuacion.size() == 5 && (ecuacion[0].get_variable().find("₁") != (size_t) - 1 || ecuacion[0].get_variable().find("₂") != (size_t) - 1))
	{
		num_length -= 1;
		den_length -= 1;
	}
	for (int j = 0; j < num_length - 1; j++)
		fraction.up << " ";
	for (int j = 0; j < den_length - 1; j++)
		fraction.down << " ";
	tmpss << ecuacion[slash - 1].value * ecuacion[slash - 1].sign;
	num_length = tmpss.str().size();
	tmpss.str("");
	tmpss << ecuacion[slash + 1].value * ecuacion[slash + 1].sign;
	den_length = tmpss.str().size();
	tmpss.str("");
	longer = (num_length > den_length ? num_length : den_length);
	for (int j = 0; j < longer; j++)
	{
		fraction.middle << "―";
		cuant_write++;
		if (j < (longer - num_length) / 2)
			fraction.up << " ";
		if (j < (longer - den_length) / 2)
			fraction.down << " ";
	}
	fraction.up << ecuacion[slash - 1].value * ecuacion[slash - 1].sign ;
	fraction.down << ecuacion[slash + 1].value * ecuacion[slash + 1].sign;
	fraction.middle << ecuacion[slash + 1].get_variable();
	return fraction;
}

string printer (vector<monomio> ecuacion)
{
	int grade, iplus = 0;
	size_t i = 0, mon_cuant = ecuacion.size();
	stringstream ss;
	string tmp;
	bool sign = false, reset = true;
	fraction_str_t fraction, tmpfra;

	while (i < mon_cuant)
	{
		iplus = 1;
		tmp = ecuacion[i].get_variable();
		if (tmp == "=" || tmp == "±")
		{
			ss << tmp;
			sign = false;
			i += iplus;
			continue;
		}
		if (i + 1 < mon_cuant && ecuacion[i + 1].get_variable() == "/")
		{
			tmpfra.middle.str("");
			tmpfra.middle << ss.str();
			tmpfra = print_fraction(ecuacion, i + 1, sign, tmpfra, reset);
			fraction.up.str("");
			fraction.up << tmpfra.up.str();
			ss.str("");
			ss << tmpfra.middle.str();
			fraction.down.str("");
			fraction.down << tmpfra.down.str();
			reset = false;
			sign = true;
			iplus = 3;
		}
		else
		{
			if (sign || ecuacion[i].sign < 0)
			{
				if (ecuacion[i].sign < 0)
					ss << '-';
				else
					ss << '+';
			}
			sign = true;
			if (ecuacion[i].value != 1 || tmp == "")
				ss << ecuacion[i].value;
			ss << ecuacion[i + iplus - 1].get_variable();
		}

		grade = ecuacion[i + iplus - 1].get_grade();
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
		i += iplus;
	}
	if (fraction.up.str()[0])
	{
		fraction.up << endl;
	        ss << endl;
		fraction.up << ss.str() << fraction.down.str();
		return fraction.up.str();
	}
	return ss.str();
}

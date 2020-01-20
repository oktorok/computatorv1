#ifndef COMPUTATOR_H
#define COMPUTATOR_H

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vector>
#include <cmath>
//#include <bits/stdc++.h>

#define SQR_ERR 0.001
#define SUPERINDEX_2 "\u00B2"
#define SUPERINDEX_4 "\u2074"

using namespace std;

union value_u
{
	long l;
	double d;
};

typedef struct solution_s {
	bool imaginary;
	char value_type;
	value_u real;
	string imaginary_sol;
	vector<string> steps;
} solution_t;

class monomio {
private:
	string variable;
	int grade;
	
public:
	string value_string;
	char value_type;
	value_u value;
	short sign;
	short side;
	
	monomio()
	{
		variable = "";
		grade = 0;
		sign = 1;
		side = 1;
		value_type = 0;
		value = (value_u){0};
	}
	
	void ini_monomio(string var, union value_u val, int gra, int val_typ, short val_sign, short val_side)
	{
		this->value_type = val_typ;
		this->sign = val_sign;
		this->side = val_side;
		this->value = val;
		this->variable = var;
		this->grade = gra;
	}
		
	string get_variable()
	{
		return (variable);
	}

	int get_grade()
	{
		return (grade);
	}

	bool is_compt(monomio compatible)
	{
		if (this->get_variable() == compatible.get_variable() && this->get_grade() == compatible.get_grade())
			return (true);
		return (false);
	}
	
	void sum_monomios(monomio sumando, short side)
	{
		char t1 = this->value_type, t2 = sumando.value_type;
		stringstream ss;
		for (int i=0; i < this->value_string.size();i++)
		{
			if (isdigit(this->value_string[i]) && !ss.rdbuf()->in_avail())
			{
				ss << this->value_string.substr(0, i);
				if (t1 == t2 && t1 == 'l')
				{
					this->value.l += sumando.value.l * side;
					ss << this->value.l;
				}
				else
				{
					this->value.d += sumando.value.d * side;
					ss << this->value.d;
				}
				this->value_string = ss.str();
				return;
			}
		}
		return ;
	}
};

vector<monomio> parsing(string);
vector<monomio> parsing2(string);
vector<monomio> parsing3(string);
solution_t computatorv1(string);
value_u solve(vector<monomio> , vector<string> &, char &);
string printer(vector<monomio>, string *);
void printer2(string, string, string );
float mySqrt(float);
float myPow(float, int);
#endif

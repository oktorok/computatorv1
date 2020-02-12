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
#include <algorithm>



#define SQR_ERR 0.001
#define SUPERINDEX_2 "\u00B2"
#define SUPERINDEX_4 "\u2074"

using namespace std;
#include "templates.h"
union value_u
{
	long l;
	double d;
};

typedef struct complex_solution_s {
	char real_type;
	char imaginary_type;
	value_u real;
	value_u imaginary;
} complex_solution_t;

union type_sol_u
{
	value_u real;
	complex_solution_t imaginary;
};

typedef struct solution_s {
	bool imaginary;
	char value_type;
	type_sol_u sol;
} solution_t;

typedef struct output_s {
	vector<solution_t> solutions;
	vector<string> steps;
} output_t;

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

	monomio(const monomio &src)
	{
		this->value_type = src.value_type;
		this->sign = src.sign;
		this->side = src.side;
		this->value = src.value;
		this->variable = src.variable;
		this->grade = src.grade;
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

	void set_variable(string var)
	{
		this->variable = var;
	}
	
	int get_grade()
	{
		return (grade);
	}

	void set_grade(int grad)
	{
		this->grade = grad;
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

//vector<monomio> parsing(string);
//vector<monomio> parsing2(string);
vector<monomio> move_indepterm(vector<monomio>);
vector<monomio> go_div(vector<monomio>);
vector<monomio> parsing3(string, int &);
int take_grade(int &, string);
string take_var(int &, string);
value_u take_value(int &, string, char &);
output_t computatorv1(vector<monomio>, int );
output_t solve(vector<monomio> , output_t);
output_t no_indepterm(vector<monomio>, output_t);
vector<monomio> solve_fractions(vector<monomio>);
output_t solv_first_grade(vector<monomio>, output_t);
output_t simple_solve(vector<monomio>, output_t);
output_t normal_solve(vector<monomio>, output_t);
complex_solution_t create_complex(vector<monomio>);
value_u check_division(value_u, char, value_u, char &);
string printer(vector<monomio>, string *);
value_u mySqrt(value_u, char &);
float myPow(float, int);
#endif

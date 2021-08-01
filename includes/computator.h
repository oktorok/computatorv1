#ifndef COMPUTATOR_H
#define COMPUTATOR_H

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vector>
// #include <cmath>
//#include <bits/stdc++.h>
#include <algorithm>



#define SQR_ERR 0.001
#define SUPERINDEX_2 "\u00B2"
#define SUPERINDEX_4 "\u2074"
#define STEPS 1 << ('s' - 'a')
#define HELP 1 << ('h' - 'a')

using namespace std;
#include "templates.h"

typedef struct fraction_str_s {
	stringstream up;
	stringstream middle;
	stringstream down;
} fraction_str_t;

typedef struct complex_solution_s {
	double real;
	double imaginary;
} complex_solution_t;

union type_sol_u
{
	double real;
	complex_solution_t imaginary;
};

typedef struct solution_s {
	bool imaginary;
	type_sol_u sol;
} solution_t;

typedef struct output_s {
	vector<solution_t> solutions;
	vector<string> steps;
	vector<string> guide;
} output_t;

class monomio {
private:
	string variable;
	int grade;
	
public:
	double value;
	short sign;
	
	monomio()
	{
		variable = "";
		grade = 0;
		sign = 1;
		value = 0;
	}

	monomio copy_monomio()
	{
		monomio t;

		t.ini_monomio(this->variable, this->value, this->grade, this->sign);
		return t;
	}
	
	void ini_monomio(string var, double val, int gra, short val_sign)
	{
		this->sign = val_sign;
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
};

//vector<monomio> parsing(string);
//vector<monomio> parsing2(string);
vector<monomio> move_indepterm(vector<monomio>);
vector<monomio> go_div(vector<monomio>);
vector<monomio> parsing3(string, int &);
monomio calc_den(monomio);
monomio calc_sumand(monomio);
monomio calc_radicand(monomio, monomio, monomio);
monomio calc_num(monomio, monomio, bool);
int take_grade(int &, string);
string take_var(int &, string);
double take_value(int &, string);
output_t computatorv1(vector<monomio> &, int &, int);
output_t solve(vector<monomio> , output_t, int);
output_t no_indepterm(vector<monomio>, output_t, int);
vector<monomio> solve_fractions(vector<monomio>);
output_t solv_first_grade(vector<monomio>, output_t, int);
output_t simple_solve(vector<monomio>, output_t, int);
output_t normal_solve(vector<monomio>, output_t, int);
complex_solution_t create_complex(vector<monomio>);
string printer(vector<monomio>);
double mySqrt(double);
#endif

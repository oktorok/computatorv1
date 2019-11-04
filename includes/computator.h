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

typedef struct solution_s {
	bool imaginary;
	float real_sol;
	string imaginary_sol;
	vector<string> steps;
} solution_t;

union value_u
{
	long l;
	double d;
};

class monomio {
private:
	string variable;
	int grade;
	
public:
	string value_string;
	char value_type;
	value_u value;
	
	monomio()
	{
		variable = "";
		grade = 0;
		value_string = "";
		value_type = 0;
		value = (value_u){0};
	}
	
	void ini_monomio(char var, union value_u val, int gra, int val_typ, string val_str)
	{
		this->value_type = val_typ;
		this->value_string = val_str;
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
	
	void sum_monomios(monomio sumando)
	{
		char t1 = this->value_type, t2 = sumando.value_type;
		if (t1 == t2 && t1 == 'i')
			this->value.l += sumando.value.l;
		else
			this->value.d += sumando.value.d;
		return ;
	}
};

vector<monomio> parsing(string);
vector<monomio> parsing2(string);
solution_t computatorv1(string);
string *solve(vector<monomio> *, vector<string> *);
string printer(vector<monomio>, string *);
void printer2(string, string, string );
float mySqrt(float);
float myPow(float, int);
#endif

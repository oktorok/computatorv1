#ifndef COMPUTATOR_H
#define COMPUTATOR_H

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vector>
//#include <bits/stdc++.h>

#define SQR_ERR 0.001

using namespace std;

class monomio {
private:
		string variable;
		int grade;
	
public:
		int value;
		float frac_value;
		
		monomio()
				{
						variable = "";
						grade = 0;
						value = 0;
						frac_value = 0;
				}
	
		void ini_monomio(char var, int val, int gra, float frac_val)
				{
						if (frac_val)
						{
								this->frac_value = frac_val;
								this->value = 0;
						}
						else
						{
								this->value = val;
								this->frac_value = 0;
						}
						if (!(this->grade = gra))
								this->variable = "\0";
						else
								this->variable = var;
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
						this->value += sumando.value;
						return ;
				}
};

vector<monomio> parsing(char *expresion);
string *solve(vector<monomio> *);
void printer(vector<monomio>, string *);
float mySqrt(float num);
float myPow(float base, int exponent);
#endif

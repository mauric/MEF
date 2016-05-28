#ifndef POINTS_H
#define POINTS_H

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>


using namespace std;

typedef struct
{	
	double num;
	double x;
	double y;
} P;

typedef struct
{
	double num;
	string n;
	double pt1;
	double pt2;
	double Xc;
	double Yc;
	double l;
	P * pdep;
	P * pfin;
} S;


struct L
{
	string lg;
};

#endif

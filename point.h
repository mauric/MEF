/*
 ============================================================================
 Name        : MEF.c
 Author      : Tous
 Date		 : 29 mai
 Version     :
 Copyright   : Your copyright notice
 Description : Implementation d'algorithme de mallage
 Source 	 : https://github.com/mauric/MEF -
 ============================================================================
 */


#ifndef POINTS_H
#define POINTS_H

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>

using namespace std;

typedef struct {
	double id; //identificateur du point
	double x; //coord en x
	double y; //coord en y
} P;

typedef struct {
	double id; //identificateur du segment
	string n;  //je ne sais pas
	double pt1; // point de depart (ubication dans le tableu) TODO changer cette implementation pour pointer a struct de type P
	double pt2; // point final
	double Xc; // coord. X du centre (cas de un arc)
	double Yc; // coord. Y du centre (cas de un arc)
	double l; // longueur du segment
	P * pdep; // pointeur au struct P de depart
	P * pfin; // poointeur au struct P final
} S;

struct L {
	string lg;
};

#endif


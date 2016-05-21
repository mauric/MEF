#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>    // sort
#include <vector>
#include "point.h"
#include <cmath>

using namespace std;

#define ERROR_DOUBLE -999999
#define ERROR_ARC 696969

bool croissant (int i, int j) { return (i < j); }

bool decroissant (int i, int j) { return (i > j); }

vector<string> split(const string &s, char delim) { // s -> %d %d %d %d
  vector<string> elems;
  stringstream ss(s);
  string item;

  while (getline(ss, item, delim)) {
    elems.push_back(item);
  }

  // tour 0 : 1 2 3 5 -- item = vide -- elems -- vide
  // tour 1 : 2 3 5 -- item = 1 -- elems -- 1
  // tour 2 : 3 5 -- item = 2 -- elems -- 1 2
  // tour 3 : 5 -- item = 3 -- elems -- 1 2 3
  // tour 4 : vide -- item = 5 -- elems -- 1 2 3 5

  return elems;
}

vector<string> split2(const string &s, string delimiter) {
  vector<string> elems;

  string sTmp(s);  //" 1  0.1  0.25";

  size_t zero = 0;
  size_t pos = 0;
  string token;

  do{
    pos = sTmp.find(delimiter);
    if (pos > zero) {
      token = sTmp.substr(0, pos);
      elems.push_back(token);
    }
    if (pos >= zero)  sTmp.erase(0, pos + delimiter.length());

  } while (pos != string::npos);

  elems.push_back(sTmp);

  return elems;
}

double string_to_double( const string& s )
{
  stringstream i(s);
  double x;
  if (!(i >> x))
    return ERROR_DOUBLE;
  return x;
}

P transformerPoint(string ligne) {
  P p;
  vector<string> tabString = split2(ligne, " ");

  p.num = string_to_double(tabString[0]);
  p.x = string_to_double(tabString[1]);
  p.y = string_to_double(tabString[2]);

  return p;
}


S transformerSegment(string line){
  S s;
vector<string> tabString = split2(line, " ");
    s.n = tabString[0];
    s.pt1 = string_to_double(tabString[1]);
    s.pt2 = string_to_double(tabString[2]);
    s.Xc = ERROR_ARC;
    s.Yc = ERROR_ARC;
  if(s.n=="arc")
  { s.Xc = string_to_double(tabString[3]);
    s.Yc = string_to_double(tabString[4]);}
  return s;
  
}


int lireFichier(string path, vector<string> &v) {
  int nbline = 0;
  string l;
  l = "";
  ifstream fil(path.c_str());

  if (fil.is_open())
  {
    while ( getline (fil, l) )
    {
      v.push_back(l);
      nbline = nbline + 1;
    }
    fil.close();
  }
  return nbline;
}


int chercherString(int debutRecherche, vector<string> &v, string recherche) {
  for (unsigned int i = debutRecherche; i < v.size(); i++ ) {
    if (v[i].find(recherche) != string::npos) {
      return i;
    }
  }
  return -1;
}

int chercherString(vector<string> &v, string recherche) {
  return chercherString(0, v, recherche);
}



int main()
{
///////////////////////////////////////////////////////////
  vector<string> lignesLues;
  string nomFichier("projet mef.geo");
  int nbline;

  nbline = lireFichier(nomFichier, lignesLues);

  cout << "nombre de lignes : " <<  nbline << endl;
//////////////////////////////////////////////////////////

  /*for (unsigned int i = 0; i < lignesLues.size(); i++ ) {
    cout << lignesLues[i] << endl;
  }*/


  unsigned int pdeb  = chercherString(lignesLues, "$points");
  unsigned int pfin  = chercherString(pdeb, lignesLues, "=======");

  cout << "pdeb : " <<  pdeb << endl;
  cout << "pfin : " <<  pfin << endl;

  pdeb += 2;
  pfin -= 2;

  // Traitement des lignes
  vector<P> points;
  P pTmp;

  for (unsigned int i = pdeb; i <= pfin; i++ ) {
    pTmp = transformerPoint(lignesLues[i]);
    points.push_back(pTmp);
  }
  
  unsigned int sdeb  = chercherString(lignesLues, "$courbes");
  unsigned int sfin  = chercherString(sdeb, lignesLues, "=======");

  cout << "sdeb : " <<  sdeb << endl;
  cout << "sfin : " <<  sfin << endl;

  sdeb += 2;
  sfin -= 2;




  // Traitement des lignes
  vector<S> segments;
  S sTmp;

  for (unsigned int i = sdeb; i <= sfin; i++ ) {
     sTmp = transformerSegment(lignesLues[i]);
     sTmp.num=i-sdeb+1;
     segments.push_back(sTmp);
  }


  // Affichages des points
  for (unsigned int i = 0; i < points.size(); i++ ) {
    cout << "Point: " << points[i].num << " X: " << points[i].x << " Y: " << points[i].y << endl;
  }
  // Affichages des segments
  for (unsigned int i = 0; i < segments.size(); i++ ){
    if (segments[i].n=="arc")
    {
cout << segments[i].n  << ": " << segments[i].num << " Pt1:  " << segments[i].pt1 << " Pt2: " << segments[i].pt2 <<" Xc:  " << segments[i].Xc << " Yc: " << segments[i].Yc << endl;
    }
    else{
cout << segments[i].n  << ": " << segments[i].num << " Pt1:  " << segments[i].pt1 << " Pt2: " << segments[i].pt2 << endl;
         }
  }

  return 0;
}
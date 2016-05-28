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
//#define PI 3.14159265

bool croissant(int i, int j) {
	return (i < j);
}

bool decroissant(int i, int j) {
	return (i > j);
}

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

double findAngle(P & p1, P & p2) { // du premier point vers le deuxième (le ref se pose sur le premier point)
	double Dx = p2.x - p1.x;
	double Dy = p2.y - p1.y;
	double alpha = atan2(Dy, Dx);
	const double DEG = M_PI / 180;
	alpha /= DEG;
	if (alpha == 180) {
		alpha = -alpha;
	}
	return alpha;
}

void AfficherSegment(vector<S> &segment) {
	for (unsigned int i = 0; i < segment.size(); i++) {
		if (segment[i].n == "arc") {
			cout << segment[i].n << ": " << segment[i].id << " Pt1:  "
					<< segment[i].pt1 << " Pt2: " << segment[i].pt2 << " Xc:  "
					<< segment[i].Xc << " Yc: " << segment[i].Yc << " longeur: "
					<< segment[i].l << endl;
		} else {
			cout << segment[i].n << ": " << segment[i].id << " Pt1:  "
					<< segment[i].pt1 << " Pt2: " << segment[i].pt2
					<< " longeur: " << segment[i].l << endl;
		}
	}
	cout << endl;
}

double longArc(S &s, vector<P> &p) {
	double k;
	double alpha;
	double beta;
	double anglesomme;
	P pt_tmp1;
	P pt_tmp2;
	if (s.n == "arc") {
		for (unsigned int i = 0; i < p.size(); i++) {
			if (s.pt1 == p[i].id) {
				cout << "s.pt1 :   " << s.pt1 << " p[i].id :    " << p[i].id
						<< endl;
				pt_tmp1 = p[i];
			}
		}
		for (unsigned int j = 0; j < p.size(); j++) {
			if (s.pt2 == p[j].id) {
				pt_tmp2 = p[j];
			}
		}
	}
	P centre;
	centre.x = s.Xc;
	centre.y = s.Yc;
	alpha = findAngle(centre, pt_tmp1);
	beta = findAngle(centre, pt_tmp2);
	anglesomme = abs(alpha - beta);
	anglesomme = 360 - anglesomme;
	k = sqrt(
			(pt_tmp1.x - centre.x) * (pt_tmp1.x - centre.x)
					+ (pt_tmp1.y - centre.y) * (pt_tmp1.y - centre.y))
			* anglesomme;
	return k;
}

double longSeg(S &s, vector<P> &p) {
	double k = 0;
	if (s.n == "segment") {
		P pt_tmp1;
		P pt_tmp2;

		for (unsigned int i = 0; i < p.size(); i++) {
			if (s.pt1 == p[i].id) {
				pt_tmp1 = p[i];
			}
		}
		for (unsigned int j = 0; j < p.size(); j++) {
			if (s.pt2 == p[j].id) {
				pt_tmp2 = p[j];
			}
		}

		k = sqrt(
				(pt_tmp1.x - pt_tmp2.x) * (pt_tmp1.x - pt_tmp2.x)
						+ (pt_tmp1.y - pt_tmp2.y) * (pt_tmp1.y - pt_tmp2.y));

	}
	return k;
}

void AfficherPoint(vector<P> &points) {
	for (unsigned int i = 0; i < points.size(); i++) {
		cout << "Point: " << points[i].id << " X: " << points[i].x << " Y: "
				<< points[i].y << endl;
	}
	cout << endl;
}

S changerSensSegment(S & s) {
	S tmp = s;

	s.pt2 = tmp.pt1;
	s.pt1 = tmp.pt2;
	return s;
}

vector<S> trierSegments(vector<S> &s) {
	vector<S> elems;
	unsigned int taille = s.size();
	unsigned int taillej = s.size();
	unsigned int taillei = s.size();
	double objectif = 1;
	unsigned int fin = 0;
	S tmp;

	while (fin != taille) {
		unsigned int i = 0;
		while (i <= taillei) {
			if (objectif == s[i].pt1) {
				elems.push_back(s[i]);
				objectif = s[i].pt2;
				s.erase(s.begin() + i);
				cout << endl;
				taillei = s.size();
				fin = fin + 1;
				break;
			}
			i = i + 1;
		}

		unsigned int j = 0;
		if (i > taillei) {
			while (j < taillej) {
				if (objectif == s[j].pt2) {
					if (s[j].n == "arc") {
						elems.push_back(s[j]);
						objectif = s[j].pt1;
						s.erase(s.begin() + j);
						//taillej=s.size();

						fin = fin + 1;
						break;
					}
					tmp = changerSensSegment(s[j]);
					s[j] = tmp;
					break;
				}
				j = j + 1;
			}
		}

		if (j >= taillej) {
			cout << "le point " << objectif << " n'existe pas" << endl;
			exit(1);
		}
	}
	return elems;
}

vector<string> split2(const string &s, string delimiter) {
	vector<string> elems;

	string sTmp(s);  //" 1  0.1  0.25";

	size_t zero = 0;
	size_t pos = 0;
	string token;

	do {
		pos = sTmp.find(delimiter);
		if (pos > zero) {
			token = sTmp.substr(0, pos);
			elems.push_back(token);
		}
		if (pos >= zero)
			sTmp.erase(0, pos + delimiter.length());

	} while (pos != string::npos);

	elems.push_back(sTmp);

	return elems;
}

double string_to_double(const string& s) {
	stringstream i(s);
	double x;
	if (!(i >> x))
		return ERROR_DOUBLE;
	return x;
}

P transformerPoint(string ligne) {
	P p;
	vector<string> tabString = split2(ligne, " ");

	p.id = string_to_double(tabString[0]);
	p.x = string_to_double(tabString[1]);
	p.y = string_to_double(tabString[2]);

	return p;
}

S transformerSegment(string line) {
	S s;
	vector<string> tabString = split2(line, " ");
	s.n = tabString[0];
	s.pt1 = string_to_double(tabString[1]);
	s.pt2 = string_to_double(tabString[2]);
	s.Xc = ERROR_ARC;
	s.Yc = ERROR_ARC;
	if (s.n == "arc") {
		s.Xc = string_to_double(tabString[3]);
		s.Yc = string_to_double(tabString[4]);
	}
	return s;

}

int lireFichier(string path, vector<string> &v) {
	int nbline = 0;
	string l;
	l = "";
	ifstream fil(path.c_str());

	if (fil.is_open()) {
		while (getline(fil, l)) {
			v.push_back(l);
			nbline = nbline + 1;
		}
		fil.close();
	}
	return nbline;
}

int chercherString(int debutRecherche, vector<string> &v, string recherche) {
	for (unsigned int i = debutRecherche; i < v.size(); i++) {
		if (v[i].find(recherche) != string::npos) {
			return i;
		}
	}
	return -1;
}

int chercherString(vector<string> &v, string recherche) {
	return chercherString(0, v, recherche);
}

double TotalAngle(vector<P> points) {
	double total = 0;
	for (unsigned int i = 0; i < points.size(); i++) {
		double b = findAngle(points[i + 1], points[i]);
		if (i == points.size() - 1) {
			b = findAngle(points[0], points[i]);
			total = total + b;
		} else {
			total = total + b;
		}
	}
	return total;
}

void AfficherAngle(vector<P> points) {
	double total = 0;
	for (unsigned int i = 0; i < points.size(); i++) {
		double b = findAngle(points[i + 1], points[i]);
		if (i == points.size() - 1) {

			b = findAngle(points[0], points[i]);
			cout << "Angle: " << b << "° ente " << points[0].id << " et "
					<< points[i].id << endl;
			total = total + b;
		} else {
			cout << "Angle: " << b << "° ente " << points[i + 1].id << " et "
					<< points[i].id << endl;
			total = total + b;
		}
	}
}

int main() {
///////////////////////////////////////////////////////////
	vector<string> lignesLues;
	string nomFichier("point6_point7.geo");
	int nbline;

	nbline = lireFichier(nomFichier, lignesLues);

	cout << "nombre de lignes : " << nbline << endl;
//////////////////////////////////////////////////////////

	/*for (unsigned int i = 0; i < lignesLues.size(); i++ ) {
	 cout << lignesLues[i] << endl;
	 }*/

	unsigned int pdeb = chercherString(lignesLues, "$points");
	unsigned int pfin = chercherString(pdeb, lignesLues, "=======");

	cout << "pdeb : " << pdeb << endl;
	cout << "pfin : " << pfin << endl;

	pdeb += 2;
	pfin -= 2;

	// Traitement des lignes
	vector<P> points;
	P pTmp;

	for (unsigned int i = pdeb; i <= pfin; i++) {
		pTmp = transformerPoint(lignesLues[i]);
		points.push_back(pTmp);
	}

	unsigned int sdeb = chercherString(lignesLues, "$courbes");
	unsigned int sfin = chercherString(sdeb, lignesLues, "=======");

	cout << "sdeb : " << sdeb << endl;
	cout << "sfin : " << sfin << endl;

	sdeb += 2;
	sfin -= 2;

	// Traitement des lignes
	vector<S> segments;
	S sTmp;

	for (unsigned int i = sdeb; i <= sfin; i++) {
		sTmp = transformerSegment(lignesLues[i]);
		sTmp.id = i - sdeb + 1;
		segments.push_back(sTmp);
	}
	double t = TotalAngle(points);

	cout << "Total Angle: " << t << endl;

	AfficherPoint(points);

	AfficherSegment(segments);

	vector<S> Seg_trie = trierSegments(segments);

	for (unsigned int i = 0; i < Seg_trie.size(); i++) {
		Seg_trie[i].l = longSeg(Seg_trie[i], points);
	}

	for (unsigned int i = 0; i < Seg_trie.size(); i++) {
		if (Seg_trie[i].n == "arc") {
			Seg_trie[i].l = longArc(Seg_trie[i], points);
		}
	}

	AfficherAngle(points);

	AfficherSegment(Seg_trie);

	return 0;
}

	
   RDM - Dessin - Maillage
   Calcul des Structures par la M�thode des �l�ments Finis

   Version  - 6.17 - 29 mars 2011

   Utilisateur : Nedellec

==========================================================================================================================================

																$debut du fichier

==========================================================================================================================================

																$version

6.17

==========================================================================================================================================

																$SI unites
$nom du fichier
projet mef.geo

==========================================================================================================================================

																$date

3/5/2016

==========================================================================================================================================

																$points

   1  0.00000000000E+00  1.00000000000E-01 0  1.00  	//
   2  5.00000000000E-02  7.50000000000E-02 0  1.00 		//
   3  1.50000000000E-01  7.50000000000E-02 0  1.00 		//==//num�ro des points cr��s dans l'ordre	//coordonn�e en X	//coordonn�e en Y
   4  2.00000000000E-01  2.50000000000E-02 0  1.00 		//
   5  2.00000000000E-01  0.00000000000E+00 0  1.00 		//
   6  0.00000000000E+00  0.00000000000E+00 0  1.00 		//

==========================================================================================================================================

																$courbes

segment 6 1 101 0 										//
segment 1 2 101 0 										//
segment 2 3 101 0 										//=//num�ro des segments cr��s dans l'ordre	//point origine	//point final
segment 6 5 101 0 										//	
segment 5 4 101 0 										//
arc 4 3  1.75000000000E-01  5.00000000000E-02 101 0 	////// fin des courbes

==========================================================================================================================================

																$fenetre

-6.36807471874E-02  2.23469008703E+00 -6.36807471874E-02  1.06368074719E+00

==========================================================================================================================================

																$maillage

elements 800
lissage 3
jacobien 0.70

//// fin maillage

==========================================================================================================================================

$fin du fichier

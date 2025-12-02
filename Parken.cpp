/*
 * Parken.cpp
 *
 *  Created on: 18.11.2025
 *      Author: test
 */

#include "Parken.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Losfahren.h"

extern double dGlobaleZeit;
extern double dEpsilon;


Parken::Parken(Weg& weg, double Startzeitpunkt):
	Verhalten(weg),
	p_dStart(Startzeitpunkt)
{
	// TODO Auto-generated constructor stub

}

Parken::~Parken()
{
	// TODO Auto-generated destructor stub
}

//Überschriebene Funktion für die Strecke
double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	if(dGlobaleZeit<p_dStart-dEpsilon)
	{
		return 0.0;
	}
	//wirft exception
	throw Losfahren(aFzg,p_pWeg);
}

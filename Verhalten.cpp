/*
 * Verhalten.cpp
 *
 *  Created on: 17.11.2025
 *      Author: test
 */

#include "Verhalten.h"
#include "Weg.h"

Verhalten::Verhalten(Weg& weg): p_pWeg(weg)
{

}

Verhalten::~Verhalten()
{
	// TODO Auto-generated destructor stub
}


/* wurde nach "Fahren" übertragen
double Verhalten::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	double dStrecke = aFzg.dGeschwindigkeit() * dZeitIntervall;
	double dAbschnitt = aFzg.getAbschnitt();
	double dLaenge = p_pWeg.getLaenge();

	if (dAbschnitt > dLaenge)
	{
		std::cout<<"Fehler! Der gefahrene Abschnitt darf nicht größer sein als die Laenge der Strecke"<<std::endl;
		exit (1);
	}

	if (dAbschnitt + dStrecke > dLaenge)
	{
		//Falls das Auto das Wegende erreicht, wird nur die verbleibende Strecke zurückgegeben,
		//damit dieses genau am Ende des Weges ankommt
		return dLaenge - dAbschnitt;
	}

	return dStrecke;

}
*/


Weg& Verhalten::getWeg() const
{
	return p_pWeg;
}



/*
 * Fahren.cpp
 *
 *  Created on: 18.11.2025
 *      Author: test
 */

#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"

extern double dEpsilon;

Fahren::Fahren(Weg& weg): Verhalten(weg)
{

}

Fahren::~Fahren()
{
	// TODO Auto-generated destructor stub
}


double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{

	double dStrecke = aFzg.dGeschwindigkeit() * dZeitIntervall;
	double dAbschnitt = aFzg.getAbschnitt();
	double dLaenge = p_pWeg.getLaenge();
	double dSchranke = p_pWeg.getSchranke();

	// Streckenende prüfen (Exception)
	if (dAbschnitt > dLaenge - dEpsilon)
	{
		throw Streckenende(aFzg, p_pWeg);
	}
	// Überholverbot / Schranke prüfen
	// Wenn man weiter fahren würde, als die Schranke erlaubt:
	if (dAbschnitt + dStrecke > dSchranke - dEpsilon)
	{
		//nur bis zur Schranke fahren
		dStrecke = dSchranke - dAbschnitt;
	}
	// Falls negative Strecke negativ:
	if (dStrecke < 0)
	{
		dStrecke = 0;
	}

	// Schranke für den Hintermann aktualisieren. Position ist die Grenze für das nächste Auto.
	p_pWeg.setSchranke(dAbschnitt + dStrecke);

	return dStrecke;


}

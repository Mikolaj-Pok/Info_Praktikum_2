/*
 * Fahrrad.cpp
 *
 *  Created on: 06.11.2025
 *      Author: test
 */

#include "Fahrrad.h"
#include "Weg.h"
#include "SimuClient.h"

#include <cmath>

Fahrrad::Fahrrad()
{
	// TODO Auto-generated constructor stub

}

Fahrrad::~Fahrrad()
{
	// TODO Auto-generated destructor stub
}

Fahrrad::Fahrrad(std::string sName, double dGeschwindigkeit)
	:Fahrzeug(sName,dGeschwindigkeit)
	{

	}

double Fahrrad::dGeschwindigkeit() const
	{
		double dAbnahmePro20km=p_dGesamtStrecke/20.0;

		//reduziert die Momentangschwindigkeit sprunghaft um 10% alle 20km
		//double dMomentanGeschwindigkeit = p_dMaxGeschwindigkeit;
		//for (int i = 0; i < dAbnahmePro20km; ++i)
		//{
		//		dMomentanGeschwindigkeit *= 0.9;
		//}

		//reduziere die Geschwindigkeit so lange exponentiell bis der index die Abnahme erreicht wurde
		double dMomentanGeschwindigkeit= p_dMaxGeschwindigkeit*pow(0.9,dAbnahmePro20km);

		if (dMomentanGeschwindigkeit<12.0)
			{
				dMomentanGeschwindigkeit=12.0;
			}

		return dMomentanGeschwindigkeit;
	}

/*
 * alte Ausgabefunktion
void Fahrrad::vAusgeben() const
{
	Fahrzeug::vAusgeben();
		std::cout<< std::setw(18) << "----";
		std::cout<< std::setw(18) << "----";

}
*/

void Fahrrad::vAusgeben(std::ostream& ausgabe) const
	{
		Fahrzeug::vAusgeben(ausgabe);
		ausgabe<< std::setw(18) << "----"
			   << std::setw(18) << "----";
	}




void Fahrrad::vZeichnen(const Weg& weg) const
{
	//Zeichenfunktion für Fahrrad
	bZeichneFahrrad(p_sName,weg.getName(),(p_dAbschnittStrecke/weg.getLaenge()),dGeschwindigkeit());
}

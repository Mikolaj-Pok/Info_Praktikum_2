/*
 * PKW.cpp
 *
 *  Created on: 06.11.2025
 *      Author: test
 */

#include "PKW.h"
#include "Weg.h"
#include "SimuClient.h"

extern double dGlobaleZeit;

PKW::PKW()
{
	// TODO Auto-generated constructor stub

}

PKW::~PKW()
{
	// TODO Auto-generated destructor stub
}

PKW::PKW(std::string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen)
	:Fahrzeug(sName, dMaxGeschwindigkeit), //muss mit Fahrzeug-Konstruktor initialisiert werden, da sName und dMax... nicht in PKW zu finden sind
	 p_dVerbrauch(dVerbrauch),
	 p_dTankvolumen(dTankvolumen),
	 p_dTankinhalt(dTankvolumen/2)
	{

	}

double PKW::dTanken(double dMenge)
	{
	if(p_dTankinhalt+dMenge>p_dTankvolumen)
		{
		double dGetankteMenge= p_dTankvolumen-p_dTankinhalt;
		p_dTankinhalt = p_dTankvolumen;
		return dGetankteMenge;

		}
	else
		{
		p_dTankinhalt += dMenge;
		return dMenge;
		}

	}

void PKW::vSimulieren()
	{
		if(p_dTankinhalt>0.0)
			{
			//Speichert den Betrag der alten Strecke
			double dStrecke = p_dGesamtStrecke;
			Fahrzeug::vSimulieren();
			//Berechnet den Verbrauch aus dem Verbrauch und der Differenz von aktuell gefahrener Strecke und der zuvor gespeicherten -> Verbrauch durch Hundert, um den Verbrauch pro Kilometer zubekommen
			double dVerbrauch = (p_dGesamtStrecke-dStrecke)*p_dVerbrauch/100.0;
			p_dTankinhalt -= dVerbrauch;
			//Falls Tankinhalt negativ werden sollte, wird dieser auf 0 gesetzt
			if (p_dTankinhalt <0.0)
				{
					p_dTankinhalt = 0.0;
				}
			}
		else {
				p_dZeit = dGlobaleZeit;
			}
	}

/*
 * alte Ausgabefunktion:
void PKW::vAusgeben() const
	{
	Fahrzeug::vAusgeben();
	std::cout<<std::setw(18)<<p_dGesamtStrecke*p_dVerbrauch/100;
	std::cout<<std::setw(18)<<p_dTankinhalt;
	}
*/

void PKW::vAusgeben(std::ostream& ausgabe) const
	{
		Fahrzeug::vAusgeben(ausgabe);
		ausgabe<<std::setw(18)<<p_dGesamtStrecke*p_dVerbrauch/100 //GESAMTVERBRAUCH!!!!!!
			   <<std::setw(18)<<p_dTankinhalt;
	}

//Kopiert die zusätzlichen Stammdaten von PKW
PKW& PKW::operator=(const PKW& Zuweisungsfahrzeug)
	{
		Fahrzeug::operator=(Zuweisungsfahrzeug);
		p_dVerbrauch = Zuweisungsfahrzeug.p_dVerbrauch;
		p_dTankvolumen = Zuweisungsfahrzeug.p_dTankvolumen;
		p_dTankinhalt = Zuweisungsfahrzeug.p_dTankinhalt; //muss der Tankinhalt auch kopiert werden?

		return *this;
	}

PKW& PKW::operator=(const Fahrzeug& Zuweisungsfahrzeug)
{
	Fahrzeug::operator=(Zuweisungsfahrzeug);

	return *this;
}


double PKW::dGeschwindigkeit() const
{
	//falls Verhalten vorhanden...
	if(p_pVerhalten!=nullptr)
	{
		//dLimit ist das Tempolimit des jeweiligen Weges
		double dLimit=p_pVerhalten->getWeg().getTempolimit();
		if(p_dMaxGeschwindigkeit>dLimit)
		{
			return dLimit;
		}
	}

	return p_dMaxGeschwindigkeit;
}


void PKW::vZeichnen(const Weg& weg) const
{
	//Zeichenfunktion für PKW
	bZeichnePKW(p_sName,weg.getName(),(p_dAbschnittStrecke/weg.getLaenge()),dGeschwindigkeit(),p_dTankinhalt);
}



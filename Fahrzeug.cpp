/*
 * Fahrzeug.cpp
 *
 *  Created on: 30.10.2025
 *      Author: Mikolaj Pokrywinski
 */

#include "Fahrzeug.h"
#include "Weg.h"
#include "Fahren.h"
#include "Parken.h"

#include <iomanip>
#include <iostream>

extern double dGlobaleZeit;


Fahrzeug::Fahrzeug(): Simulationsobjekt()

	//Intitialisierungsliste

		{
			//std::cout<<"Standardkonstruktor Fahrzeug"<<std::endl;
			//std::cout<<"ID des Fahrzeugs:"<<p_iID<<std::endl<< "ID des Fahrzeugs: " << p_iID << std::endl;
		}


//Konstruktor aber der Name wird zusätzlich bestimmt
Fahrzeug::Fahrzeug (std::string sName)
	//Initialisierungsliste
	:Simulationsobjekt(sName)
		{
		/*	std::cout<<"Name des Fahrzeugs:"<<p_sName<<std::endl;
			std::cout<<"ID des Fahrzeugs:"<<p_iID<<std::endl; */
		}


//Konstruktor mit Namen und MaxGeschwindigkeit
Fahrzeug::Fahrzeug (std::string sName, double dMaxGeschwindigkeit)
	//Initialisierungsliste
	:Simulationsobjekt(sName),
	 p_dMaxGeschwindigkeit(dMaxGeschwindigkeit > 0 ? dMaxGeschwindigkeit:0) //MaxGeschwindigkeit muss positiv sein!
		{
		/*	std::cout<<"Name des Fahrzeugs:"<<p_sName<<std::endl;
			std::cout<<"Maximale Geschwindigkeit:"<<p_dMaxGeschwindigkeit<<std::endl;
			std::cout<<"ID des Fahrzeugs:"<<p_iID<<std::endl; */
		}

Fahrzeug::~Fahrzeug()
	{
		//std::cout<<"Aufruf des Destruktors"<<std::endl;
	}

/*
void Fahrzeug::vAusgeben() const
		{
			std::cout<<std::resetiosflags(std::ios::left)<<std::setiosflags(std::ios::right);//rechtsbündig
			std::cout<<std::setw(4)<<p_iID<<" ";
			std::cout<<std::resetiosflags(std::ios::right)<<std::setiosflags(std::ios::left);//linksbündig
			std::cout<<std::setw(12)<<p_sName;
			std::cout<<std::resetiosflags(std::ios::left)<<std::setiosflags(std::ios::right);//rechtsbündig
			std::cout<<std::setw(18)<<p_dMaxGeschwindigkeit;
			std::cout<<std::setw(18)<<p_dGesamtStrecke;
			std::cout<<std::setw(25)<<dGeschwindigkeit();
		}
*/

void Fahrzeug::vAusgeben(std::ostream& ausgabe) const
		{
		Simulationsobjekt::vAusgeben(ausgabe);

		ausgabe<<std::resetiosflags(std::ios::left)<<std::setiosflags(std::ios::right)//rechtsbündig
		<<std::setw(18)<<p_dMaxGeschwindigkeit
		<<std::setw(18)<<p_dGesamtStrecke
		<<std::setw(18)<<p_dAbschnittStrecke
		<<std::setw(25)<<dGeschwindigkeit();
		}

void Fahrzeug::vKopf()
	{
	//Definition durchgezogene Linie:
	static std::string line(150,'-');
	std::cout<<std::endl;
	std::cout<<std::resetiosflags(std::ios::left)<<std::setiosflags(std::ios::right); //rechtsbündig
	std::cout<<std::setw(4)<<"ID ";
	std::cout<<std::resetiosflags(std::ios::right)<<std::setiosflags(std::ios::left);//linksbündig
	std::cout<<std::setw(15)<<"Name";
	std::cout<<std::resetiosflags(std::ios::left)<<std::setiosflags(std::ios::right);//rechtsbündig
	std::cout<<std::setw(18)<<"MaxGeschwindigkeit";
	std::cout<<std::setw(18)<<"Gesamtstrecke";
	std::cout<<std::setw(18)<<"Abschnittstrecke";
	std::cout<<std::setw(25)<<"MomentanGeschwindigkeit";
	std::cout<<std::setw(18)<<"Gesamtverbrauch";
	std::cout<<std::setw(18)<<"Tankinhalt"<<std::endl;
	std::cout<<line<<std::endl;
	}

void Fahrzeug::vSimulieren()
	{
	//bestimmt vergangene Zeit
	double dZeitDifferenz=dGlobaleZeit-p_dZeit;
	//Falls die Zeitdifferenz nicht 0 ist (also Zeit vergangen ist)
	if (dZeitDifferenz>0.0)
		{
		p_dZeit=dGlobaleZeit;
		double strecke=0.0;
		if (p_pVerhalten != nullptr)
			{
			//Aufruf von der dStrecke-Funktion, welche die vom Objekt gefahrene Strecke bestimmt
			strecke = p_pVerhalten->dStrecke(*this, dZeitDifferenz);
			}
		else
			{
			strecke = dGeschwindigkeit()*dZeitDifferenz;
			}
		if (strecke>0)
			{
			p_dGesamtStrecke += strecke;
			p_dAbschnittStrecke += strecke;
			p_dGesamtZeit += dZeitDifferenz;
			}
		}

	}

//Falls das Fahrzeug nicht tanken kann bzw. die Funktion nicht überschrieben ist (Fahrrad):
double Fahrzeug::dTanken(double dMenge)
	{
		return 0.0;
	}

//Falls nicht überschrieben, gibt die Funktion die maximale Geschwindigkeit wieder (z.B. PKW)
double Fahrzeug::dGeschwindigkeit() const
	{
		return p_dMaxGeschwindigkeit;
	}

//Überladener '<'-Operator
bool Fahrzeug::operator<(const Fahrzeug &Vergleichsobjekt)
{
	if (p_dGesamtStrecke<Vergleichsobjekt.p_dGesamtStrecke)
	{
		return true;
	}
	return false;
}

// Zuweisungsoperator kopiert die Stammdaten ohne die ID zu kopieren!
Fahrzeug& Fahrzeug::operator=(const Fahrzeug& Zuweisungsfahrzeug)
{
	//Selbstzuweisung vermeiden
	if (this==&Zuweisungsfahrzeug)
	{
		return *this;
	}

	p_sName =Zuweisungsfahrzeug.p_sName + " Kopie";
	p_dMaxGeschwindigkeit = Zuweisungsfahrzeug.p_dMaxGeschwindigkeit;
	p_dGesamtStrecke=0;
	p_dAbschnittStrecke = 0;
	p_dZeit=dGlobaleZeit;
	p_dGesamtZeit=0;

	return *this; //da es sich um Fahrzeug& handelt
}


void Fahrzeug::vNeueStrecke(Weg& weg)
{
	//man dem Verhalten einen neuen unique_ptr zuordnet wird der alte automatisch gelöscht
	//außerdem ist durch die Referenz &Weg jedem weg ein einzigartiges Verhalten zuzuordnen
	//die alte Instanz  wird gelöscht!!
	p_pVerhalten = std::make_unique<Fahren>(weg);
	//neuer Weg, also muss der Abschnitt Null sein
	p_dAbschnittStrecke=0.0;
}

void Fahrzeug::vNeueStrecke(Weg& weg, double dStartzeit)
{
	p_pVerhalten = std::make_unique<Parken>(weg, dStartzeit);
	p_dAbschnittStrecke=0.0;
}

double Fahrzeug::getAbschnitt() const
{
	return p_dAbschnittStrecke;
}

void Fahrzeug::vZeichnen(const Weg&) const
{
	//leer... Fahrzeuge können per se nicht gezeichnet werden
}



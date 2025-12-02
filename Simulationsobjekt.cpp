/*
 * Simulationsobjekt.cpp
 *
 *  Created on: 13.11.2025
 *      Author: test
 */

#include "Simulationsobjekt.h"

//Globale Uhr in Stunden
double dGlobaleZeit=0.0;


Simulationsobjekt::Simulationsobjekt():
	p_sName("Unbekanntes Simulationsobjekt"),
	p_dZeit(dGlobaleZeit)


	{

	}

Simulationsobjekt::~Simulationsobjekt()
	{
		std::cout <<"ID: " << p_iID << " Name: " << p_sName << " wurde geloescht." << std::endl;
	}

Simulationsobjekt::Simulationsobjekt(std::string sName):
		p_sName(sName),
		p_dZeit(dGlobaleZeit)
	{

	}

void Simulationsobjekt::vAusgeben(std::ostream& ausgabe) const
	{
	ausgabe<<std::resetiosflags(std::ios::left)<<std::setiosflags(std::ios::right)//rechtsbündig
			<<std::setw(4)<<p_iID<<" "
			<<std::resetiosflags(std::ios::right)<<std::setiosflags(std::ios::left)//linksbündig
			<<std::setw(15)<<p_sName;
	}

std::ostream& operator<<(std::ostream& ausgabe, const Simulationsobjekt& simulationsobjekt)
	{
		simulationsobjekt.vAusgeben(ausgabe);

		return ausgabe;
	}

bool Simulationsobjekt::operator==(const Simulationsobjekt& Vergleichsobjekt) const
{
		return p_iID==Vergleichsobjekt.p_iID;
}

std::string Simulationsobjekt::getName() const
{
	return p_sName;
}






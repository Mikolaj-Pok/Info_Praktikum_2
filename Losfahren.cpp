/*
 * Losfahren.cpp
 *
 *  Created on: 18.11.2025
 *      Author: test
 */

#include "Losfahren.h"
#include "Fahrzeug.h"
#include "Weg.h"


Losfahren::Losfahren(Fahrzeug& fahrzeug, Weg& weg):Fahrausnahme(fahrzeug, weg)
{
}

Losfahren::~Losfahren()
{
	// TODO Auto-generated destructor stub
}

void Losfahren::vBearbeiten()
{
	//Fahrzeug fährt los, es wird also in die vAnnahme funktion mit nur *einem* Argument eingesetzt,
	//da diese das Auto auf die gleiche Strecke setzt und zum Fahren bringt
	p_pWeg.vAnnahme(p_pWeg.pAbgabe(p_pFahrzeug));
	std::cout<<"Fahrausnahme: Losfahren"<<std::endl<<"Zeit: "<< dGlobaleZeit <<std::endl<<"Fahrzeug: "<< p_pFahrzeug.getName() <<std::endl<< "Weg: " << p_pWeg.getName()<<std::endl<<std::endl;
}


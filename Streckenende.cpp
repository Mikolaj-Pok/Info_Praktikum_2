/*
 * Streckenende.cpp
 *
 *  Created on: 18.11.2025
 *      Author: test
 */

#include "Streckenende.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Kreuzung.h"
#include <iomanip>

extern double dGlobaleZeit;

Streckenende::Streckenende(Fahrzeug& fahrzeug, Weg& weg):Fahrausnahme(fahrzeug, weg)
{

}

Streckenende::~Streckenende()
{
	// TODO Auto-generated destructor stub
}

void Streckenende::vBearbeiten()
{

	//man definiere einen shared_ptr als Ziel eines Weges
	std::shared_ptr<Kreuzung> pZielkreuzung = p_pWeg.getZielkreuzung();

	//Falls Zielkreuzung vorhanden
	if (pZielkreuzung != nullptr)
	{
		//Fahrzeug am Streckenende wird betankt
		pZielkreuzung->vTanken(p_pFahrzeug);
		//bestimmt zufälligen nächsten Weg
		std::shared_ptr<Weg> pNaechsterWeg = pZielkreuzung->pZufaelligerWeg(p_pWeg);
		//nächster Weg nimmt vom vorherigen Weg abgegebenes Fahrzeug an
		pNaechsterWeg->vAnnahme(p_pWeg.pAbgabe(p_pFahrzeug));
		//AUSGABE:
		std::cout
		<<std::resetiosflags(std::ios::right)<<std::setiosflags(std::ios::left)
		<<std::setw(10)<<"ZEIT"
		<<std::resetiosflags(std::ios::left)<<std::setiosflags(std::ios::right)
		<< ": ["<< dGlobaleZeit <<"] "<<std::endl

		<<std::resetiosflags(std::ios::right)<<std::setiosflags(std::ios::left)
		<<std::setw(10)<<"KREUZUNG"
		<<std::resetiosflags(std::ios::left)<<std::setiosflags(std::ios::right)
		<< ": ["<< pZielkreuzung->getName() << "] ["<<pZielkreuzung->getTankstelle() <<"] "<< std::endl

		<<std::resetiosflags(std::ios::right)<<std::setiosflags(std::ios::left)
		<<std::setw(10)<<"FAHRZEUG"
		<<std::resetiosflags(std::ios::left)<<std::setiosflags(std::ios::right)
		<< ": ["<< p_pFahrzeug.getName() << "] "<< std::endl

		<<std::resetiosflags(std::ios::right)<<std::setiosflags(std::ios::left)
		<<std::setw(10)<<"WECHSEL"
		<<std::resetiosflags(std::ios::left)<<std::setiosflags(std::ios::right)
		<< ": ["<< p_pWeg.getName() << "] -> ["<< pNaechsterWeg->getName() <<"] "<< std::endl<<std::endl;


	}
	else
	{
		//Entfernt das Fahrzeug vom Weg falls keine Zielkreuzung vorhanden ist
		std::cout<<"Fahrausnahme: Streckenende"<<std::endl<<"Zeit: "<< dGlobaleZeit <<std::endl<<"Fahrzeug: "<< p_pFahrzeug.getName() <<std::endl<< "Weg: " << p_pWeg.getName()<<std::endl<<std::endl;
		p_pWeg.pAbgabe(p_pFahrzeug);
	}


}



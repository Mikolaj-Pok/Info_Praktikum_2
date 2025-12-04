/*
 * Simulation.cpp
 *
 *  Created on: 02.12.2025
 *      Author: test
 */

#include "Simulation.h"
#include "Kreuzung.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "SimuCLient.h"
#include "Tempolimit.h"
#include "PKW.h"
#include "Fahrrad.h"

#include <fstream>
#include <iostream>
#include <memory>

Simulation::Simulation()
{
	// TODO Auto-generated constructor stub

}

Simulation::~Simulation()
{
	// TODO Auto-generated destructor stub
}

void Simulation::vEinlesen(std::istream& eingabe)
{
	//exceptions werden aktiviert mit fokus auf logische (failbit) und schwerwiegende (badbit) Fehler -> Exception wird dann geworfen
	eingabe.exceptions(std::ios_base::failbit | std::ios_base::badbit); //keine Exception für End of File!
	std::string sWort;
	int iZeile=0;

	do
	{
		try
		{
			eingabe>>sWort;
			++iZeile;

			if (sWort == "KREUZUNG")
			{
				std::shared_ptr<Kreuzung> kreuzung = std::make_shared<Kreuzung>();
				eingabe>>*kreuzung;

			}

			else if (sWort == "STRASSE")
			{
				std::shared_ptr<Kreuzung> NameQ = std::make_shared<Kreuzung>();
				eingabe >> *NameQ;
				std::shared_ptr<Kreuzung> NameZ = std::make_shared<Kreuzung>();
				eingabe >> *NameZ;
				std::string NameW1;
				eingabe >> NameW1;
				std::string NameW2;
				eingabe >> NameW2;
				double laenge;
				eingabe >> laenge;

				Tempolimit limit;
				int in;
				eingabe >> in;
				switch (in)
				{
					case 1:
						limit = Tempolimit::Innerorts;
						break;
					case 2:
						limit = Tempolimit::Landstrasse;
						break;
					case 3:
						limit = Tempolimit::Autobahn;
						break;
					default:
						throw std::runtime_error(std::to_string(in) + " ist eine ungültige Eingabe");
				}

				bool Ueberholverbot;
				eingabe >> in;
				switch (in)
				{
					case (0):
						Ueberholverbot=false;
						break;
					case (1):
						Ueberholverbot=true;
						break;
					default:
						throw std::runtime_error(std::to_string(in) + " ist eine ungültige Eingabe");
				}

				Kreuzung::vVerbinde(NameW1,NameW2,laenge,NameQ,NameZ,limit,Ueberholverbot);

			}

			else if (sWort == "PKW" || sWort == "FAHRRAD")
			{
				std::unique_ptr<Fahrzeug> Fzg;
				if (sWort == "PKW")
				{
					Fzg = std::make_unique<PKW>();
				}
				else
				{
					Fzg = std::make_unique<Fahrrad>();
				}
				eingabe >> *Fzg;

				std::string NameS;
				eingabe >> NameS;

				double dZeitPunkt;
				eingabe >> dZeitPunkt;
			}

			else
			{
				throw std::runtime_error("'"+ sWort + "' ist keine gültige Eingabe!");
			}


		}

		catch (std::runtime_error& runtime_error)
		{
			if (!eingabe.eof()) //damit nicht das Ende des Dokuments als Fehler ausgegeben wird
			{
				std::cerr<<"Fehler in Zeile "<<iZeile<<":("<<runtime_error.what()<<")"<<std::endl;
				throw; //Fehler wird weitergegeben
			}
		}

	}while (!eingabe.eof());

	std::cout<<iZeile<< " Zeilten eingelesen." <<std::endl;

}

void Simulation::vSimulieren()
{

}

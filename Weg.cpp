/*
 * Weg.cpp
 *
 *  Created on: 13.11.2025
 *      Author: test
 */

#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"
#include "Kreuzung.h"

#include <iomanip>
#include <iostream>


Weg::Weg(std::string sName, double dLaenge, Tempolimit eTempolimit, bool bUeberholverbot, std::shared_ptr<Kreuzung> pZielkreuzung):
	Simulationsobjekt(sName),
	p_dLaenge(dLaenge),
	p_eTempolimit(eTempolimit),
	p_bUeberholverbot(bUeberholverbot),
	p_pZielkreuzung(pZielkreuzung)
{
	// TODO Auto-generated constructor stub
}

Weg::~Weg()
{
	// TODO Auto-generated destructor stub
}

double Weg::getTempolimit() const
{
	return (double) p_eTempolimit;
}

void Weg::vSimulieren()
{
	//Aktualisieren vor der Simulationsschleife
	p_pFahrzeug.vAktualisieren();

	//vor der Simulationsschleife wird das Wegende für das erste Fahrzeug als Schranke gesetzt!
	p_dSchranke=p_dLaenge;

	// Schleife über alle Elemente in p_pFahrzeug, das Schleifenelement wird
	// als Referenz über p angesprochen (Skript S.21)
	for (auto& p : p_pFahrzeug)
	{
		//try-Block überwacht den Code, wo eine Exception geworfen werden kann (S.88)
		try
			{
			//p greift über den "this"-Zeiger auf die Simulationsfunktion von "Fahrzeug" zu
			p->vSimulieren();
			p->vZeichnen(*this); //*this ist ein dereferenzierter Zeiger also das Objekt (Weg) selbst
			}
		//Bei einer Hierarchie von Exceptions sollte die Ausnahme mittels einer polymorphen Funktion
		//bearbeitet werden -> Deshalb nur 1x catch
		catch (Fahrausnahme& fahrausnahme)
			{
			//vBearbeiten ist polymorph definiert -> Funkt. von Losfahren ODER Streckenende wird ausgeführt
			fahrausnahme.vBearbeiten();
			}
	}

	//Aktualisieren nach der Simulationsschleife
	p_pFahrzeug.vAktualisieren();
}

void Weg::vAusgeben(std::ostream& ausgabe) const
{
	Simulationsobjekt::vAusgeben(ausgabe);

	ausgabe
	<<std::resetiosflags(std::ios::right)<<std::setiosflags(std::ios::left)
	<<std::setw(1)<<" :"
	<<std::resetiosflags(std::ios::left)<<std::setiosflags(std::ios::right)
	<<std::setw(10)<< p_dLaenge
	<<std::resetiosflags(std::ios::right)<<std::setiosflags(std::ios::left)
	<<"   (";
	for (auto& p : p_pFahrzeug)
	{
		ausgabe<<p->getName()<<" ";
	}
	ausgabe<<")" <<std::endl;


}

void Weg::vKopf()
{
	//Definition durchgezogene Linie:
		static std::string line(50,'-');
		std::cout<<std::endl;
		std::cout<<std::resetiosflags(std::ios::left)<<std::setiosflags(std::ios::right); //rechtsbündig
		std::cout<<std::setw(3)<<"ID";
		std::cout<<std::setw(1)<<" |";
		std::cout<<std::resetiosflags(std::ios::right)<<std::setiosflags(std::ios::left);//linksbündig
		std::cout<<std::setw(15)<<" Name ";
		std::cout<<std::setw(1)<<" | ";
		std::cout<<std::setw(10)<<" Laenge";
		std::cout<<std::setw(1)<<" | ";
		std::cout<<std::setw(18)<<"Fahrzeuge "<<std::endl;
		std::cout<<line<<std::endl;
}

double Weg::getLaenge() const
{
	return p_dLaenge;
}

//Annahme von fahrenden Fahrzeugen Fzg
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> Fzg)
{
	//Beim Fahrzeug wird der Weg, für den diese Funktion aufgerufen, wird als neue Strecke gesetzt
	Fzg->vNeueStrecke(*this);
	//Das fahrende Fahrzeug wird hinten in der Liste von Weg aufgenommen
	p_pFahrzeug.push_back(move(Fzg));
}

//Annahme von parkenden Fahrzeugen Fzg mit Startzeit dStartzeit
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> Fzg, double dStartzeit)
{
	//Beim Fahrzeug wird der Weg, für den diese Funktion aufgerufen, wird als neue Strecke gesetzt
	Fzg->vNeueStrecke(*this, dStartzeit);
	//Das parkende Fahrzeug wird vorne in der Liste von Weg aufgenommen
	p_pFahrzeug.push_front(move(Fzg));
}

//Funktion zum Löschen von Fahrzeugen aus der Liste
std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& gesuchtesFzg)
{
	//auto statt std::list::iterator
	//iteriert durch die gesamte Liste durch und prüft ob das gesuchte Fahrzeug vorhanden ist
   	for (auto it = p_pFahrzeug.begin(); it != p_pFahrzeug.end(); ++it)
	{
		//it: Liefert die Adresse bzw. den Iterator
		//*it: Liefert den Zeiger bzw. den unique_ptr
		//**it: Liefert den Wert bzw. das Objekt hier, Dereferenziert Iterator und Smart Pointer

   		//falls der Iterator auf einen nullptr trifft, weil ein Fahrzeug aus der Liste entfernt wurde und eine "Leiche" hinterlassen hat (CRASH)
   		if (*it== nullptr)
   		{
   			continue;
   		}

   		if(gesuchtesFzg == (**it))
		{
			//falls gefunden, speichere das Fahrzeug in einer temporären lokalen Variable
			auto temp_unique_ptr = move(*it); //auto statt std::unique_ptr<Fahrzeug>
			//lösche es aus der Liste
			p_pFahrzeug.erase(it);
			//gebe das entferte Objekt wieder
			return temp_unique_ptr;
		}
	}
	//falls nichts gefunden...
	return nullptr;

}


//Getter-Funktion für die virtuelle Schranke
double Weg::getSchranke() const
{
	if (p_bUeberholverbot)
	{
		return p_dSchranke;
	}
	//Falls kein Überholverbot vorhanden ist, gebe die Länge wieder , da sich die Fahrzeuge an keine Schranken halten müssen
	return p_dLaenge;
}

//Getter-Funktion für den Überholverbot Boolean
bool Weg::getUeberholverbot() const
{
	return p_bUeberholverbot;
}

//Funktion mit der die neue Schranke gesetzt wird
void Weg::setSchranke(double dSchranke)
{
		p_dSchranke=dSchranke;
}


std::shared_ptr<Weg> Weg::getRueckweg() const
{
	//lock() erzeugt temporär einen gültigen shared_ptr, der zurückgegeben werden kann
	return p_pRueckweg.lock();
}

std::shared_ptr<Kreuzung> Weg::getZielkreuzung() const
{
	//lock() erzeugt temporär einen gültigen shared_ptr, der zurückgegeben werden kann
	return p_pZielkreuzung.lock();
}

//damit ein Weg seinen direkten Rückweg kennt
void Weg::setRueckweg(std::shared_ptr<Weg> pRueckweg)
{
	//setzt den Rückwegsparameter auf den übergebenen Rückweg shared_pointer
	p_pRueckweg=pRueckweg;
}



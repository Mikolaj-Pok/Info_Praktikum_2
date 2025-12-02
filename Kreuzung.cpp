/*
 * Kreuzung.cpp
 *
 *  Created on: 28.11.2025
 *      Author: test
 */

#include "Kreuzung.h"
#include "Weg.h"
#include "Fahrzeug.h"


Kreuzung::Kreuzung()
{
	// TODO Auto-generated constructor stub

}

Kreuzung::~Kreuzung()
{
	//löscht die Wegeliste
	p_pWege.clear();
}

Kreuzung::Kreuzung(std::string sName, double dTankstelle):
	Simulationsobjekt(sName),
	p_dTankstelle(dTankstelle)
{

}
void Kreuzung::vVerbinde(std::string sNameHin,std::string sNameRueck, double dLaenge,
			std::shared_ptr<Kreuzung> pStartKreuzung, std::shared_ptr<Kreuzung> pZielKreuzung,
			Tempolimit limit, bool bUeberholverbot)
{
	//erzeugt(!) einen Hin- und Rückweg vom Datentyp Shared-Pointer
	std::shared_ptr<Weg> pHinweg = std::make_shared<Weg>(sNameHin, dLaenge, limit, bUeberholverbot, pZielKreuzung);
	std::shared_ptr<Weg> pRueckweg = std::make_shared<Weg>(sNameRueck, dLaenge, limit, bUeberholverbot, pStartKreuzung);
	//die erzeugten Wege werden mit ihren Rückwegen bekanntemacht
	pHinweg->setRueckweg(pRueckweg);
	pRueckweg->setRueckweg(pHinweg);
	//die jeweiligen Kreuzungen speichern die Wege, die von der Kreuzung wegführen in der Instanzvariable p_pWege
	pStartKreuzung->p_pWege.push_back(std::move(pHinweg)); //move, da der Besitz übergeben wird und die alte Referenz gelöscht
	pZielKreuzung->p_pWege.push_back(std::move(pRueckweg));

}

//Tankt das Fahrzeug voll und aktualisiert das Tankstellenvolumen
void Kreuzung::vTanken(Fahrzeug& fahrzeug)
{
	if(p_dTankstelle > 0.0)
	{
		double dGetankteMenge = fahrzeug.dTanken();
		p_dTankstelle -= dGetankteMenge;
		if(p_dTankstelle < 0)
		{
			p_dTankstelle = 0;
		}
		std::cout<<"Fahrzeug " << fahrzeug.getName() << " tankte " << dGetankteMenge << " Liter." << std::endl
		<< "Kreuzung " << getName() << " hat noch " << p_dTankstelle << " Liter übrig."<< std::endl;

	}
}

//nimmt Fahrzeuge auf und stellt diese parkend (Startzeit!) auf den ersten abgehenden Weg -> Initialisierung
void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit)
{
	//ruft die vAufnahme-Funktion von Weg.cpp auf um das Fahrzeug auf dem neuen Weg aufzunehmen
	if(dStartzeit>0.0)
	{
		p_pWege.front()->vAnnahme(std::move(pFahrzeug), dStartzeit);
	}
	else
	{
		//ohne oder mit negativer Startzeit -> fahrendes Auto
		p_pWege.front()->vAnnahme(std::move(pFahrzeug));
	}

}

//Simulationsfunktion
void Kreuzung::vSimulieren()
{
	//iteriert durch die p_pWege-Liste durch und ruft die Simulationsfunktion auf
	for(auto& it : p_pWege)
	{
		it->vSimulieren();
	}
}

std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& Hinweg)
{
	//Falls die Wege-Liste nur einen wegführenden Weg besitzt (Sackgasse!)
	if(p_pWege.size()==1)
	{
		return p_pWege.front();
	}
	//Erzeuge zufällige Zahl zwischen 1 und der Anzahl an möglichen Wegen
	//seed = 0 für die Reproduzierbarkeit
	const int seed = 0;
	static std::mt19937 device (seed);
	//man definiere eine Gleichverteilung von int-Werten zwischen 0 und der Listenlänge-1 (da es bei 0 beginnt)
	std::uniform_int_distribution<int> dist(0,int(p_pWege.size()-1));

	//man definiere einen Weg der später zurückgegeben wird, zunächst auf front() gesetzt
	std::shared_ptr<Weg> pZufälligerWeg=p_pWege.front();
	//do-while-Schleife zu verhindern, dass der zufällige Weg der Rückweg ist
	do
	{
	//man definiert eine zufällige Position
	int iPositionZufälligerWeg = dist(device);
	//man definiere einen Iterator der auf den Anfang der Liste Zeigt also worauf pZufälligerWeg initialisiert wurde
	auto itL = p_pWege.begin();
	//man iteriert durch, bis man an der Position vom zufälligen Weg landet
	for(int i = 0; i < iPositionZufälligerWeg; ++i)
	{
		++itL;
	}

	//der Iterator wird dereferenziert und in der Variable für den zufälligen Weg gespeichert
	pZufälligerWeg=*itL;

	}while(pZufälligerWeg == Hinweg.getRueckweg()); //überprüft, ob RÜckweg


	//rückgabe vom "gelosten" Weg
	return pZufälligerWeg;


}

double Kreuzung::getTankstelle() const
{
	return p_dTankstelle;
}




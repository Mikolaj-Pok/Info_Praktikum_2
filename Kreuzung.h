/*
 * Kreuzung.h
 *
 *  Created on: 28.11.2025
 *      Author: test
 */

#ifndef KREUZUNG_H_
#define KREUZUNG_H_

#include "Simulationsobjekt.h"
#include <list>
#include <memory>
#include "Tempolimit.h"
#include <random>

class Weg;
class Fahrzeug;

class Kreuzung: public Simulationsobjekt
{
public:
	Kreuzung();
	virtual ~Kreuzung();
	Kreuzung(std::string sName, double dTankstelle=0.0); //default 0Liter
	//static definiert eine allgemeine Funktion der Klasse
	static void vVerbinde(std::string sNameHin, std::string sNameRueck, double dLaenge,
			std::shared_ptr<Kreuzung> pStartKreuzung, std::shared_ptr<Kreuzung> pZielKreuzung,
			Tempolimit limit = Tempolimit::Autobahn, bool bUeberholverbot=true);
	void vTanken(Fahrzeug& fahrzeug);
	void vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit=0.0);
	void vSimulieren();
	std::shared_ptr<Weg> pZufaelligerWeg(Weg& Hinweg);
	double getTankstelle() const;

private:
	//speichert das Volumen an Benzin, das an einer Tankstelle zur Verfügung steht
	double p_dTankstelle = 0.0;
	//speichert alle von ihr wegführenden(!) Wege
	std::list<std::shared_ptr<Weg>> p_pWege;



};

#endif /* KREUZUNG_H_ */

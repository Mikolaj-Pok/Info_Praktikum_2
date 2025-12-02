/*
 * PKW.h
 *
 *  Created on: 06.11.2025
 *      Author: test
 */

#ifndef PKW_H_
#define PKW_H_

#include "Fahrzeug.h"
#include <limits>

class PKW: public Fahrzeug
{
public:
	PKW();
	//Konstruktor mit Standardparametern und zusätzlichen PKW-spezifischen Parametern
	PKW(std::string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen=55);
	virtual ~PKW();
	//überschreibt die virtuelle Funktion von Fahrzeug
	double dTanken(double dMenge=std::numeric_limits<double>::infinity()) override;
	void vSimulieren() override;
	//void vAusgeben() const override;
	void vAusgeben(std::ostream& ausgabe) const override;
	PKW& operator=(const PKW& Zuweisungsfahrzeug);
	PKW& operator=(const Fahrzeug& Zuweisungsfahrzeug) override; //einmal mit einmal ohne testen
	double dGeschwindigkeit() const override;
	void vZeichnen(const Weg&) const override;

private:
	double p_dVerbrauch=0; //(Liter/100km)
	double p_dTankvolumen=0; //default 55L
	double p_dTankinhalt=0; //(Liter)


};

#endif /* PKW_H_ */

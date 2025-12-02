/*
 * Fahrzeug.h
 *
 *  Created on: 30.10.2025
 *      Author: test
 */
#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include "Simulationsobjekt.h"
#include "Verhalten.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <memory>

class Weg;


class Fahrzeug : public Simulationsobjekt
{
public:
	//Standardkonstruktor
	Fahrzeug();
	//Konstruktoren mit Parameter
	Fahrzeug(std::string sName);
	Fahrzeug(std::string sName, double dMaxGeschwindigkeit);
	virtual ~Fahrzeug();
	//vAusgeben() ist virtuell, da es je nach Erbe verschiedene Ausgaben geben kann (siehe z.B PKW) /alte Funktion:
	//virtual void vAusgeben() const;
	//virtuelle Ausgabefunktion mit Operatorüberladung von std::cout
	virtual  void vAusgeben(std::ostream& = std::cout)const override;
	//static void, da der Kopf für alle Objekte Gleich ist
	static void vKopf();
	virtual void vSimulieren() override;
	//virtual da je nach Fahrzeug das Tankverhalten unterschiedlich ist (z.B Auto mit Tank und Fahrrad ohne)
	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());
	//virtuelle Geschwindigkeit -> je nach Fahrzeug anders definiert (z.B. v_PKW=max, v_Fahrad<max); const vermeidet Überschreibungen
	virtual double dGeschwindigkeit() const;
	//Überladung des Vergleich-Operators im Bezug auf die Gesamtstrecke
	bool operator<(const Fahrzeug &Vergleichsfahrzeug);
	//virtuelle Überladung des '='-Operators
	virtual Fahrzeug& operator=(const Fahrzeug &Zuweisungsfahrzeug);
	void vNeueStrecke(Weg& weg);
	void vNeueStrecke(Weg& weg, double dStartzeit);
	double getAbschnitt() const;
	//virtuelle Zeichenfunktion mit konstanter Referenz auf einen Weg auf dem gezeichnet werden soll
	virtual void vZeichnen(const Weg&) const;



//protected, damit die abgeleiteten Klassen Zugriff darauf haben
protected:

	//MaxGeschwindigkeit in km/h
	double p_dMaxGeschwindigkeit=0;
	//gesamt zurückgelegte Strecke
	double p_dGesamtStrecke=0;
	//gesamte Zeit
	double p_dGesamtZeit=0;
	//unique_ptr, da das Verhalten eindeutig bestimmt wird + Verhalten wird gelöscht, wenn Fzg gelöscht wird
	std::unique_ptr<Verhalten> p_pVerhalten = nullptr;
	//speichert die auf dem akutellen Weg zurückgelegte Strecke
	double p_dAbschnittStrecke=0;



};




#endif /* FAHRZEUG_H_ */


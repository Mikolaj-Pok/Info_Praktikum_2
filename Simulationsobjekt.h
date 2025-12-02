/*
 * Simulationsobjekt.h
 *
 *  Created on: 13.11.2025
 *      Author: test
 */

#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_
#include "iostream"
#include "string"
#include <iomanip>
#include <limits>

extern double GlobaleZeit;



class Simulationsobjekt
{
public:
	Simulationsobjekt();
	virtual ~Simulationsobjekt();
	Simulationsobjekt(std::string sName);
	/*Verbot eines Copy Konstruktors, da sonst eindeutige Konstanten (p_iID) kopiert werden
	und es zu Slicing kommen kann (Parameter gehen verloren beim Kopieren)*/
	Simulationsobjekt(const Simulationsobjekt&) = delete;
	//Die Simulations-Funktion ist rein virtuell, da ein Simulationsobjekt eine Abstrakte Klasse ist
	//und sich per se nicht simulieren lässt, also muss es immer überschrieben werden.
	//Eine rein virtuelle Funktion benötigt zudem keine Implementierung in der .cpp-Datei
	virtual void vSimulieren()=0;
	virtual void vAusgeben(std::ostream& = std::cout) const;
	virtual bool operator==(const Simulationsobjekt& Vergleichsobjekt) const;
	std::string getName() const;


protected:
	// das "p_" beschreibt Instanzvariablen der Klasse
	std::string p_sName="";
	//Zuletzt gemessene Zeit
	double p_dZeit=0;

private:
	//Statische Variable für alle Objekte der Klasse (statische Variablen sind im Grunde Globalvariablen für Klassen) ("inline", da die Definitio und Deklaration in der Header-Datei geschieht)
	static inline int p_iMaxID=0;
	//die neue, initialisierte  ID ist um eins höher als die Maximale ID, die maximale ID muss auch entsprechend um eins erhöht werden
	const int p_iID=p_iMaxID++;
};

/*Der operator<< muss als freie Funktion (außerhalb der Klasse) definiert werden, damit std::cout auf der linken Seite
stehen kann (in der Klasse wäre es sonst rechts), und ruft dann die (dafür angepasste) virtuelle vAusgeben-Methode auf,
um polymorph die richtige Ausgabe zu erzeugen.*/
std::ostream& operator<<(std::ostream& ausgabe, const Simulationsobjekt& simulationsobjekt);

#endif /* SIMULATIONSOBJEKT_H_ */

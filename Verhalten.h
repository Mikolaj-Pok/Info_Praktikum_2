/*
 * Verhalten.h
 *
 *  Created on: 17.11.2025
 *      Author: test
 */

#ifndef VERHALTEN_H_
#define VERHALTEN_H_

#include <iostream>

//es wird nicht geerbt, sondern nur die Referenz auf einen Weg wird gebraucht
//Außerdem soll eine zirkuläre abhängigkeit vermieden werden
class Weg;
class Fahrzeug;

class Verhalten
{
public:
	//keine uninitialisierten Konstruktoren
	Verhalten()=delete;
	//Kopieren verboten
	Verhalten(const Verhalten&) = delete;
	virtual ~Verhalten();
	//Konstruktor mit Referenz auf einen Weg als Parameter
	Verhalten(Weg& weg);
	//rein virtuelle Funktion, die in "Fahren" implementiert und überschrieben wird
	virtual double dStrecke(Fahrzeug&, double)=0;
	Weg& getWeg() const;

protected:
	//Referenz auf einen Weg als Parameter
	Weg& p_pWeg;
};

#endif /* VERHALTEN_H_ */

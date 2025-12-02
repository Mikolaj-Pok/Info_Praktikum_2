/*
 * Fahrausnahme.h
 *
 *  Created on: 18.11.2025
 *      Author: test
 */

#ifndef FAHRAUSNAHME_H_
#define FAHRAUSNAHME_H_

#include <exception>
#include <iostream>


class Fahrzeug;
class Weg;
extern double dGlobaleZeit;

//Das Erben von der Exception STL ermöglicht polymorphe Fehlerbehandlung, womit hier gearbeitet wird
class Fahrausnahme : public std::exception
{
public:
	//Standardkonstruktor existiert nicht
	Fahrausnahme()=delete;
	Fahrausnahme(Fahrzeug& fahrzeug, Weg& weg);
	virtual ~Fahrausnahme();
	virtual void vBearbeiten() = 0; //rein virtuelle Funktion


protected:
	//speichern den Weg und das Fahrzeug, bei denen die Ausnahme aufgetreten ist
	Fahrzeug& p_pFahrzeug;
	Weg& p_pWeg;
};

#endif /* FAHRAUSNAHME_H_ */

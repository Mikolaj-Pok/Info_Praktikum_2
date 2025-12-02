/*
 * Losfahren.h
 *
 *  Created on: 18.11.2025
 *      Author: test
 */

#ifndef LOSFAHREN_H_
#define LOSFAHREN_H_

#include "Fahrausnahme.h"

class Losfahren: public Fahrausnahme
{
public:
	//Standardkonstruktor existiert nicht!
	Losfahren()=delete;
	Losfahren(Fahrzeug& fahrzeug, Weg& weg);
	virtual ~Losfahren();
	void vBearbeiten() override;
};

#endif /* LOSFAHREN_H_ */

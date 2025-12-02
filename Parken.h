/*
 * Parken.h
 *
 *  Created on: 18.11.2025
 *      Author: test
 */

#ifndef PARKEN_H_
#define PARKEN_H_

#include "Verhalten.h"

class Parken: public Verhalten
{
public:
	Parken()=delete;
	Parken(Weg& weg, double Startzeitpunkt);
	virtual ~Parken();
	double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;

private:
	//Zeitpunkt, wo das parkende Fahrzeug anfängt loszufahren
	const double p_dStart=0.0;
};

#endif /* PARKEN_H_ */

/*
 * Fahren.h
 *
 *  Created on: 18.11.2025
 *      Author: test
 */

#ifndef FAHREN_H_
#define FAHREN_H_

#include "Verhalten.h"

class Fahren: public Verhalten
{
public:

	Fahren()=delete;
	Fahren(Weg& weg);
	virtual ~Fahren();
	double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
};

#endif /* FAHREN_H_ */

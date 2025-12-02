/*
 * Streckenende.h
 *
 *  Created on: 18.11.2025
 *      Author: test
 */

#ifndef STRECKENENDE_H_
#define STRECKENENDE_H_

#include "Fahrausnahme.h"

class Streckenende: public Fahrausnahme
{
public:
	Streckenende() = delete;
	Streckenende(Fahrzeug& fahrzeug, Weg& weg);
	virtual ~Streckenende();
	void vBearbeiten() override;
};

#endif /* STRECKENENDE_H_ */

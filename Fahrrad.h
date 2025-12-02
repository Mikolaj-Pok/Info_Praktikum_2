/*
 * Fahrrad.h
 *
 *  Created on: 06.11.2025
 *      Author: test
 */

#ifndef FAHRRAD_H_
#define FAHRRAD_H_

#include "Fahrzeug.h"

class Fahrrad: public Fahrzeug
{
public:
	Fahrrad();
	virtual ~Fahrrad();
	Fahrrad(std::string sName, double dGeschwindigkeit);
	double dGeschwindigkeit() const override;
	//void vAusgeben() const override;
	void vAusgeben(std::ostream& ausgabe) const override;
	void vZeichnen(const Weg&) const override;


//keine private Member
};

#endif /* FAHRRAD_H_ */

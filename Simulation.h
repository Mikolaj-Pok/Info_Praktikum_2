/*
 * Simulation.h
 *
 *  Created on: 02.12.2025
 *      Author: test
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <iostream>
#include <fstream>
#include <memory>

class Simulation
{
public:
	Simulation();
	virtual ~Simulation();
	void vEinlesen(std::istream& eingabe = std::cin);
	void vSimulieren();




};

#endif /* SIMULATION_H_ */

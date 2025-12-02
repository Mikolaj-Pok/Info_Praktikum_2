/*
 * Tempolimit.h
 *
 *  Created on: 16.11.2025
 *      Author: test
 */

#ifndef TEMPOLIMIT_H_
#define TEMPOLIMIT_H_

#include <limits>

//enum für Übersichtlichkeit und Typensicherheit. Zugriff nur über Scope!
enum class Tempolimit

{
	Innerorts = 50,
	Landstrasse = 100,
	Autobahn = std::numeric_limits<int>::max()
};



#endif /* TEMPOLIMIT_H_ */

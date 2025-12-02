/*
 * Weg.h
 *
 *  Created on: 13.11.2025
 *      Author: test
 */

#ifndef WEG_H_
#define WEG_H_

#include <list>
#include "Simulationsobjekt.h"
#include "Fahrzeug.h"
#include <memory>
#include "Tempolimit.h"
#include "vertagt_liste.h"

class Fahrzeug;
class Kreuzung;

class Weg: public Simulationsobjekt
{
public:
	Weg(std::string sName, double dLaenge, Tempolimit eTempolimit = Tempolimit::Autobahn,
			bool bUeberholverbot = true, std::shared_ptr<Kreuzung> pZielkreuzung = nullptr);
	virtual ~Weg();
	double getTempolimit() const; //get...-Funktionen immer const damit sie nichts verändern
	void vSimulieren() override;
	void vAusgeben(std::ostream& = std::cout) const override;
	static void vKopf();
	double getLaenge() const;
	void vAnnahme(std::unique_ptr<Fahrzeug> Fzg); //fahrendes Fahrzeug
	void vAnnahme(std::unique_ptr<Fahrzeug> Fzg, double dStartzeit); //parkendes Fahrzeug
	std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug&);
	double getSchranke() const;
	bool getUeberholverbot() const;
	void setSchranke(double dSchranke);
	std::shared_ptr<Weg> getRueckweg() const;
	std::shared_ptr<Kreuzung> getZielkreuzung() const;
	void setRueckweg(std::shared_ptr<Weg> pRueckweg);


protected:
	//beschreibt die Länge des Weges
	double p_dLaenge=0.0;
	//Tempolimit vom Weg
	Tempolimit p_eTempolimit=Tempolimit::Autobahn;

	//Liste von Fahrzeugen, welche sich aktuell auf dem Weg befinden (in C++ STL ist list eine doppelt verkettete Liste!)
	//std::list<std::unique_ptr<Fahrzeug>> p_pFahrzeug; -> ersetzt durch VListe

	//Liste von Fahrzeugen, welche sich aktuell auf dem Weg befinden
	vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeug;
	//Boolean, der angibt ob auf dem Weg Überholverbot gilt oder nicht (true=Überholverbot / false= kein Überholverbot)
	bool p_bUeberholverbot=true;
	//virtuelle Schranke
	double p_dSchranke=0.0;

	//speichert den Rückweg
	std::weak_ptr<Weg> p_pRueckweg;
	//speichert die Zielkreuzung, nur über Initialisierungsliste gesetzt
	const std::weak_ptr<Kreuzung> p_pZielkreuzung;




};

#endif /* WEG_H_ */

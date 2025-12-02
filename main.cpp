#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Simulationsobjekt.h"
#include "Weg.h"
#include "SimuClient.h"
#include "vertagt_liste.h"
#include "Kreuzung.h"

#include <memory>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <random>
#include <iostream>
using namespace std;


extern double dGlobaleZeit;
double dZeitschritt=0.1;
//kleiner Epsilon-Wert um doubles miteinander vergleichen zu können
double dEpsilon=0.001;



void vAufgabe_1()
{

	//statisch mit Deklaration
	static Fahrzeug Fahrzeug1;
	//dynamisch mit new
	Fahrzeug*Fahrzeug2=new Fahrzeug("Fahrzeug2", -9.8);
	Fahrzeug2->vKopf();
	Fahrzeug2->vAusgeben();
	std::cout<<std::endl;
	//Löschen von Pointer
	delete Fahrzeug2;
	//zwei unique Pointer Fahrzeuge
	std::unique_ptr <Fahrzeug> Fahrzeug3 = std::make_unique<Fahrzeug>("Fahrzeug3");
	std::unique_ptr <Fahrzeug> Fahrzeug4 = std::make_unique<Fahrzeug>("Fahrzeug4");

	//zwei shared Pointer Fahrzeuge
	std::shared_ptr <Fahrzeug> Fahrzeug5 = std::make_shared<Fahrzeug>("Fahrzeug5");
	std::shared_ptr <Fahrzeug> Fahrzeug6 = std::make_shared<Fahrzeug>("Fahrzeug6");

	std::cout<<"Die Anzahl der Referenzen vom shared Pointer 5 VOR der Zuweisung:"<< Fahrzeug5.use_count() << std::endl;
	std::cout<<"Die Anzahl der Referenzen vom shared Pointer 6 VOR der Zuweisung:"<< Fahrzeug6.use_count() << std::endl;

	//weiteres shared Pointer Fahrzeug, dem eins bereits erstelltes Fahrzeug zugewiesen wird
	std::shared_ptr <Fahrzeug> Fahrzeug7 = Fahrzeug5;
	std::shared_ptr <Fahrzeug> Fahrzeug8 = Fahrzeug6;


	//use_cout() gibt es nur für shared_ptr
	std::cout<<"Die Anzahl der Referenzen vom shared Pointer 5 NACH der Zuweisung:"<< Fahrzeug5.use_count() << std::endl;
	std::cout<<"Die Anzahl der Referenzen vom shared Pointer 6 NACH der Zuweisung:"<< Fahrzeug6.use_count() << std::endl;

	//Vektor wo die erzeugten unique Pointer Fahrzeuge gespeichert werden
	std::vector<std::unique_ptr<Fahrzeug>> v_uFahrzeug;
	//move, da sich unique Pointer nicht kopieren lassen
	v_uFahrzeug.push_back(std::move(Fahrzeug3));
	v_uFahrzeug.push_back(std::move(Fahrzeug4));

	//da shared Pointer mehr als einen Besitzer haben können, können sie kopiert
	//und per call by value ohne move() übergeben werden oder halt mit call by reference
	//mit move()
	std::vector<std::shared_ptr<Fahrzeug>> v_sFahrzeug;
	v_sFahrzeug.push_back(move(Fahrzeug5));
	v_sFahrzeug.push_back(Fahrzeug6);

	std::cout<<"Die Anzahl der Referenzen vom shared Pointer 5 nach Hinzufügen in den Vektor mit move():"<< Fahrzeug5.use_count() << std::endl;
	std::cout<<"Die Anzahl der Referenzen vom shared Pointer 6 nach Hinzufügen in den Vektor ohne move():"<< Fahrzeug6.use_count() << std::endl;

	//Vektorinhalt löschen
	v_uFahrzeug.clear();
	v_sFahrzeug.clear();

}




void vAufgabe_1a()
	{
	std::vector <std::unique_ptr<Fahrzeug>> v_uFahrzeug;
	std::string sName;
	double dMaxGeschwindigkeit;

	//Erzeugt drei Fahrzeuge mit angegebenen Parametern und speichert sie in einem Vektor
	for (int i = 0 ; i<3 ; i++)
		{
		std::cout<<"Gebe Name und Maximalgeschwindigkeit für Fahrzeug Nr."<< i << " ein."<<std::endl;
		std::cin>>sName>>dMaxGeschwindigkeit;
		v_uFahrzeug.push_back(std::make_unique<Fahrzeug>(sName,dMaxGeschwindigkeit));
		}

	for(dGlobaleZeit=0.0; dGlobaleZeit<=5.0; dGlobaleZeit+=dZeitschritt)
		{
			//gibt Globale Zeit aus und den Kopf der Tabelle
			std::cout<<"Globale Zeit: "<< dGlobaleZeit << std::endl;
			Fahrzeug::vKopf();

			for(int i = 0; i<3 ; i++)
			{
				//Simuliert Fahrzeuge 1 bis 3 für einen Zeitschritt und gibt die Daten aus
				v_uFahrzeug[i]->vSimulieren();
				v_uFahrzeug[i]->vAusgeben();
				std::cout<<std::endl;
			}
		}

	}



void vAufgabe_2()
{
	std::vector<unique_ptr<Fahrzeug>> v_uFahrzeug;
	std::string sName;
	double dGeschwindigkeit;
	double dVerbrauch;
	double dTankvolumen;
	int Auswahl;
	bool Menu=true;

	while (Menu)

	{

	std::cout<<"Was möchten Sie machen?"<<std::endl;
	std::cout<<"PKW erzeugen (1)"<<std::endl;
	std::cout<<"Fahrrad erzeugen (2)"<<std::endl;
	std::cout<<"Automatisch erzeugen (3)"<<std::endl;

	std::cin>>Auswahl;


	switch (Auswahl)
	{
	case 1:
		std::cout<<"Geben Sie Name des PKWs ein:"<<std::endl;
		std::cin>>sName;
		std::cout<<"Geben Sie MaxGeschwindigkeit des PKWs ein:"<<std::endl;
		std::cin>>dGeschwindigkeit;

		if (dGeschwindigkeit<=0)
			{
			std::cout<<"MaxGeschwindigkeit ungültig, es wird auf 100km/h gesetzt"<<std::endl;
			dGeschwindigkeit=100;
			}

		std::cout<<"Verbrauch des PKWs ein:"<<std::endl;
		std::cin>>dVerbrauch;

		if (dVerbrauch<=0)
			{
			std::cout<<"Verbrauch ungültig, es wird auf 8L gesetzt"<<std::endl;
			dVerbrauch=8;
			}

		std::cout<<"Geben Sie Tankvolumen des PKWs ein:"<<std::endl;
		std::cin>>dTankvolumen;

		if (dTankvolumen<=0)

		{
		std::cout<<"Tankvolumen ungültig, es wird auf 55L gesetzt"<<std::endl;
		dTankvolumen=55;
		}

		v_uFahrzeug.push_back(std::make_unique<PKW>(sName,dGeschwindigkeit,dVerbrauch,dTankvolumen));

		std::cout<<"Noch ein Fahrzeug? ja (1) / nein (0)"<<std::endl;

		std::cin>>Menu;

	break;

	case 2:

			std::cout<<"Geben Sie Namen des Fahrrads ein:"<<std::endl;
			std::cin>>sName;
			std::cout<<"Geben Sie Geschwindigkeit des Fahrrads ein (mind. 12 km/h):"<<std::endl;
			std::cin>>dGeschwindigkeit;

			if (dGeschwindigkeit<12)
			{
			std::cout<<"Geschwindigkeit ungültig, es wird auf 20km/h gesetzt"<<std::endl;
			dGeschwindigkeit=20;
			}
			v_uFahrzeug.push_back(std::make_unique<Fahrrad>(sName,dGeschwindigkeit));

			std::cout<<"Noch ein Fahrzeug? ja (1) / nein (0)"<<std::endl;
			std::cin>>Menu;

	break;

	case 3:

		std::cout<<"Es werden zwei PKWs und zwei Fahrräder automatisch erstellt"<<std::endl;
		v_uFahrzeug.push_back(std::make_unique<PKW>("VW Sharan",100,6,80));
		v_uFahrzeug.push_back(std::make_unique<PKW>("Trucker Joe",80,25,300));
		v_uFahrzeug.push_back(std::make_unique<Fahrrad>("BMX Tobi",25));
		v_uFahrzeug.push_back(std::make_unique<Fahrrad>("Rennrad Susi",35));


		Menu=false; //Menu wird verlassen

	break;
	}

	}

	std::cout<<"Simulation beginnt!"<<std::endl;
	for (dGlobaleZeit = 0; dGlobaleZeit-dEpsilon <= 5; dGlobaleZeit += 0.3)
	{
		std::cout << std::endl << "Globalezeit = " << dGlobaleZeit << std::endl;
		Fahrzeug::vKopf();
		int groesseVektor=v_uFahrzeug.size();
		for (int i = 0; i < groesseVektor; i++)
		{
			v_uFahrzeug[i]->vSimulieren();
			if (fabs(dGlobaleZeit - 3.0) < dEpsilon)
			{
				v_uFahrzeug[i]->dTanken();
			}
			v_uFahrzeug[i]->vAusgeben();
			std::cout << endl;
		}
	}
}



void vAufgabe_3()
{
	std::cout<<"Es werden zwei PKWs und zwei Fahrräder automatisch erstellt"<<std::endl;
	unique_ptr <PKW> pkw1 = std::make_unique<PKW>("PKW 1",100,6,80);
	unique_ptr <PKW> pkw2 = std::make_unique<PKW>("PKW 2",80,8,50);
	unique_ptr <Fahrrad> fahrrad1 = std::make_unique<Fahrrad>("RAD 1",25) ;
	unique_ptr <Fahrrad> fahrrad2 = std::make_unique<Fahrrad>("RAD 2",35);

	std::cout<<"Ausgabe der erzeugten Fahrzeuge:"<<std::endl;
	Fahrzeug::vKopf();
	std::cout<< *pkw1 <<std::endl<<*pkw2<<std::endl<<*fahrrad1<<std::endl<<*fahrrad2<<std::endl;

	PKW pkw3("PKW 3", 150, 4);
	*pkw1 = pkw3;
	Fahrrad fahrrad3("RAD 3", 20);
	*fahrrad1 = fahrrad3;

	std::cout<<"Ausgabe der erzeugten Fahrzeuge nach dem Kopieren:"<<std::endl;
	Fahrzeug::vKopf();
	std::cout<< *pkw1 <<std::endl<<*pkw2<<std::endl<<*fahrrad1<<std::endl<<*fahrrad2<<std::endl;

	std::cout<<"Simulation startet:"<<std::endl;

	for (dGlobaleZeit = 0; dGlobaleZeit - dEpsilon <= 5; dGlobaleZeit += 0.3)
		{
			std::cout << std::endl << "Globalezeit = " << dGlobaleZeit << std::endl;
			Fahrzeug::vKopf();
			//Simulation
			pkw1->vSimulieren();
			pkw2->vSimulieren();
			fahrrad1->vSimulieren();
			fahrrad2->vSimulieren();
			//Ausgabe
			std::cout << *pkw1 << std::endl << *pkw2 << std::endl << *fahrrad1 << std::endl<< *fahrrad2<< std::endl << std::endl;
			//Vergleich der Gesamtstrecke
			std::cout << std::endl << "PKW_1 < PKW_2: " << (*pkw1 < *pkw2) << std::endl;
			std::cout << std::endl << "FAHRRAD_1< PKW_2: " << (*fahrrad1 < *pkw2 ) << std::endl;
			std::cout << std::endl << "FAHRRAD_1< FAHRRAD_2: " << (*fahrrad1 < *fahrrad2 ) << std::endl;

		}

}



void vAufgabe_Probe()
{
    Fahrzeug* pF1 = new PKW("Audi", 150, 8);
    dGlobaleZeit = 0.0;
    Fahrzeug::vKopf();
    dGlobaleZeit = 3.0;
    cout << endl << "Globalezeit = " << dGlobaleZeit << endl;
    pF1->vSimulieren();
    std::cout << *pF1 << endl;
    delete pF1;
    char c;
    std::cin >> c;
}


/*
//Vom E-Test
void vAufgabe_AB1() {

    int l = 0; // Laufindex für gezielte AUsgabe
    vector<int> ausgabe{13};
    double dTakt = 0.4;

    std::vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
    vecFahrzeuge.push_back(make_unique <PKW>("Audi", 217, 10.7));
    vecFahrzeuge.push_back(make_unique <Fahrrad>("BMX", 21.4));
    for (dGlobaleZeit = 0; dGlobaleZeit < 6; dGlobaleZeit += dTakt)
    {
        auto itL = find(ausgabe.begin(), ausgabe.end(), l);
        if (itL != ausgabe.end()) {
            std::cout << std::endl << l <<  " Globalezeit = " << dGlobaleZeit << std::endl;
            Fahrzeug::vKopf();
        }

        for (int i = 0; i < vecFahrzeuge.size(); i++)
        {
            vecFahrzeuge[i]->vSimulieren();
            if (fabs(dGlobaleZeit - 3.0) < dTakt/2)
            {
                vecFahrzeuge[i]->dTanken();
            }
            if (itL != ausgabe.end()) {
                std::cout << *vecFahrzeuge[i] << endl;
            }
        }
        l++;
    }
    char c;
    std::cin >> c;
}
*/

void vAufgabe_4()
{
	Weg meinWeg("meinWeg",100.0, Tempolimit::Innerorts,true,nullptr);
	Weg::vKopf();
	std::cout<<meinWeg<<std::endl;
}


void vAufgabe_5()
{
	//Definiere Weg
	Weg meinWeg("meinWeg",200.0, Tempolimit::Autobahn,false,nullptr);

	//Definiere drei Fahrzeuge
	std::unique_ptr<PKW> PKW1 = std::make_unique<PKW>("BMW", 240.0, 7.0);
	std::unique_ptr<Fahrrad> RAD1 = std::make_unique<Fahrrad>("BMX", 25);

	//packe Fahrzeuge auf den Weg
	meinWeg.vAnnahme(move(PKW1));
	meinWeg.vAnnahme(std::make_unique<PKW>("parkender Audi", 150.0, 8.0),2.0); //Parkt bis die Startzeit (=2.0) erreicht wurde
	meinWeg.vAnnahme(move(RAD1));

	//Simulieren
	Weg::vKopf();
	std::cout<<meinWeg<<std::endl;

	for(dGlobaleZeit=0.0; dGlobaleZeit<=5.0; dGlobaleZeit+=dZeitschritt)
		{
		meinWeg.vSimulieren();
		std::cout<<meinWeg<<std::endl;
		}

}

//erste Version der Aufgabe 6 noch ohne Grafikausgabe
void vAufgabe_6v0()
{
	Weg WOhneT("WOhneT",199.0,Tempolimit::Autobahn,true,nullptr);
	Weg WMitT("WMitT",99.0,Tempolimit::Innerorts,true,nullptr);

	WOhneT.vAnnahme(std::make_unique<PKW>("parkender Audi", 100.0, 8.0),3.0);
	WOhneT.vAnnahme(std::make_unique<PKW>("BMW", 200.0, 9.0));
	WOhneT.vAnnahme(std::make_unique<Fahrrad>("BMX", 25));

	WMitT.vAnnahme(std::make_unique<PKW>("parkender Audi", 100.0, 8.0),3.0);
	WMitT.vAnnahme(std::make_unique<PKW>("BMW", 200.0, 9.0));
	WMitT.vAnnahme(std::make_unique<Fahrrad>("BMX", 25));

	Weg::vKopf();
	std::cout<<WOhneT<<std::endl;
	std::cout<<WMitT<<std::endl;
	for(dGlobaleZeit=0.0; dGlobaleZeit<=5.0; dGlobaleZeit+=dZeitschritt)
		{
			WOhneT.vSimulieren();
			WMitT.vSimulieren();
			//std::cout<<"Globale Zeit: "<<dGlobaleZeit<<" Std"<<std::endl<<std::endl;

			//Funktioniert nur bei 0.25=2^-2, da es sich gut Binär darstellen lässt. 0.3 nicht!
			if (dGlobaleZeit==3.0)
			{
				std::cout<<"Fahrzeug fährt los!"<<std::endl<<std::endl;
			}

			//Besser mit fabs(), da kleine Abweichungen (z.B. 2.9999994) ausgeglichen werden
			if (std::fabs(dGlobaleZeit-3)<dEpsilon)
			{
				std::cout<<"Fahrzeug fährt los!"<<std::endl<<std::endl;
			}

			std::cout<<std::endl<<std::endl;

		}
}



//Aufgabe 6 überarbeitet mit der Grafikausgabe
void vAufgabe_6()
{
	Weg wegHin("Hinweg",100.0,Tempolimit::Innerorts,true,nullptr);
	Weg wegRueck("Rueckweg",100.0,Tempolimit::Autobahn,true,nullptr);

	wegRueck.vAnnahme(std::make_unique<PKW>("parkender_Audi", 180.0, 8.0),3.0);
	wegHin.vAnnahme(std::make_unique<PKW>("parkender_BMW", 150.0, 12.0),1.5);
	wegHin.vAnnahme(std::make_unique<Fahrrad>("BMX", 30.0));

	bInitialisiereGrafik(800,500);
	int iKoordinaten[] = {700,250,100,250};
	bZeichneStrasse(wegHin.getName(),wegRueck.getName(),500,2,iKoordinaten);


	for(dGlobaleZeit=0.0; dGlobaleZeit<=6.0; dGlobaleZeit+=dZeitschritt)
		{

			wegHin.vSimulieren();
			wegRueck.vSimulieren();

			vSetzeZeit(dGlobaleZeit);
			std::cout << "dGlobaleZeit: " << dGlobaleZeit<<std::endl;
			Weg::vKopf();
			std::cout<<wegHin<<wegRueck;
			std::cout<<std::endl<<std::endl;
			vSleep(1000);

		}

	vBeendeGrafik();

	//Nach dem Implementieren von Weg::pAbgabe kommt es zum Programmabsturz, vermutlich dadurch, weil
	//durch pAbgabe man Fahrzeuge aus der Liste umsetzt und der Iterator nicht mehr definiert ist. Oder
	//es liegt daran dass Simulationsschritte fehlen, da durch das Umsetzten Elemente nach hinten
	//oder vorne verschoben wurden -> Lösung mit Templateklasse VListe!!
}


void vListeAusgeben(const vertagt::VListe<int>& iListe)
{
	//auto: Der Compiler ermittelt den Datentyp von 'p' automatisch
	//& (Referenz):Wir greifen auf das Original-Element in der Liste zu.
	//p: Ist der Name der Variable für das aktuelle Element im Schleifendurchlauf.
	for (auto& p : iListe)
	{
		std::cout<<"["<< p <<"] ";
	}
	std::cout<<std::endl;
}

void vAufgabe_6a()
{
	//Erzeuge zufällige Zahl zwischen 1 & 10
	//seed = 0 für die Reproduzierbarkeit
	const int seed = 0;
	static std::mt19937 device (seed);
	std::uniform_int_distribution<int> dist(1,10);

	//erzeugt Liste mit int-Werten
	vertagt::VListe<int> iListe;

	//befüllt die Liste mit zufälligen Werten
	for (int i=0; i<10; ++i)
	{
		iListe.push_back(dist(device));
	}

	std::cout<<"Liste vor der Aktualisierung: "<<std::endl;
	vListeAusgeben(iListe);
	std::cout<<"Liste nach der Aktualisierung: "<<std::endl;
	iListe.vAktualisieren();
	vListeAusgeben(iListe);


	for (auto it = iListe.begin(); it != iListe.end(); ++it)
	{
		//Falls der dereferenzierte Iterator größer als 5 ist...
		if(*it>5)
		{
			//entferne den Wert, auf den der Iterator zeigt
			iListe.erase(it);
		}
	}

	std::cout<<"Liste nachdem Werte >5 gelöscht wurden (unaktualisiert): "<<std::endl;
	vListeAusgeben(iListe);
	std::cout<<"Liste nach der Aktualisierung: "<<std::endl;
	iListe.vAktualisieren();
	vListeAusgeben(iListe);

	iListe.push_front(12);
	iListe.push_back(34);

	std::cout<<"Liste nachdem 2 Werte hinzugefügt wurden (unaktualisiert): "<<std::endl;
	vListeAusgeben(iListe);
	std::cout<<"Liste nach der Aktualisierung: "<<std::endl;
	iListe.vAktualisieren();
	vListeAusgeben(iListe);


}

void vAufgabe_7()
{
	bInitialisiereGrafik(1000,600);

	//erzeuge vier shared_ptr vom Typ Kreuzung
	std::shared_ptr<Kreuzung> K1 = std::make_shared<Kreuzung>("K1");
	std::shared_ptr<Kreuzung> K2 = std::make_shared<Kreuzung>("K2",1000); // 1000 Liter Tankstellenvolumen
	std::shared_ptr<Kreuzung> K3 = std::make_shared<Kreuzung>("K3");
	std::shared_ptr<Kreuzung> K4 = std::make_shared<Kreuzung>("K4");

	bZeichneKreuzung(680, 40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);

	Kreuzung::vVerbinde("W12","W21",40,K1,K2,Tempolimit::Innerorts,true);
	Kreuzung::vVerbinde("W23a","W32a",115,K2,K3,Tempolimit::Autobahn,false);
	Kreuzung::vVerbinde("W23b","W32b",40,K2,K3,Tempolimit::Innerorts,true);
	Kreuzung::vVerbinde("W24","W42",55,K2,K4,Tempolimit::Innerorts,true);
	Kreuzung::vVerbinde("W34","W43",85,K3,K4,Tempolimit::Autobahn,false);
	Kreuzung::vVerbinde("W44a","W44b",130,K4,K4,Tempolimit::Landstrasse,false);

	int iW12[] = {680,40,680,300};
	int iW23a[] = {680,300,850,300,970,390,970,500,850,570,680,570};
	int iW23b[] = {680,300,680,570};
	int iW24[] = {680,300,320,300};
	int iW34[] = {680,570,500,570,350,510,320,420,320,300};
	int iW44[] = {320,300,320,150,200,60,80,90,70,250,170,300,320,300};

	bZeichneStrasse("W12","W21",40,2,iW12);
	bZeichneStrasse("W23a","W32a",115,6,iW23a);
	bZeichneStrasse("W23b","W32b",40,2,iW23b);
	bZeichneStrasse("W24","W42",55,2,iW24);
	bZeichneStrasse("W34","W43",85,5,iW34);
	bZeichneStrasse("W44a","W44b",130,7,iW44);

	K1->vAnnahme(std::make_unique<PKW>("PKW1",80, 8.0));
	K1->vAnnahme(std::make_unique<PKW>("PKW2",130, 6.0),5.0);
	K1->vAnnahme(std::make_unique<PKW>("PKW3",200, 10.0));
	K1->vAnnahme(std::make_unique<Fahrrad>("RAD1",20));
	K1->vAnnahme(std::make_unique<Fahrrad>("RAD2",35));

	//Simulierschleife
	for(dGlobaleZeit=0.0; dGlobaleZeit<=20.0; dGlobaleZeit+=dZeitschritt)
			{
				//Verschachtelte Simulationsfunktion Kreuzung->Weg->Fahrzeug->PKW/Fahrrad
				K1->vSimulieren();
				K2->vSimulieren();
				K3->vSimulieren();
				K4->vSimulieren();

				vSetzeZeit(dGlobaleZeit);
				vSleep(10);

			}


	vBeendeGrafik();





}

void test()
{
	std::vector<unique_ptr<Fahrzeug>> vFahrzeug;
	vFahrzeug.push_back(std::make_unique<PKW> ("PKW1", 200, 10, 100));
	vFahrzeug.push_back(std::make_unique<Fahrrad> ("RAD1", 25));

	for(dGlobaleZeit=0;dGlobaleZeit<3;dGlobaleZeit+=dZeitschritt)
	{
	vFahrzeug[0]->vSimulieren();
	vFahrzeug[1]->vSimulieren();

	Fahrzeug::vKopf();
	std::cout<<*vFahrzeug[0]<<std::endl<<*vFahrzeug[1];
	}

	vFahrzeug[0]->dTanken(30);

}



int main()

	{

	//vAufgabe_1();

	//vAufgabe_1a();

	//vAufgabe_2();

	//vAufgabe_3();

	//vAufgabe_Probe();

	//vAufgabe_AB1();

	//vAufgabe_4();

	//vAufgabe_5();

	//die erste Version von Aufgabe 6:
	//vAufgabe_6v0();

	//vAufgabe_6();

	//vAufgabe_6a();

	vAufgabe_7();

	//test();


	return 0;
	}

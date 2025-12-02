#pragma once

#include "vertagt_aktion.h"
#include <list>

namespace vertagt
{
	template <class T>
	class VListe
	{
	private:
		//Liste mit den eigentlichen Objekten mit den zu speichernden Elementen vom Templatetyp T
		std::list<T> p_objekte;

		//Liste zum Zwischenspeichern der noch auszuführenden Aktionen
		std::list<std::unique_ptr<VAktion<T>>> p_aktionen;

	public:
		// Typdefinitionen
		using iterator = typename std::list<T>::iterator;
		using const_iterator = typename std::list<T>::const_iterator;

		// Konstruktoren, default da kein Funktionskörper mit {}
		VListe() = default; // Benötigt man einen Standardkonstruktor? JA, Liste nicht abstrakt
		// Destruktor
		~VListe()
		{
			vAktualisieren();
			p_objekte.clear();
		}

		void clear()
		{
			vAktualisieren();
			p_objekte.clear();
		}

		// Lesefunktionen
		const_iterator begin() const
		{
			return p_objekte.begin();
		}
		const_iterator end() const
		{
			return p_objekte.end();
		}
		iterator begin()
		{
			return p_objekte.begin();
		}
		iterator end()
		{
			return p_objekte.end();
		}
		bool empty() const
		{
			return p_objekte.empty();
		}

		// Schreibfunktionen:

		//push_back und push_front speichern Anweisung UND Objekt (eine Art Akte)
		void push_back(T obj)
		{
			// Aktionselement für PushBack auf Liste erzeugen
			p_aktionen.push_back(std::make_unique<VPushBack<T>>(p_objekte,std::move(obj)));
		}

		void push_front(T obj)
		{
			// Aktionselement für PushFront auf Liste erzeugen
			// make_unique erstellt ein neues VPushFront-Objekt auf dem Heap.
			// Parameter 1 (p_objekte): Die Referenz auf die Liste, in die später eingefügt werden soll.
			// Parameter 2 (move(obj)): Das Objekt selbst wird in die Aktion "verschoben" (Besitzwechsel),
			// damit es dort verwahrt ist, bis vAktualisieren() aufgerufen wird.
			p_aktionen.push_back(std::make_unique<VPushFront<T>>(p_objekte,std::move(obj)));
		}

		void erase(iterator it)
		{
			// Aktionselement für PushBack auf Liste erzeugen (hier Iterator statt Objekt!)
			p_aktionen.push_back(std::make_unique<VErase<T>>(p_objekte,it));
		}

		// Änderungen auf Objektliste übertragen
		void vAktualisieren()
		{
			// Änderungen auf Objektliste übertragen
			for (auto& pAktion : p_aktionen)
			{
				// Aktion ausführen
				pAktion->vAusfuehren();

			}
			// Aktionsliste löschen
			p_aktionen.clear();

		}
	};
} // namespace vertagt


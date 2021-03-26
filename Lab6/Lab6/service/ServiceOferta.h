#pragma once

#include "../repo/RepoOferta.h"
#include <string>
#include <functional>
using std::string;

class ServiceOferta {
private:
	RepoOferte repo;
	int id;  // Id asignat automat la aduagare.

public:
	/** Constructor implicit */
	ServiceOferta() noexcept : repo{} {
		id = 0;
	}

	/** Functie de adaugare de service. Adauga un element in registru.
	* @param denumire - denumirea elementului adaugat.
	* @param destinatie - destinatia elementului adaugat.
	* @param tip - tipul elementului adaugat;
	* @param pret - pretul elementului adaugat.
	* @return Arunca eroare cu un mesaj daca elementul nu se poate introduce.
	*/
	// TODO: Nu permite adaugare cu id deja existent.
	void adaugare(string denumire, string destinatie, string tip, int pret);

	/** Functie de stergere din service. Sterge un element din registru.
	* @param id - id-ul elementului de sters
	* @return Arunca o exceptie std::out_of_range daca elementul cu id dat nu este in registru.
	*/
	void stergere(int id_sters);

	/** Functie de modificare din service. Modifica elementul cu id-ul dat.
	* @param id_modificat - id-ul elementului modificat.
	* @param denumire - noua denumire
	* @param destinatie - noua destinatie
	* @param tip - noul tip
	* @param pret - noul pret
	* @return Arunca exceptie daca elementul cu id dat nu se poate gasi in registru.
	*/
	void modificare(int id_modificat, string denumire, string destinatie, string tip, int pret);

	/** Cauta si returneaza o referinta constanta la Oferta cu id dat.
	* @param id_cautat - id-ul ofertei cautate.
	* @return Referinta const la elementul cautat sau arunca eroare daca nu se poate gasi in registru.
	*/
	const Oferta& cautare(int id_cautat) const;

	/** Functie de filtrare pentru pret
	* @param lower - limita inferioara a pretului.
	* @param upper - limita superioara a pretului. 
	* @return Returneaza un vector de OFerte care este un subset al registrului. 
	*/
	const vector<Oferta> filtrare_pret(int lower, int upper) const;

	/** Functie de filtrare pentru destinatie.
	* @param filtru_destinatie - destinatia dorita
	* @ return lista constanta de Oferte, care au aceeasi destinatie cu cea data.
	*/
	const vector<Oferta> filtrare_destinatie(string filtru_destinatie) const;

	/** Functia de sortare pentru service.
	* @param criteriu - functie bool (Oferta& a, Oferta& b) care returneaza true daca elementul a este "mai mic" decat b.
	* @return Lista constanta de Oferta care este sortata
	*/
	const vector<Oferta> sortare(std::function<bool (Oferta& a, Oferta& b)> criteriu) const;  // TODO: sistem de transmitere criteriu.
	/** Ofera un vector cu toate elementele din lista */
	const vector<Oferta> get_all() const;
	
}; 
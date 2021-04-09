#pragma once

#include "../repo/RepoOferta.h"
#include "../Validator/validator.h"
#include <string>
#include <vector>
#include <functional>
#include "../Cos.h"
using std::string;
using std::vector;

class ServiceOferta {
private:
	RepoOferte repo;
	int id;  // Id asignat automat la aduagare.
	Validator valid;
	Cos cos;

public:
	/** Constructor implicit */
	ServiceOferta() noexcept : repo{}, cos{}, valid{&repo} {
		this->id = 0;
	}

	/** Functie de adaugare de service. Adauga un element in registru.
	* @param denumire - denumirea elementului adaugat.
	* @param destinatie - destinatia elementului adaugat.
	* @param tip - tipul elementului adaugat;
	* @param pret - pretul elementului adaugat.
	* @return Arunca eroare cu un mesaj daca elementul nu se poate introduce.
	*/
	void adaugare(const string& denumire, const string& destinatie, const string& tip, const int pret);

	/** Functie de stergere din service. Sterge un element din registru.
	* @param id - id-ul elementului de sters
	* @return Arunca o exceptie std::out_of_range daca elementul cu id dat nu este in registru.
	*/
	void stergere(const int id_sters);

	/** Functie de modificare din service. Modifica elementul cu id-ul dat.
	* @param id_modificat - id-ul elementului modificat.
	* @param denumire - noua denumire
	* @param destinatie - noua destinatie
	* @param tip - noul tip
	* @param pret - noul pret
	* @return Arunca exceptie daca elementul cu id dat nu se poate gasi in registru.
	*/
	void modificare(const int id_modificat, const string& denumire, const string& destinatie, const string& tip, const int pret);

	/** Cauta si returneaza o referinta constanta la Oferta cu id dat.
	* @param id_cautat - id-ul ofertei cautate.
	* @return Referinta const la elementul cautat sau arunca eroare daca nu se poate gasi in registru.
	*/
	const Oferta& cautare(const int id_cautat) const;

	/** Functie de filtrare pentru pret
	* @param lower - limita inferioara a pretului.
	* @param upper - limita superioara a pretului. 
	* @return Returneaza un vector de OFerte care este un subset al registrului. 
	*/
	const vector<Oferta> filtrare_pret(const int lower, const int upper) const;

	/** Functie de filtrare pentru destinatie.
	* @param filtru_destinatie - destinatia dorita
	* @ return lista constanta de Oferte, care au aceeasi destinatie cu cea data.
	*/
	const vector<Oferta> filtrare_destinatie(const string& filtru_destinatie) const;

	/** Functia de sortare pentru service.
	* @param criteriu - functie bool (Oferta& a, Oferta& b) care returneaza true daca elementul a este "mai mic" decat b.
	* @return Lista constanta de Oferta care este sortata
	*/
	const vector<Oferta> sortare(std::function<bool (const Oferta& a, const Oferta& b)> criteriu) const;  // TODO: sistem de transmitere criteriu.
	/** Ofera un vector cu toate elementele din lista */
	const vector<Oferta>& get_all() const noexcept;

	/** Ofera o referinta const la vectorul de elemente */
	const vector<Oferta>& get_ref_all() const noexcept;

	/** Adauga oferta cu denumirea data in cos. 
	* Arunca eroare de Repo daca nu este gasit niciun element.
	*/
	void adauga_cos(const string& denumire);

	/** Sterge oferta cu denumirea data din cos. */
	void sterge_din_cos(const string& denumire);

	/** Goleste cosul de oferte */
	void golire_cos() noexcept;

	/** Returneaza dimensiunea cosului. */
	unsigned dimensiune_cos() const noexcept;

	/** Referinta la vectorul de elemente din cos. */
	const vector<Oferta>& vector_cos() const noexcept;

	/** Creeaza si exporteaza un document html afarent cosului curent de cumparaturi.
	* @param file_name - numele fisierului dorit, fara extensie.
	*/
	void export_html_cos(const string& file_name) const;

	/** Adauga un numar de elemente random in cos.
	* @param numar - int numar elemente.
	*/
	void adauga_random_cos(int numar);
	
}; 

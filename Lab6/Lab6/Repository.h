#pragma once
#include "domain/oferta.h"
#include <vector>

class Repository {
public:

	/** Adauga elementul dat. 
	* @param de_adaugat - referinta la oferta pe care dorim sa o adaugam.
	*/
	virtual void add(const Oferta& de_adaugat) = 0;

	/** Elimina elementul cu id dat.
	* @param id - id-ul elementului pe care dorim sa il stergem.
	*/
	virtual void remove(const int id) = 0;

	/** Updateaza elementul cu id dat. 
	* @param id - id-ul elementului pe care dorim sa il modificam.
	* @param new_oferta - oferta cu care dorim sa inlocuim elementul modificat.
	*/
	virtual void update(const int id, const Oferta& new_oferta) = 0;

	/** Cauta elementul dupa id. Returneaza true daca exista.
	* @param id - id-ul dupa care dorim sa cautam.
	* @return True daca exista o oferta cu id-ul dat.
	*/
	virtual bool search(const int id) const = 0;

	/** Determina daca elemetul cu denumirea data exista in lista. 
	* @param denumire - denumirea dupa care dorim sa cautam.
	* @return True daca exista o oferta cu denumirea data. False atlfel.
	*/ 
	virtual bool search_denumire(const std::string& denumire) const = 0;

	/** Returneaza referinta la elementul cu denumirea data.
	* @param denumire - denumire dupa care dorim sa cautam.
	* @return Referinta la oferta din repo.
	*/
	virtual const Oferta& search_get_denumire(const std::string& denumire) const = 0;

	/** Returneaza referinta la elementul cu id dat.
	* @param id - id-ul elementului dorit.
	* @return referinta la oferta din repo. 
	* Arunca exceptie de Repo daca nu este elementul.
	*/
	virtual const Oferta& search_element(const int id) const = 0;

	/** Returneaza un vector cu copii dupa fiecre element. 
	* @return vector cu copii la toate elementele.
	*/
	virtual std::vector<Oferta> get_all() const = 0;
	
	/** Returneaza o referinta la vectorul de elemente.
	* @return referinta la vectorul de elemente.
	*/
	virtual const std::vector<Oferta>& afisare() const = 0;
	
	/** Elimina toate elementele din repo. */
	virtual void remove_all() = 0;

	/** Returneaza dimensiunea */
	virtual unsigned dim() = 0;

	/** Get the max in dex of this repository. */
	virtual int get_max_index() const = 0;

	virtual ~Repository() = default;
};
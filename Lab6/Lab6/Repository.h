#pragma once
#include "domain/oferta.h"
#include <vector>

class Repository {
public:

	/** Adauga elementul dat. */
	virtual void add(const Oferta& de_adaugat) = 0;

	/** Elimina elementul cu id dat. */
	virtual void remove(const int id) = 0;

	/** Updateaza elementul cu id dat. */
	virtual void update(const int id, const Oferta& new_oferta) = 0;

	/** Cauta elementul dupa id. Returneaza true daca exista. */
	virtual bool search(const int id) const = 0;

	/** Determina daca elemetul cu denumirea data exista in lista. */
	virtual bool search_denumire(const std::string& denumire) const = 0;

	/** Returneaza referinta la elementul cu denumirea data.  */
	virtual const Oferta& search_get_denumire(const std::string& denumire) const = 0;

	/** Returneaza referinta la elementul cu id dat. */
	virtual const Oferta& search_element(const int id) const = 0;

	/** Returneaza un vector cu copii dupa fiecre element. */
	virtual std::vector<Oferta> get_all() const = 0;
	
	/** Returneaza o referinta la vectorul de elemente. */
	virtual const std::vector<Oferta>& afisare() const = 0;
	
	/** Elimina toate elementele din repo. */
	virtual void remove_all() = 0;

	/** Returneaza dimensiunea */
	virtual unsigned dim() = 0;

	virtual ~Repository() = default;
};
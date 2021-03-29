#pragma once

#include <vector>
#include "../domain/oferta.h"
using std::vector;

/** RepoOferte clasa responsabila pentru stocarea si gestionarea ofertelor. */
class RepoOferte {
private:
	vector<Oferta> elems;  // Lista de elemente.
public:
	RepoOferte() noexcept : elems{} {}  // Constructor implicit.

	/** Adauga o oferta in repository.
	* @param de_adaugat - Oferta pe care dorim sa o adaugam.
	*/
	void add(const Oferta& de_adaugat);

	/** Elimina elementul cu id-ul dat. 
	* @param id - id elementului pe care dorim sa il eliminam.
	*/
	void remove(const int id);

	/** Updateaza elementul cu id dat la noua oferta.
	* Elementului din lista ii sunt inlocuite atribuitele cu cele noi.
	* @param id - id-ul elementului cautat
	* @param new_oferta - noua oferta.
	*/
	void update(const int id, const Oferta& new_oferta);

	/** Determina daca elementul cu id dat este in lista.
	* @param id - id-ul elementului cautat.
	* @return true daca elementul exista in lista, false altfel.
	*/
	bool search(const int id) const noexcept;

	/** Returneaza o referinta const la elementul cu id dat
	* arunca o exceptie daca nu exista elementul cu acest id.
	*/
	const Oferta& search_element(const int id) const;

	/** Returneaza un vector de copii ale elementelor. 
	* @return un vector de Oferta care contine copii
	* ale elementelor din repo.
	*/
	vector<Oferta> get_all() const;

	/** Returneaza referinta la vector*/
	const vector<Oferta>& afisare() const noexcept;

	/** Elimina toate elementele din repository. */
	void remove_all() noexcept;

	/** Returneaza numarul de elemente din repo.
	* @return int numarul de elemente 
	*/
	unsigned int dim() noexcept;
};
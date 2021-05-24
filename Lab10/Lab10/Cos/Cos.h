#pragma once

#include <vector>
#include "../observer/observable.h"
#include "../observer/observer.h"
#include "../repo/RepoOferta.h"
using std::vector;

class Cos : public Observable {
private:
	vector<Oferta> elems;

public:

	/** Adauga oferta data in cos.
	* @param of - oferta pe care dorim sa o adaugam.
	* Daca se incearca introducerea a aceleasi oferte de doua ori,
	* nu se intampla nimic.
	* @return true daca s-a efectuat adaugarea.
	*/
	bool adauga(const Oferta& of);

	/** Sterge oferta data din cos.
	* @param of - oferta pe care dorim sa o stergem din cos.
	* Se sterge oferta.
	* @return true daca s-a efectuat stergerea.
	*/
	bool sterge(const Oferta& of);

	/** Goleste cosul de elemente. */
	void golire() noexcept;

	/** Exporta cosul curent ca html.
	* @param fisier - numele fisierului dorit, FARA extensie.
	*/
	void export_html(const string& fisier) const;

	/** Exporta cosul curent ca html.
	* Versiunea cu bootstrap.
	* @param fisier - numele fisierului pe care dorim
	* sa il scriem fara extensie.
	*/
	void export_html_fancy(const string& fisier) const;

	/** Returneaza lista de elemente din cos. 
	* @return referinta la vectorul de oferte.
	*/
	const vector<Oferta>& lista_cos() const noexcept ;

	/** Modifica oferta data. Daca nu apartine, nu se intampla nimic.
	* @param of - oferta de modificat.
	* @param new_of - noua oferta.
	* @return true - daca s-a efectuat modificarea.
	*/
	bool modifica(const Oferta& of, const Oferta& new_of);

	/** Dimensiunea cosului. 
	* @return UNSIGNED.
	*/
	const size_t dim() const noexcept;
};

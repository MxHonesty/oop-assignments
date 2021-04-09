#pragma once

#include <vector>
#include "repo/RepoOferta.h"
using std::vector;

class Cos {
private:
	vector<Oferta> elems;

public:

	/** Adauga oferta data in cos.
	* @param of - oferta pe care dorim sa o adaugam.
	* Daca se incearca introducerea a aceleasi oferte de doua ori,
	* nu se intampla nimic.
	*/
	void adauga(const Oferta& of);

	/** Sterge oferta data din cos.
	* @param of - oferta pe care dorim sa o stergem din cos.
	* Se sterge oferta.
	*/
	void sterge(const Oferta& of);

	/** Goleste cosul de elemente. */
	void golire() noexcept;

	/** Exporta cosul curent ca html.
	* @param fisier - numele fisierului dorit, FARA extensie.
	*/
	void export_html(const string& fisier) const;

	/** Exporta cosul curent ca html.
	* Versiunea cu bootstrap.
	*/
	void export_html_fancy(const string& fisier) const;

	/** Returneaza lista de elemente din cos. */
	const vector<Oferta>& lista_cos() const noexcept ;

	const unsigned dim() const noexcept;
};

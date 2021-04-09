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
	* Se creeaza o copie a ofertei.
	*/
	void adauga(const Oferta& of);

	/** Sterge oferta data din cos.
	* @param of - oferta pe care dorim sa o stergem din cos.
	* Se sterge oferta.
	*/
	void sterge(const Oferta& of);

	/** Exporta cosul curent ca html. */
	void export_html();

	/** Returneaza lista de elemente din cos. */
	const vector<Oferta>& lista_cos() noexcept ;
};

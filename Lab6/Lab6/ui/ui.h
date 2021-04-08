#pragma once
#include "../service/ServiceOferta.h"
#include "../VectorDinamic/VectorDinamic.h"

class UI {
private:
	ServiceOferta srv;  // Service curent.
	bool running;

	/** Functia ui de adaugare. */
	void ui_adaugare();

	/** Functia ui de stergere. */
	void ui_stergere();

	/** Functia ui de modificare. */
	void ui_modificare();

	/** Functia ui de cautare. */
	void ui_cautare() const;

	/** Filtrare dupa pret */
	void ui_filtrare_pret() const;

	/** Filtrare dupa destinatie */
	void ui_filtrare_destinatie() const;

	/** Functia ui de filtrare. */
	void ui_filtrare() const;

	/** Returneaza tipul citit de la tastatura pentru sortare */
	string ui_sortare_determina_tipul() const;

	/** Functie ajutatoare de sortare denumire */
	void ui_sortare_denumire() const;
	
	/** Functie ajutatoare de sortare destinatie */
	void ui_sortare_destinatie() const;
	
	/** Functie ajutatoare de sortare tip+pret */
	void sortare_tip_pret() const;

	/** Functie ajutatoare de sortare pret */
	void sortare_pret() const; 

	/** Functia ui de sortare. */
	void ui_sortare() const;

	/** Functia ui de quit. */
	void ui_quit() noexcept;

	/** Functia ui de afisare. */
	void ui_afisare() const;

	/** Afiseaza o lista de elemente */
	void afisare_lista(const vector<Oferta>& de_parcurs) const;

	/** Adauga elemente de proba */
	void adauga_elemente_de_proba();

	/** Afisare o oferta.
	* @param of - oferta de afisat.
	*/
	void afisare_oferta(const Oferta& of) const;
public:
	/** Constructor implicit */
	UI() noexcept : srv{} {
		this->running = true;
	};

	/** Functia principala a ui-ului. Contine main loop.  */
	void run();
};

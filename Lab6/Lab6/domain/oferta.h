#pragma once
/** Modul pentru clasa Oferta. Reprezinta modelarea domeniului problemei. */

#include <string>
using std::string;

#include <iostream>

class Oferta {
private:
	std::string denumire;
	std::string destinatie;
	std::string tip;
	int pret;
	int id;  // Identificator unic.
public:

	Oferta() noexcept; // Default constructor

	/** Data constructor */
	Oferta(int id, const string& denumire, const string& destinatie, const string& tip, int pret): 
		denumire{ denumire }, destinatie{ destinatie }, tip{ tip }, id{ id }, pret{ pret } {

	}

	/** Move constructor */
	Oferta(const Oferta&& elem) {
		this->denumire = elem.denumire;
		this->destinatie = elem.destinatie;
		this->tip = elem.tip;
		this->pret = elem.pret;
		this->id = elem.id;
	};

	/** Move assignemnt */
	Oferta& operator=(const Oferta&& elem) {
		//std::cout << "MOVE\n";
		this->denumire = elem.denumire;
		this->destinatie = elem.destinatie;
		this->tip = elem.tip;
		this->pret = elem.pret;
		this->id = elem.id;
		return *this;
	};

	/** Copy Assignment */
	Oferta& operator=(const Oferta& elem) {
		//std::cout << "COPY ASSIGN\n";
		this->denumire = elem.denumire;
		this->destinatie = elem.destinatie;
		this->tip = elem.tip;
		this->pret = elem.pret;
		this->id = elem.id;
		return *this;
	};

	Oferta(const Oferta& elem);
	
	/** Returneaza denumirea ofertei. */
	std::string get_denumire() const;

	/** Returneaza destinatia ofertei. */
	std::string get_destinatie() const;

	/** Returneaza tipul ofertei */
	std::string get_tip() const;

	/** Returneaza pretul ofertei. */
	int  get_pret() const noexcept;

	/** Returneaza id-ul ofertei */
	int get_id() const noexcept;

	/** Seteaza denumirea ofertei */
	void set_denumire(const std::string new_denumire);

	/** Seteaza destinatia ofertei */
	void set_destinatie(const std::string new_destinatie);

	/** Seteaza tipul ofertei */
	void set_tip(const std::string new_tip);

	/** Seteaza pretul ofertei */
	void set_pret(const int new_pret) noexcept;

	/** Egalitate dintre oferte.
		@param rhs referinta la o alta oferta
		@return true daca cele doua oferte au id egal. false altfel */
	bool operator==(const Oferta& rhs) const noexcept;

};
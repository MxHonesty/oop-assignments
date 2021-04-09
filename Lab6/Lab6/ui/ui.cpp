#include "ui.h"
#include "../errors/UiError.h"
#include "../errors/ServiceError.h"
#include <string>
#include <iostream>
#include <vector>
using std::vector;
using std::string;

void UI::ui_adaugare(){
	string denumire, destinatie, tip, pret_string;
	std::cout << "\nDenumire: ";
	std::getline(std::cin, denumire);
	
	std::cout << "Destinatie: ";
	std::getline(std::cin, destinatie);

	std::cout << "Tip: ";
	std::getline(std::cin, tip);

	std::cout << "Pret: ";
	std::getline(std::cin, pret_string);
	try {
		const int pret = std::stoi(pret_string);  // Arunca exceptie la invalid.
		if (pret < 0)
			throw UiError{ "Pret invalid" };
		srv.adaugare(denumire, destinatie, tip, pret);
	}
	catch (std::invalid_argument) {
		std::cout << "Pret invalid.";
	}
}

void UI::ui_stergere(){
	string id_string;
	
	std::cout << "\nId de sters: ";
	std::getline(std::cin, id_string);
	try {
		const int id_sters = std::stoi(id_string);
		srv.stergere(id_sters);
	}
	catch (std::invalid_argument) {
		std::cout << "Id invalid";
	}

}

void UI::ui_modificare(){
	string id_string;

	std::cout << "\nId de modificat: ";
	std::getline(std::cin, id_string);
	try {
		const int id_modificat = std::stoi(id_string);
		string denumire, destinatie, tip, pret_string;
		std::cout << "\nDenumire: ";
		std::getline(std::cin, denumire);

		std::cout << "Destinatie: ";
		std::getline(std::cin, destinatie);

		std::cout << "Tip: ";
		std::getline(std::cin, tip);

		std::cout << "Pret: ";
		std::getline(std::cin, pret_string);

		try {
			const int pret = std::stoi(pret_string);  // Arunca exceptie la invalid.
			if (pret < 0)
				throw UiError{"Pret invalid"};
			srv.modificare(id_modificat, denumire, destinatie, tip, pret);
		}
		catch (std::invalid_argument) {
			std::cout << "Pret invalid";
		}
	}
	catch (std::invalid_argument) {  // eroare de la stoi
		std::cout << "Id invalid";
	}
}

void UI::ui_cautare() const {
	string id_string;
	std::cout << "\nId de cautare: ";
	std::getline(std::cin, id_string);
	try {
		const int id_cautat = std::stoi(id_string);
		const auto& gasit = srv.cautare(id_cautat);
		this->afisare_oferta(gasit);
	}
	catch (std::invalid_argument) {
		std::cout << "Id invalid.";
	}
}

void UI::ui_filtrare_pret() const{
	string lower, upper;
	std::cout << "Limita inferioara: ";
	std::getline(std::cin, lower);
	try {  // Convertin limita inferioara in int.
		const int l = std::stoi(lower);
		std::cout << "Limita superioara: ";
		std::getline(std::cin, upper);
		int u = INT_MAX;
		if (upper == "max")  // Cazul max.
			u = INT_MAX;
		else {  // Cazul int normal.
			try {  // Incarcam conversia.
				u = std::stoi(upper);
			}
			catch (std::invalid_argument) {
				std::cout << "Limita superioara invalida. ";
				return;
			}
		}
		auto rez = this->srv.filtrare_pret(l, u);  // Se ajunge aici daca totul a fost efectuat cu succes.
		this->afisare_lista(rez);
	}
	catch (std::invalid_argument) {  // Exceptie limita inferioara
		std::cout << "Limita inferioara invalida.";
		return;
	}
}

void UI::ui_filtrare_destinatie() const{
	string destinatie;
	std::cout << "Destinatie: ";
	std::getline(std::cin, destinatie);
	auto rez = this->srv.filtrare_destinatie(destinatie);
	for (const auto& el : rez)
		this->afisare_oferta(el);
}

void UI::ui_filtrare() const {
	string tip_filtrare;
	std::cout << "\nTip Filtrare (destinatie / pret): ";
	std::getline(std::cin, tip_filtrare);
	std::cout << "\n";

	if (tip_filtrare == "destinatie") {  // Filtrare Destinatie
		ui_filtrare_destinatie();
	}
	else if (tip_filtrare == "pret") {  // Filtrare Pret
		ui_filtrare_pret();
	}
	else
		throw UiError{"Tipul sortarii invalid"};
}

string UI::ui_sortare_determina_tipul() const {
	string tip;
	std::cout << "\nTipul sortarii (crescator / descrescator): ";
	std::getline(std::cin, tip);

	return tip;
}

void UI::ui_sortare_denumire() const {
	string tip = this->ui_sortare_determina_tipul();
	if (tip == "crescator") {
		auto vec = srv.sortare([](const Oferta& a, const Oferta& b) {return a.get_denumire() < b.get_denumire(); });
		this->afisare_lista(vec);
	}
	else if (tip == "descrescator") {
		auto vec = srv.sortare([](const Oferta& a, const Oferta& b) {return a.get_denumire() > b.get_denumire(); });
		this->afisare_lista(vec);
	}
	else
		throw UiError{"Tipul sortarii invalid"};
}

void UI::ui_sortare_destinatie() const{
	string tip = this->ui_sortare_determina_tipul();
	if (tip == "crescator") {
		auto vec = srv.sortare([](const Oferta& a, const Oferta& b) {return a.get_destinatie() < b.get_destinatie(); });
		this->afisare_lista(vec);
	}
	else if (tip == "descrescator") {
		auto vec = srv.sortare([](const Oferta& a, const Oferta& b) {return a.get_destinatie() > b.get_destinatie(); });
		this->afisare_lista(vec);
	}
	else
		throw UiError{ "Tipul sortarii invalid" };
}

void UI::sortare_tip_pret() const{
	string tip = this->ui_sortare_determina_tipul();
	if (tip == "crescator") {
		auto vec = srv.sortare([](const Oferta& a, const Oferta& b) {
			if (a.get_tip() == b.get_tip())
				return a.get_pret() < b.get_pret();
			return a.get_tip() < b.get_tip();
		});
		this->afisare_lista(vec);
	}
	else if (tip == "descrescator") {
		auto vec = srv.sortare([](const Oferta& a, const Oferta& b) {
			if (a.get_tip() == b.get_tip())
				return a.get_pret() > b.get_pret();
			return a.get_tip() > b.get_tip();
		});
		this->afisare_lista(vec);
	}
	else
		throw UiError{ "Tipul sortarii invalid" };
}

void UI::sortare_pret() const{
	string tip = this->ui_sortare_determina_tipul();
	if (tip == "crescator") {
		auto vec = srv.sortare([](const Oferta& a, const Oferta& b) noexcept {
			return a.get_pret() < b.get_pret();
		});
		this->afisare_lista(vec);
	}
	else if (tip == "descrescator") {
		auto vec = srv.sortare([](const Oferta& a, const Oferta& b) noexcept {
			return a.get_pret() > b.get_pret();
		});
		this->afisare_lista(vec);
	}
	else
		throw UiError{ "Tipul sortarii invalid" };
}

void UI::ui_sortare() const {
	string tip_sortare;
	std::cout<<"\nTipul sortare (denumire / destinatie / tip+pret / pret): ";
	std::getline(std::cin, tip_sortare);
	if (tip_sortare == "denumire") {
		this->ui_sortare_denumire();
	}
	else if (tip_sortare == "destinatie") {
		this->ui_sortare_destinatie();
	}
	else if (tip_sortare == "tip+pret") {
		this->sortare_tip_pret();
	}
	else if (tip_sortare == "pret") {
		this->sortare_pret();
	}
	else
		throw UiError{"Tipul sortarii invalid"};
}

void UI::ui_quit() noexcept {
	this->running = false;
}

void UI::ui_afisare() const {
	auto& lista = srv.get_ref_all();
	this->afisare_lista(lista);
}

void UI::afisare_lista(const vector<Oferta>& de_parcurs) const {
	for (const auto& el : de_parcurs)
		this->afisare_oferta(el);
}

void UI::adauga_elemente_de_proba(){
	srv.adaugare("J", "Grecia", "Vacanta", 300);
	srv.adaugare("I", "Bhutan", "Expeditie", 500);
	srv.adaugare("H", "Nepal", "Expeditie", 500);
	srv.adaugare("G", "Korea", "Vacanta", 900);
	srv.adaugare("F", "Japonia", "Cazare", 1200);
	srv.adaugare("E", "SUA", "Vacanta", 1000);
	srv.adaugare("D", "UK", "Vacanta", 500);
	srv.adaugare("C", "Franta", "Vacanta", 400);
	srv.adaugare("B", "Romania", "Vacanta", 200);
	srv.adaugare("A", "Franta", "Cazare", 400);
}

void UI::afisare_oferta(const Oferta& of) const {
	std::cout << "\n";
	std::cout<< "Id: " << of.get_id() <<"   Denumire: "<<of.get_denumire()<<"   Destinatie: "<<of.get_destinatie()<<"   Tip: "<<of.get_tip()<<"   Pret: "<<of.get_pret() << "\n";
}

void UI::ui_afisare_cos() const {
	afisare_lista(srv.vector_cos());
}

void UI::ui_export_cos() const {
	string fisier;
	std::cout << "\nNume fisier(fara extensie): ";
	std::getline(std::cin, fisier);
	srv.export_html_cos(fisier);
}

void UI::ui_adauga_cos() {
	string denumire;
	std::cout << "\nDenumirea: ";
	std::getline(std::cin, denumire);
	srv.adauga_cos(denumire);
}

void UI::ui_sterge_cos() {
	string denumire;
	std::cout << "\nDenumirea: ";
	std::getline(std::cin, denumire);
	srv.sterge_din_cos(denumire);
}

void UI::ui_golire_cos() {
	srv.golire_cos();
}

void UI::ui_random_cos() {
	string numar_string;
	std::cout << "\nNumarul de elemente: ";
	std::getline(std::cin, numar_string);
	try {
		const unsigned int numar = std::stoi(numar_string);
		if (numar <= 0 or numar > srv.get_all().size())
			throw std::invalid_argument{"Numar invalid"};
		srv.golire_cos();
		srv.adauga_random_cos(numar);
	}
	catch (std::invalid_argument) {
		std::cout << "Numar invalid";
	}
}



void UI::run(){
	while (this->running) {
		std::cout << R"(
Alegeti o optiune: 
1  - Adaugare 
2  - Stergere 
3  - Modificare 
4  - Cautare 
5  - Filtrare 
6  - Sortare 
7  - Afisare
8  - Adauga elemente proba
9  - Afisare cos
10 - Adauga cos
11 - Sterge cos
12 - Goleste cos
13 - Random cos
14 - Export cos
q  - Iesire
)";
		std::cout << "Numarul de oferte din cos: " << srv.dimensiune_cos() <<"\n";
		string comanda;
		std::cout << "Optiune: ";
		std::getline(std::cin, comanda);  // Citim linia.
		try {
			if (comanda == "q") ui_quit();
			else if (comanda == "1") ui_adaugare();
			else if (comanda == "2") ui_stergere();
			else if (comanda == "3") ui_modificare();
			else if (comanda == "4") ui_cautare();
			else if (comanda == "5") ui_filtrare();
			else if (comanda == "6") ui_sortare();
			else if (comanda == "7") ui_afisare();
			else if (comanda == "8") adauga_elemente_de_proba();
			else if (comanda == "9") ui_afisare_cos();
			else if (comanda == "10") ui_adauga_cos();
			else if (comanda == "11") ui_sterge_cos();
			else if (comanda == "12") ui_golire_cos();
			else if (comanda == "13") ui_random_cos();
			else if (comanda == "14") ui_export_cos();
		}
		catch (const std::exception& e) {
			std::cout << "\n" << e.what() << "\n";
		}
	}
}

#include "oferta.h"
#include <iostream>

Oferta::Oferta() noexcept{
	this->pret = 0;
	this->id = 0;
}

Oferta::Oferta(const Oferta& elem){
	this->denumire = elem.denumire;
	this->destinatie = elem.destinatie;
	this->tip = elem.tip;
	this->pret = elem.pret;
	this->id = elem.id;
	//std::cout << "Oferta Copiata \n";
}

std::string Oferta::get_denumire() const{
	return this->denumire;
}

std::string Oferta::get_destinatie() const{
	return this->destinatie;
}

std::string Oferta::get_tip() const {
	return this->tip;
}

int Oferta::get_pret() const noexcept {
	return this->pret;
}

int Oferta::get_id() const noexcept {
	return this->id;
}

bool Oferta::operator==(const Oferta& rhs) const noexcept {
	return this->get_id() == rhs.get_id();
}

bool Oferta::equals(const Oferta& other) const noexcept {
	return (id == other.id) and (denumire == other.denumire) and
		(tip == other.tip) and (destinatie == other.denumire);
}

void Oferta::set_denumire(const std::string new_denumire){
	this->denumire = new_denumire;
}

void Oferta::set_destinatie(const std::string new_destinatie){
	this->destinatie = new_destinatie;
}

void Oferta::set_tip(const std::string new_tip){
	this->tip = new_tip;
}

void Oferta::set_pret(const int new_pret) noexcept {
	this->pret = new_pret;
}

std::ostream& operator<<(std::ostream& os, const Oferta& dt) {
	os << dt.id <<" "<<dt.denumire<<" "<<dt.destinatie<<" "<<dt.tip<<" "<<dt.pret<<"\n";
	return os;
}

std::istream& operator>>(std::istream& in, Oferta& of) {
	in >> of.id >> of.denumire >> of.destinatie >> of.tip >> of.pret;
	return in;
}

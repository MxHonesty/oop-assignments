#include "Cos.h"

void Cos::adauga(const Oferta& of) {
	elems.push_back(of);
}

void Cos::sterge(const Oferta& of) {
	auto gasit = std::remove_if(elems.begin(), elems.end(), 
		[of](const Oferta& el) noexcept {return el == of; });
	if (gasit != elems.end()) {
		elems.erase(gasit, elems.end());
	}
}

void Cos::export_html() {
}

const vector<Oferta>& Cos::lista_cos() noexcept {
	return elems;
}

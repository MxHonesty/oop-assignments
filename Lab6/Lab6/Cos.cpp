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

const unsigned Cos::dim() const {
	return elems.size();
}

void Cos::export_html() const {
}

const vector<Oferta>& Cos::lista_cos() const noexcept {
	return elems;
}

#include "Cos.h"
#include <fstream>
#include "errors/ServiceError.h"

void Cos::adauga(const Oferta& of) {
	const auto& gasit = std::find(elems.begin(), elems.end(), of);
	if (gasit == elems.end())
		elems.push_back(of);
}

void Cos::sterge(const Oferta& of) {
	auto gasit = std::remove_if(elems.begin(), elems.end(), 
		[of](const Oferta& el) noexcept {return el == of; });
	if (gasit != elems.end()) {
		elems.erase(gasit, elems.end());
	}
}

void Cos::golire() noexcept {
	elems.clear();
}

const unsigned Cos::dim() const noexcept {
	return elems.size();
}

void Cos::export_html(const string& fisier) const {
	const std::string filename = fisier + ".html";
	std::ofstream f(filename);
	f << "<!DOCTYPE html><html><body>";
	f << "<ul>";  // unordered list.
	for (const auto& el : elems) {
		const string denumire = el.get_denumire();
		const string destinatie = el.get_destinatie();
		const string tip = el.get_tip();
		const string pret = std::to_string(el.get_pret());
		f << "<li>" << denumire << " " << destinatie << " " 
			<< tip << " " << pret << "</li>";
	}
	f << "</ul>";
	f << "</body></html>";

	f.close();
}


const vector<Oferta>& Cos::lista_cos() const noexcept {
	return elems;
}

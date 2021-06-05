#include "Repository.h"
#include <fstream>
#include <exception>

void Repository::load_from_file(std::istream& in) {
	while (!in.eof()) {
		Produs prod{ -1, "A", "A", 0, 0 };
		try {
			in >> prod;
		}
		catch (...) {
			continue;
		}

		elems.push_back(prod);
	}
}

Repository::Repository(std::istream& in) {
	this->load_from_file(in);
}

Repository::Repository(const string& filename) {
	std::ifstream f{ filename };
	this->load_from_file(f);
}

const Produs& Repository::get_produs(const int id) const {
	auto found = std::find_if(elems.begin(), elems.end(), [id](const Produs& prod) {
		if (prod.get_id() == id) {
			return true;
		}
		return false;
	});

	if (found == elems.end()) {
		throw std::exception{ "element with given id not found" };
	} else return *found;
}

const vector<Produs>& Repository::get_all() const {
	return elems;
}

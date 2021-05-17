#include "Repository.h"
#include <exception>
#include <fstream>
#include <exception>
#include "Produs.h"

void Repository::initializare_din_fisier(string name) {
    std::ifstream file(name);
    if (file.fail()) {
        throw std::exception{ "Eroare fisier" };
    }
    else {
        while (!file.eof()) {
            Produs citit{ 0, "a", "a", 10, 10 };
            try {
                file >> citit;
            }
            catch (...) {
                continue;
            }
            //adauga(citit);
            elems.push_back(citit);
        }
        file.close();
    }
}

void Repository::adauga(const Produs& prod) {
    elems.push_back(prod);
}

int Repository::stoc_necesar(const int id) const {
    for (const auto& el : elems) {
        if (el.get_id() == id) {
            const int diferenta = el.get_cn() - el.get_ca();
            if (diferenta > 0)
                return diferenta;
            return 0;
        }
    }
    throw std::exception{ "Nu exista element cu id dat" };
}

vector<Produs> Repository::get_all() const {
    return elems;
}

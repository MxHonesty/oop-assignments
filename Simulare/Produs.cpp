#include "Produs.h"
#include <sstream>

int Produs::get_id() const {
    return id;
}

string Produs::get_denumire() const {
    return denumire;
}

string Produs::get_tip() const {
    return tip;
}

int Produs::get_ca() const {
    return ca;
}

int Produs::get_cn() const {
    return cn;
}

std::istream& operator>>(std::istream& in, Produs& prod) {
    string line;
    std::getline(in, line);

    const auto gasite = std::count(line.begin(), line.end(), ',');
    // Trebuie sa avem 4 virgule.
    if (gasite != 4)
        throw std::exception{ "Stream error" };

    std::istringstream token{ line };
    string str_id, str_denumire, str_tip, str_ca, str_cn;

    std::getline(token, str_id, ',');
    std::getline(token, str_denumire, ',');
    std::getline(token, str_tip, ',');
    std::getline(token, str_ca, ',');
    std::getline(token, str_cn, ',');

    int id = 0, ca = 0, cn = 0;
    try {
        id = stoi(str_id);
        ca = stoi(str_ca);
        cn = stoi(str_cn);
    }
    catch (...) {
        throw std::exception{ "Stream error" };
    }

    prod.id = id;
    prod.denumire = str_denumire;
    prod.tip = str_tip;
    prod.ca = ca;
    prod.cn = cn;
    
    return in;
}

#include "Service.h"
#include <sstream>
#include <algorithm>

Service::Service() : repo{ std::istringstream{"10|DEN|TIP|10|11|\n11|DEN|TIP|11|11|\n2|DEN3|TIP|10|30|\n1|DEN2|TIP|30|11|\n"} } {}

vector<Produs> Service::sort_tip() const {
    auto vec = repo.get_all();  // Copy the elements.
    sort(vec.begin(), vec.end(), [](const Produs& p1, const Produs& p2) {
        if (p1.get_tip() < p2.get_tip())
            return true;
        return false;
    });

    return vec;
}

vector<Produs> Service::sort_ca() const {
    auto vec = repo.get_all();  // Copy the elements.
    sort(vec.begin(), vec.end(), [](const Produs& p1, const Produs& p2) {
        if (p1.get_ca() < p2.get_ca())
            return true;
        return false;
    });

    return vec;
}

vector<Produs> Service::get_all() const {
    return repo.get_all();
}

const Produs& Service::find(const int id) {
    return repo.get_produs(id);
}

bool Service::este_nevoie(const int id) {
    const auto& prod = repo.get_produs(id);
    if (prod.get_ca() < prod.get_cn())
        return true;
    return false;
}

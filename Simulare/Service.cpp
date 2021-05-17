#include "Service.h"
#include <algorithm>

std::vector<Produs> Service::get_all() {
    return repo.get_all();
}

std::vector<Produs> Service::sortare_stoc_desc() {
    auto vec = repo.get_all();

    std::sort(vec.begin(), vec.end(), [](const Produs& a, const Produs& b) {
        return a.get_ca() > b.get_ca();
    });

    return vec;
}

std::vector<Produs> Service::sortare_tip_crescator() {
    auto vec = repo.get_all();

    std::sort(vec.begin(), vec.end(), [](const Produs& a, const Produs& b) {
        return a.get_tip() < b.get_tip();
    });

    return vec;
}

int Service::stoc_necesar(const int id) {
    return repo.stoc_necesar(id);
}

bool Service::nu_este_suficient(const int id) {
    return repo.stoc_necesar(id) == 0;
}

#include "Service.h"
#include <algorithm>

const vector<Task> Service::get_all() {
    auto vec = repo.get_all();

    // Sortam
    sort(vec.begin(), vec.end(), [](const Task& t1, const Task& t2) {
        return t1.get_descriere() < t2.get_descriere();
    });

    return vec;
}

void Service::add_task(const int id, const string& descriere, const string& tip, const vector<string>& prog) {
    auto vec = repo.get_all();

    // verificam id.
    for (const auto& el : vec)
        if (el.get_id() == id)
            throw std::exception{ "id existent" };

    if (tip != "open" && tip != "inprogress" && tip != "closed")
        throw std::exception{"stare invalida"};

    Task new_task{ id, descriere, tip, prog };
    repo.add(new_task);
    update();
}

const vector<Task> Service::get_programator(string programator) {
    vector<Task> rez;
    for (const auto& el : repo.get_all()) {
        for (const auto& p : el.get_programatori()) {
            if (p == programator) {
                rez.push_back(el);
                break;
            }
        }
    }

    return rez;
}

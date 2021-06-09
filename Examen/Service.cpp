#include "Service.h"
#include <algorithm>

const vector<Task> Service::get_all() {
    auto vec =  repo.get_all();
    sort(vec.begin(), vec.end(), [](const Task& t1, const Task& t2) {
        return t1.get_stare() < t2.get_stare();
    });

    return vec;
}

void Service::add_task(const int id, const string& descriere, const string& stare, const vector<string>& programatori) {
    const auto& vec = repo.get_all();  // Pentru validare.

    // Verificam id.
    for (const auto& el : vec) {
        if (el.get_id() == id)
            throw std::exception{"Exista element cu id dat"};
    }

    // Verifica descriere nevida.
    if (descriere == "")
        throw std::exception{"Descriere vida"};

    // Verifica stare
    if (stare != "open" && stare != "inprogress" && stare != "closed")
        throw std::exception{"Stare invalida"};

    Task tsk{id, descriere, stare, programatori};
    repo.add(tsk);
    update();
}

void Service::change_stare(const int id, const string& new_stare) {
    repo.change_stare(id, new_stare);
    update();
}

const vector<Task> Service::get_programtor(string programtor) {
    vector<Task> rez;

    for (const auto& el : repo.get_all()) {
        for (const auto& prog : el.get_programatori()) {
            if (prog == programtor) {
                rez.push_back(el);
                break;
            }
        }
    }

    sort(rez.begin(), rez.end(), [](const Task& t1, const Task& t2) {
        return t1.get_stare() < t2.get_stare();
    });

    return rez;
}

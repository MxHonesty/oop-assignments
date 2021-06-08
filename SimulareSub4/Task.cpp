#include "Task.h"
#include <iostream>
#include <sstream>
#include <qdebug.h>

int Task::get_id() const {
    return id;
}

string Task::get_descriere() const {
    return descriere;
}

string Task::get_stare() const {
    return stare;
}

vector<string> Task::get_programatori() const {
    return programatori;
}

void Task::set_stare(const string& new_stare) {
    this->stare = new_stare;
}

std::ostream& operator<<(std::ostream& out, Task& tsk) {
    out << tsk.id << '|' << tsk.descriere << '|' << tsk.stare << '|';
    for (const auto& el : tsk.programatori)
        out << el << '|';

    out << '#' << '|';  // Adaug un terminator.
    out << '\n';

    return out;
}

std::istream& operator>>(std::istream& in, Task& tsk) {
    string input;
    std::getline(in, input);

    std::istringstream in_stream{ input };
    string id_str, denumire, stare;
    vector<string> programatori;

    string prog;
    std::getline(in_stream, id_str, '|');

    std::getline(in_stream, denumire, '|');
    std::getline(in_stream, stare, '|');

    std::getline(in_stream, prog, '|');
    while (prog != "#" && prog != "") {
        programatori.push_back(prog);
        std::getline(in_stream, prog, '|');
    }

    tsk.id = std::stoi(id_str);
    tsk.descriere = denumire;
    tsk.stare = stare;
    tsk.programatori = programatori;
    return in;
}

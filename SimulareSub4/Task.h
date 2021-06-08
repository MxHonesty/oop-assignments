#pragma once

#include <string>
#include <vector>
using std::string;
using std::vector;


class Task {
private:
	int id;
	string descriere, stare;
	vector<string> programatori;

public:

	// Constructor implicit.
	Task(const int id, const string& descriere, const string& stare, const vector<string>& programatori) :
		id{ id }, descriere{ descriere }, stare{ stare }, programatori{ programatori } {};

	// Returneaza id-ul Task-ului.
	int get_id() const;

	// Returneaza descrierea task-ului.
	string get_descriere() const;

	// Returneaza starea task-ului.
	string get_stare() const;

	// Returneaza Lista de programatori ai Task-ului.
	vector<string> get_programatori() const;

	void set_stare(const string& new_stare);

	friend std::ostream& operator<<(std::ostream& out, Task& tsk);

	friend std::istream& operator>>(std::istream& in, Task& tsk);
};

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

	// Constructor default
	Task() : id{}, descriere{}, stare{}, programatori{} {};

	// Data constructor
	Task(const int id, const string descriere, const string stare, const vector<string> programatori) :
		id{ id }, descriere{ descriere }, stare{ stare }, programatori{ programatori } {};

	// Returneaza id Task.
	int get_id() const;

	// Returneaza descriere Task.
	string get_descriere() const;

	// Returnea stare task.
	string get_stare() const;

	// Returneaza vector programatori task.
	vector<string> get_programatori() const;

	// Seteaza starea taskului la new_stare.
	void set_stare(const string new_stare);
	
	// SCriere task in stream. ID|DESC|STARE|PROG|#|
	friend std::ostream& operator<<(std::ostream& out, Task& tsk);

	// Citire task din stream.
	// Arunca std::exception la eroare de conversie la int.
	friend std::istream& operator>>(std::istream& in, Task& tsk);
};

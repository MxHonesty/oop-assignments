#pragma once
#include "Repository.h"
#include "Observer.h"


class Service : public Observable {
private:
	Repository repo;

public:
	
	// Initializam repo pentru fisier data.txt
	Service(const string& filename) : repo{ filename } {};

	// Returneaza toate elementele
	// Mereu returneaza sortat dupa stare.
	const vector<Task> get_all();

	// Adauga un task in repo.
	// Face verificarile de rigoare si arunca std::exception daca nu este task valid.
	// Validari: id unic, stare corecta.
	void add_task(const int id, const string& descriere, const string& stare, const vector<string>& programatori);

	// Schimba starea unui element. ARunca exceptie daca nu exista element
	// Cu id dat.
	void change_stare(const int id, const string& new_stare);

	// Returneaza un vector de Taskuri la care a lucrat programatorul dat.
	// Lista returnata este sortata.
	const vector<Task> get_programtor(string programtor);
};

#include "Test.h"
#include "Task.h"
#include <sstream>
#include <cassert>
#include "Repository.h"
#include "Service.h"

void Test::test_task() {
	// Testam citirea unui task din stream.
	std::istringstream in{ "0|DescA|open|A|B|C|#|\n1|DescB|open|#|\n" };
	
	Task tsk1, tsk2;
	in >> tsk1 >> tsk2;
	assert(tsk1.get_id() == 0);
	assert(tsk2.get_id() == 1);

	assert(tsk1.get_descriere() == "DescA");
	assert(tsk2.get_descriere() == "DescB");

	// Ne Asiguram ca s-au citit bine programatorii.
	assert(tsk1.get_programatori().size() == 3);
	assert(tsk2.get_programatori().size() == 0);

	// Testam setarea de stare.
	tsk1.set_stare("closed");
	assert(tsk1.get_stare() == "closed");
}

void Test::test_repo() {
	// Incarcam repo din fisierul de test.
	Repository repo{"test.txt"};
	// Trebuie sa fie 10 elemente.
	assert(repo.get_all().size() == 10);

	// Testam schimbarea de stare.
	repo.change_stare(0, "closed");
	assert(repo.get_all().at(0).get_stare() == "closed");
}

void Test::test_service() {
	// Testam metoda get_all
	Service srv{ "test.txt" };
	auto vec = srv.get_all();

	// ne asteptam sa fie 10 elemente.
	assert(vec.size() == 10);

	// Testam metoda get_programator.
	auto prog = srv.get_programtor("A");
	// Ne asteptam sa aiba marimea 4.
	assert(prog.size() == 4);
	// id 0 3 5 7
	assert(prog.at(0).get_id() == 0);
	assert(prog.at(1).get_id() == 3);
	assert(prog.at(2).get_id() == 5);
	assert(prog.at(3).get_id() == 7);
}

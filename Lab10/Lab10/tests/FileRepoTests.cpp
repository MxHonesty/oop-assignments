#include "FileRepoTests.h"

#include <cassert>
#include <iostream>
#include <fstream>
#include "../repo/RepoFile.h"
#include "../errors/RepoError.h"

/** Testare adaugare */
void test_file_repo_add() {
	RepoFile repo;
	for (int i = 0; i < 10; i++)
		repo.add({ i, "A", "A", "A", 10 });
	assert(repo.dim() == 10);
	for (int i = 0; i < 10; i++)
		assert(repo.search(i));
	assert(! repo.search(10));

	std::remove("salvare.txt");
}

/** Testare remove */
void test_file_repo_remove() {
	RepoFile repo;
	for (int i = 0; i < 10; i++)
		repo.add({ i, "A", "A", "A", 10 });
	assert(repo.dim() == 10);
	for (int i = 0; i < 5; i++)
		repo.remove(i);
	assert(repo.dim() == 5);

	for (int i = 0; i < 20; i++) {
		repo.remove(i);
	}
	assert(repo.dim() == 0);
	std::remove("salvare.txt");
}

/** Testare search */
void test_file_repo_search() {
	RepoFile repo;
	for (int i = 0; i < 10; i += 2)  // Adaugam doar index par.
		repo.add({ i, "A", "A", "A", 10 });
	for (int i = 0; i < 10; i++) {
		i % 2 == 0 ? assert(repo.search(i)) : assert(! repo.search(i));
	}

	assert(! repo.search(100));

	repo.add({ 1000, "B", "B", "B", 20 });
	assert(repo.search(1000));
	repo.remove(1000);
	assert(! repo.search(1000));
	std::remove("salvare.txt");
}

/** Testare get_all */
void test_file_repo_get_all() {
	RepoFile repo;
	for (int i = 0; i < 50; i++)
		repo.add({ i, "a", "a", "a", 10 });  // Adaugam 50 de elemente

	vector<Oferta> t = repo.get_all();
	for (auto& el : t) {  // Aceste elemente trebuie sa fie in repo)
		const int id = el.get_id();
		assert(repo.search(id));
	}
	assert(t.size() == repo.dim());
	std::remove("salvare.txt");
}

/** Testare remove_all */
void test_file_repo_remove_all() {
	RepoFile repo;
	for (int i = 0; i < 100; i++)
		repo.add({ i, "a", "a", "a", 1 });
	assert(repo.dim() == 100);
	repo.remove_all();
	assert(repo.dim() == 0);
	std::remove("salvare.txt");
}

/** Testare dim */
void test_file_repo_dim() {
	RepoFile repo;
	for (int i = 0; i < 50; i++)
		repo.add({ i, "a", "a", "a", 10 });
	assert(repo.dim() == 50);
	std::remove("salvare.txt");
}

/** Testare search */
void test_file_search_element() {
	RepoFile repo;
	Oferta a{ 1, "a", "a", "a", 10 };
	for (int i = 2; i < 5; i++)
		repo.add({ i, "a", "a", "a", 20 });
	repo.add(a);
	for (int i = 5; i < 10; i++)
		repo.add({ i, "a", "a", "a", 20 });
	assert(a == repo.search_element(1));
	try {
		repo.search_element(1000);
		assert(false);
	}
	catch (RepoError) {
		assert(true);
	}
	std::remove("salvare.txt");
}

/** Testare search denumire */
void test_file_repo_search_denumire() {
	RepoFile repo;
	Oferta a{ 1, "a", "a", "a", 1 };
	Oferta b{ 1, "b", "a", "a", 1 };
	Oferta c{ 1, "c", "a", "a", 1 };
	repo.add(a);
	repo.add(b);
	repo.add(c);
	assert(repo.search_denumire("a"));
	assert(repo.search_denumire("b"));
	assert(repo.search_denumire("c"));
	assert(! repo.search_denumire("d"));

	const Oferta& verif = repo.search_get_denumire("a");
	assert(a == verif);

	try {
		repo.search_get_denumire("ABAB");
	}
	catch (...) {
		assert(true);
	}
	std::remove("salvare.txt");
}

/** Testare update_element */
void test_file_update_element() {
	RepoFile repo;
	for (int i = 0; i < 10; i++)
		repo.add({ i, "a", "a", "a", 10 });
	repo.update(5, { 5, "b", "b", "b", 100 });
	Oferta de_comp{ 5, "a", "a", "a", 10 };
	assert(! (repo.search_element(5).get_pret() == de_comp.get_pret()));
	de_comp = { 5, "b", "b", "b", 100 };
	assert(repo.search_element(5).get_pret() == de_comp.get_pret());
	std::remove("salvare.txt");
}

void test_file_get_max_index() {
	RepoFile repo;
	repo.add({9, "a", "a", "a", 100});
	assert(repo.get_max_index() == 9);
	std::remove("salvare.txt");
}

void test_file_citire_fisier() {
	std::ifstream in{ "salvare.txt" };
	in.close();
	std::ofstream out{ "salvare.txt" };
	const Oferta a{1, "a", "a", "a", 2};
	const Oferta b{2, "b", "a", "a", 2};
	const Oferta c{3, "c", "a", "a", 2};
	const Oferta d{3, "d", "a", "a", 2};
	out << a << b << c << d;
	out.close();
	const RepoFile repo;
	repo.search_element(1).equals(a);
	repo.search_element(2).equals(b);
	repo.search_element(3).equals(c);
	assert(repo.get_max_index() == 3);

	std::remove("salvare.txt");
}

void test_file_cititm_element_gol() {
	std::ifstream in{ "salvare.txt" };
	in.close();
	std::ofstream out{ "salvare.txt" };
	const Oferta a{ 1, "", "a", "a", 2 };
	const Oferta b{ 2, "a", "", "a", 2 };
	const Oferta c{ 3, "a", "a", "", 2 };
	out << a << b << c;
	out.close();
	const RepoFile repo;
	assert(repo.get_max_index() == 0);
	std::remove("salvare.txt");
}

void test_bad_name() {
	try {
		RepoFile repo{ "<<>>" };
		repo.add({1, "a", "a", "a", 1});
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void test_afisare_elemente() {
	RepoFile repo;
	Oferta a{1, "a", "a", "a", 1};
	Oferta b{2, "b", "a", "a", 1};
	Oferta c{3, "c", "a", "a", 1};
	Oferta d{4, "d", "a", "a", 1};
	repo.add(a);
	repo.add(b);
	repo.add(c);
	repo.add(d);

	const auto& vec = repo.afisare();
	assert(vec.size() == 4);

	std::remove("salvare.txt");
}

void Testing::run_file_repo_tests() {
	std::remove("salvare.txt");
	test_file_repo_add();
	test_file_repo_remove();
	test_file_repo_search();
	test_file_repo_get_all();
	test_file_repo_remove_all();
	test_file_repo_dim();
	test_file_search_element();
	test_file_update_element();
	test_file_repo_search_denumire();
	test_file_get_max_index();
	test_file_citire_fisier();
	test_file_cititm_element_gol();
	test_bad_name();
	test_afisare_elemente();
	std::remove("salvare.txt");
}

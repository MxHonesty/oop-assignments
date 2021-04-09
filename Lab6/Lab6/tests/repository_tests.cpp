#include "repository_tests.h"
#include <cassert>
#include "../repo/RepoOferta.h"
#include "../errors/RepoError.h"
#include <iostream>

void test_repo_add() {
	RepoOferte repo;
	for(int i = 0; i < 10; i++)
		repo.add({ i, "A", "A", "A", 10 });
	assert(repo.dim() == 10);
	for (int i = 0; i < 10; i++)
		assert(repo.search(i));
	assert(not repo.search(10));
}

void test_repo_remove() {
	RepoOferte repo;
	for (int i = 0; i < 10; i++)
		repo.add({i, "A", "A", "A", 10});
	assert(repo.dim() == 10);
	for (int i = 0; i < 5; i++)
		repo.remove(i);
	assert(repo.dim() == 5);

	for (int i = 0; i < 20; i++) {
		repo.remove(i);
	}
	assert(repo.dim() == 0);
}

void test_repo_search() {
	RepoOferte repo;
	for (int i = 0; i < 10; i += 2)  // Adaugam doar index par.
		repo.add({ i, "A", "A", "A", 10 });
	for (int i = 0; i < 10; i++) {
		i % 2 == 0 ? assert(repo.search(i)) : assert(not repo.search(i));
	}

	assert(not repo.search(100));

	repo.add({1000, "B", "B", "B", 20});
	assert(repo.search(1000));
	repo.remove(1000);
	assert(not repo.search(1000));
}

void test_repo_get_all() {
	RepoOferte repo;
	for (int i = 0; i < 50; i++)
		repo.add({i, "a", "a", "a", 10});  // Adaugam 50 de elemente

	vector<Oferta> t = repo.get_all();
	for (auto& el : t) {  // Aceste elemente trebuie sa fie in repo)
		const int id = el.get_id();
		assert(repo.search(id));
	}
	assert(t.size() == repo.dim());
}

void test_repo_remove_all() {
	RepoOferte repo;
	for (int i = 0; i < 100; i++)
		repo.add({i, "a", "a", "a", 1});
	assert(repo.dim() == 100);
	repo.remove_all();
	assert(repo.dim() == 0);
}

void test_repo_dim() {
	RepoOferte repo;
	for (int i = 0; i < 50; i++)
		repo.add({i, "a", "a", "a", 10});
	assert(repo.dim() == 50);
}

void test_search_element() {
	RepoOferte repo;
	Oferta a{1, "a", "a", "a", 10};
	for (int i = 2; i < 5; i++)
		repo.add({i, "a", "a", "a", 20});
	repo.add(a);
	for (int i = 5; i < 10; i++)
		repo.add({i, "a", "a", "a", 20});
	assert(a == repo.search_element(1));
	try {
		repo.search_element(1000);
		assert(false);
	}
	catch (RepoError) {
		assert(true);
	}
}

void test_update_element() {
	RepoOferte repo;
	for (int i = 0; i < 10; i++)
		repo.add({i, "a", "a", "a", 10});
	repo.update(5, { 5, "b", "b", "b", 100 });
	Oferta de_comp{ 5, "a", "a", "a", 10 };
	assert(not (repo.search_element(5).get_pret() == de_comp.get_pret()));
	de_comp = {5, "b", "b", "b", 100};
	assert(repo.search_element(5).get_pret() == de_comp.get_pret());
}

void Testing::run_oferta_repository_tests(){
	test_repo_add();
	test_repo_remove();
	test_repo_search();
	test_repo_get_all();
	test_repo_remove_all();
	test_repo_dim();
	test_search_element();
	test_update_element();
}

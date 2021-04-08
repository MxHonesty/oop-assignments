#include "service_tests.h"
#include "../service/ServiceOferta.h"
#include <cassert>
#include <iostream>

void srv_adaugare_test() {
	ServiceOferta srv;
	for(int i = 0; i < 10; i++)
		srv.adaugare("a", "a", "a", 10);
	auto de_test = srv.get_all(); 
	assert(de_test.size() == 10);
}

void srv_stergere_test() {
	ServiceOferta srv;
	for (int i = 0; i < 20; i++)
		srv.adaugare("a", "a", "a", 100);
	assert(srv.get_all().size() == 20);
	for (int i = 0; i < 10; i++)  // Stergem 10 elemente
		srv.stergere(i);
	assert(srv.get_all().size() == 10);

	try {
		srv.stergere(1);
	}
	catch (...) {
		assert(true);
	}

	auto vec = srv.get_all();
	int i = 10;
	for (const auto& el : vec) {
		if (el.get_id() != i)
			assert(false);
		i++;
	}
	assert(i == 20);
}

void srv_modificare_test() {
	ServiceOferta srv;
	for (int i = 0; i < 10; i++)
		srv.adaugare("a", "a", "a", 100);

	try {
		srv.modificare(10, "b", "b", "b", 1);  // Elementul nu exista
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	// Modificam un element din lista.
	srv.modificare(5, "b", "b", "b", 1);
	assert(srv.cautare(5).get_pret() == 1);
}

void srv_cautare_test() {
	ServiceOferta srv; 
	for (int i = 0; i < 10; i++)
		srv.adaugare("a", "a", "a", 100);

	Oferta of = srv.cautare(5);
	assert(of.get_pret() == 100);

	try {
		srv.cautare(10);  // Nu exista.
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void srv_filtrare_pret_test() {
	ServiceOferta srv;
	for(int i = 0; i < 100; i++)
		srv.adaugare("a", "a", "a", i);
	auto rez = srv.filtrare_pret(0, 49);
	assert(rez.size() == 50);
	int i = 0;
	for (const auto& el : rez) {
		assert(i == el.get_pret());
		i++;
	}
}

void srv_filtrare_destinatie_test() {
	ServiceOferta srv;
	srv.adaugare("a", "a", "a", 1);
	srv.adaugare("a", "b", "a", 1);
	srv.adaugare("a", "a", "a", 1);
	srv.adaugare("a", "a", "a", 1);
	srv.adaugare("a", "c", "a", 1);

	auto rez = srv.filtrare_destinatie("a");
	assert(rez.size() == 3);
}

void srv_sortare_test() {
	ServiceOferta srv;
	srv.adaugare("b", "b" ,"a", 2);
	srv.adaugare("a", "a", "a", 1);
	srv.adaugare("d", "d", "b", 4);
	srv.adaugare("c", "c", "b", 3);  // Sortare Destinatie
	auto vec = srv.sortare([](const Oferta& a, const Oferta& b) {return a.get_destinatie() < b.get_destinatie(); });
	int i = 1;
	for (const auto& el : vec) {
		assert(i == el.get_pret());
		i++;
	}
		
	vec = srv.sortare([](const Oferta& a, const Oferta& b) {return a.get_denumire() < b.get_denumire(); });
	i = 1;
	for (const auto& el : vec) {
		assert(i == el.get_pret());  // Verificam ordinea corecta.
		i++;
	}

	vec = srv.sortare([](const Oferta& a, const Oferta& b) {
		if (a.get_tip() == b.get_tip())
			return a.get_pret() < b.get_pret();
		return a.get_tip() < b.get_tip();
	});

	i = 1;
	for (const auto& el : vec) {
		assert(i == el.get_pret());
		i++;
	}

}

void Testing::run_all_service_tests(){
	srv_adaugare_test();
	srv_stergere_test();
	srv_modificare_test();
	srv_cautare_test();
	srv_filtrare_pret_test();
	srv_filtrare_destinatie_test();
	srv_sortare_test();
}

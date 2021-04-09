#include "service_tests.h"
#include "../service/ServiceOferta.h"
#include <cassert>
#include <iostream>
#include <fstream>

void srv_adaugare_test() {
	ServiceOferta srv;
	char index = 'a';
	for (int i = 0; i < 10; i++) {
		srv.adaugare(string{ index }, "a", "a", 10);
		index++;
	}
	auto de_test = srv.get_all(); 
	assert(de_test.size() == 10);
}

void srv_stergere_test() {
	ServiceOferta srv;
	char index = 'a';
	for (int i = 0; i < 20; i++) {
		srv.adaugare(string{index}, "a", "a", 100);
		index++;
	}
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
	char index = 'a';
	for (int i = 0; i < 10; i++) {
		srv.adaugare(string{ index }, "a", "a", 100);
		index++;
	}

	try {
		srv.modificare(10, "b", "b", "b", 1);  // Elementul nu exista
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	// Modificam un element din lista.
	srv.modificare(5, "z", "b", "b", 1);
	assert(srv.cautare(5).get_pret() == 1);
}

void srv_cautare_test() {
	ServiceOferta srv; 
	char index = 'a';
	for (int i = 0; i < 10; i++) {
		srv.adaugare(string{ index }, "a", "a", 100);
		index++;
	}

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
	char index = 'a';
	for (int i = 0; i < 100; i++) {
		srv.adaugare(string{ index }, "a", "a", i);
		index++;
	}
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
	srv.adaugare("b", "b", "a", 1);
	srv.adaugare("c", "a", "a", 1);
	srv.adaugare("d", "a", "a", 1);
	srv.adaugare("e", "c", "a", 1);

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

void srv_test_cos() {
	ServiceOferta srv;
	srv.adaugare("a", "a", "a", 1);
	srv.adaugare("b", "a", "a", 2);
	srv.adaugare("c", "a", "a", 3);
	srv.adaugare("d", "a", "a", 4);
	srv.adauga_cos("a");
	srv.adauga_cos("b");
	
	try {
		srv.adauga_cos("C");  // Adauga in cos un element care nu exista.
	}
	catch (const std::exception& e) {
		assert(string{e.what()} == "Element not found");
	}
	assert(srv.dimensiune_cos() == 2);

	// Nu putem adauga acelasi element de mai multe ori.
	srv.adauga_cos("a");
	srv.adauga_cos("a");
	srv.adauga_cos("a");
	srv.adauga_cos("a");
	assert(srv.dimensiune_cos() == 2);

	srv.adauga_cos("c");
	srv.adauga_cos("d");
	try {
		srv.sterge_din_cos("D");
	}
	catch (const std::exception& e) {
		assert(string{ e.what() } == "Element not found");
	}

	srv.sterge_din_cos("d");
	assert(srv.dimensiune_cos() == 3);

	const auto& vec = srv.vector_cos();
	assert(vec.size() == 3);

	srv.golire_cos();
	assert(srv.dimensiune_cos() == 0);
}

void test_export_html() {
	ServiceOferta srv;
	srv.adaugare("a", "a", "a", 1);
	srv.adaugare("b", "a", "a", 2);
	srv.adaugare("c", "a", "a", 3);
	srv.adaugare("d", "a", "a", 4);

	srv.adauga_cos("a");
	srv.adauga_cos("b");
	srv.adauga_cos("c");
	srv.adauga_cos("d");

	srv.export_html_cos("testfisier");
	srv.export_html_cos_fancy("testfisierfancy");
	std::ifstream de_test;
	de_test.open("testfisier.html");
	if (de_test) {
		assert(true);
		de_test.close();
		std::remove("testfisier.html");
	}
	else {
		assert(false);
	}

	std::ifstream de_test_fancy;
	de_test_fancy.open("testfisierfancy.html");
	if (de_test_fancy) {
		de_test_fancy.close();
		assert(true);
		std::remove("testfisierfancy.html");
	}
	else {
		assert(false);
	}

	try {
		srv.export_html_cos("/<>");
		assert(false);
	}
	catch (...){
		assert(true);
	}

	try {
		srv.export_html_cos_fancy("<>");
		assert(false);
	}
	catch (...) {
		assert(true);
	}

}

void test_adaugare_random() {
	ServiceOferta srv;
	srv.adaugare("a", "a", "a", 1);
	srv.adaugare("b", "a", "a", 2);
	srv.adaugare("c", "a", "a", 3);
	srv.adaugare("d", "a", "a", 4);

	srv.adauga_random_cos(3);
	assert(srv.dimensiune_cos() == 3);

	try {
		srv.adauga_random_cos(-1);
	}
	catch (...) {
		assert(true);
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
	srv_test_cos();
	test_export_html();
	test_adaugare_random();
}

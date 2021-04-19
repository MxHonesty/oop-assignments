#pragma once
#include "Repository.h"
#include "errors/RepoError.h"
#include <unordered_map>
#include <vector>
using std::vector;

class RepoException : public Repository {
private:
	std::unordered_map<int, Oferta> dict;
	float prob;

	/** Trigger la exceptie dupa probabilitate. */
	void trigger() const;

public:
	/** Default constructor */
	RepoException() noexcept : dict{}, prob{ 0 } {};

	/** Constructor cu probabilitate. */
	RepoException(const float probabilitate) : prob{ probabilitate } {};

	/** Adauga o oferta in repository.
	* @param de_adaugat - Oferta pe care dorim sa o adaugam.
	*/
	void add(const Oferta& de_adaugat) override;

	/** Elimina elementul cu id-ul dat.
	* @param id - id elementului pe care dorim sa il eliminam.
	*/
	void remove(const int id) override;

	/** Updateaza elementul cu id dat la noua oferta.
	* Elementului din lista ii sunt inlocuite atribuitele cu cele noi.
	* @param id - id-ul elementului cautat
	* @param new_oferta - noua oferta.
	*/
	void update(const int id, const Oferta& new_oferta) override;

	/** Determina daca elementul cu id dat este in lista.
	* @param id - id-ul elementului cautat.
	* @return true daca elementul exista in lista, false altfel.
	*/
	bool search(const int id) const override;

	/** Determina daca exista un element cu denumirea data.
	* @param denumire - string
	*/
	bool search_denumire(const std::string& denumire) const override;

	/** Returneaza referinta constanta la elementul cu denumirea data.
	* @param denumire - string
	*/
	const Oferta& search_get_denumire(const std::string& denumire) const override;

	/** Returneaza o referinta const la elementul cu id dat
	* arunca o exceptie daca nu exista elementul cu acest id.
	*/
	const Oferta& search_element(const int id) const override;

	/** Returneaza un vector de copii ale elementelor.
	* @return un vector de Oferta care contine copii
	* ale elementelor din repo.
	*/
	vector<Oferta> get_all() const override;

	/** Returneaza referinta la vector*/
	const vector<Oferta> afisare() const noexcept override;

	/** Elimina toate elementele din repository. */
	void remove_all() noexcept override;

	/** Returneaza numarul de elemente din repo.
	* @return int numarul de elemente
	*/
	unsigned dim() noexcept override;


	/** Get max index out of elements */
	int get_max_index() const noexcept override;
};


#pragma once 

#include <stdexcept>
#include <functional>

#include <iostream>

template <typename T>
class IteratorSVector;  // Forward declaration IteratorS

template <typename T>
class VectorDinamic {
private:
	T* elems;
	int capacitate;
	int lungime;  // Urmatoarea pozitie pe care se poate introduce un element.

	/** Redimensioneaza vectorul daca este nevoie. */
	void ensure_capacity();

public:
	// Constructor implicit
	VectorDinamic() noexcept;
	
	/** Copy constructor */
	VectorDinamic(const VectorDinamic<T>& de_copiat);

	/** Move constructor */ 
	VectorDinamic(VectorDinamic<T>&& de_copiat);

	/** Copy assignment */
	VectorDinamic<T>& operator=(const VectorDinamic<T>& de_copiat);

	/** Move assignment */
	VectorDinamic<T>& operator=(VectorDinamic<T>&& de_copiat);

	/** Destructor */
	~VectorDinamic();

	/** Metoda adauga o copie a elementului dat in vector.
	* @param de_adaugat - elementul pe care dorim sa il adaugam.
	*/
	void add(const T& de_adaugat);

	/** Elimina elementul de pe pozitia data.
	* @param pozitie - pozitia elementului de eliminat.
	*/
	void remove(const int pozitie) noexcept;

	/** Oferta elementul de pe pozitia data.
	* @param pozitia din vector.
	* @return Referinta la elementul respectiv
	*/
	T& get(const int pozitie) const noexcept;

	/** Returneaza dimensiunea vectorului.
	* @return Numarul de elemente stocate in vector.
	*/
	int size() const noexcept;

	/** Returneaza IteratorS incpand de la primul element */
	IteratorSVector<T> begin() const;

	/** Returneaza IteratorS pe prima pozitie dupa ultimul element */
	IteratorSVector<T> end() const;

	/** Elimina toate elementele din vector. */
	void clear();

	/** Functia care sorteaza vectorul dupa un criteriu. 
	* @param criteriu - functia care determina daca un element ar trebui
	* sa fie inalntea celuilalt. Returneaza true daca primul element trebuie sa fie
	* inaintea celui de-al doilea in lista sortata. 
	*/
	void sort(std::function<bool(const T& a, const T& b)> criteriu);
};

template <typename T>
class IteratorSVector {
private:
	int index;
	const VectorDinamic<T>& container;  // Referinta la container parcurs.

public:
	// Constructor implicit
	IteratorSVector(const VectorDinamic<T>& m) : container{ m } {
		this->index = 0;
	};

	IteratorSVector(const VectorDinamic<T>& m, int pos) : container{ m }, index{ pos } {
	};


	/** Determina daca pozitia curenta din IteratorS este valida. 
	* @return true daca pozitia curenta este valida, false altfel.
	*/
	bool valid() const;

	/** Incrementeaza pozitia IteratorSului vectorului. */
	void urmator();

	/** Returneaza elementul curent aratat de catre IteratorS.
	* @return Referinta la un element din vector.
	*/
	T& element() const;

	/** Operator dereferentiere, returneaza referinta la elemntul curent. */
	T& operator*() const;

	/** Incrementeaza pozitia si returneaza IteratorS. */
	IteratorSVector<T>& operator++();

	/** Operator de egalitate intre IteratorSi.  */
	bool operator==(const IteratorSVector<T>& ot) const;

	/** Operatori de diferenta intre IteratorSi.  */
	bool operator!=(const IteratorSVector<T>& ot) const;
	
};

template<typename T>
inline void VectorDinamic<T>::sort(std::function<bool(const T& a, const T& b)> criteriu) {
	for (int i = 0; i < size() - 1; i++) {
		for(int j = i + 1; j < size(); j++)
			if (criteriu(this->get(j), this->get(i))) {
				//std::cout << "\nCOPIE 1!\n";
				std::swap(this->get(j), this->get(i));
				//std::cout << "\nCOPIE 2!\n";
			}
	}
}

template<typename T>
inline T& IteratorSVector<T>::operator*() const {
	return element();
}

template<typename T>
inline IteratorSVector<T>& IteratorSVector<T>::operator++() {
	urmator();
	return *this;
}

template<typename T>
inline bool IteratorSVector<T>::operator==(const IteratorSVector<T>& ot) const {
	return this->index == ot.index;
}

template<typename T>
inline bool IteratorSVector<T>::operator!=(const IteratorSVector<T>& ot) const {
	return this->index != ot.index;
}

template<typename T>
inline IteratorSVector<T> VectorDinamic<T>::begin() const {
	return IteratorSVector<T>{*this};
}

template<typename T>
inline IteratorSVector<T> VectorDinamic<T>::end() const {
	return IteratorSVector<T>{ *this, this->lungime };
}

template<typename T>
inline void VectorDinamic<T>::ensure_capacity() {
	if (this->lungime >= this->capacitate) {
		this->capacitate *= 2;  // dublare capacitate
		auto new_elems = new T[capacitate];
		for (int i = 0; i < this->lungime; i++)
			new_elems[i] = elems[i];  // Copiem toate elementele in noul array.
		delete[] elems;
		elems = new_elems;
	}
}

template<typename T>
inline void VectorDinamic<T>::clear() {
	int de_sters = size();
	for (int i = 0; i < de_sters; i++) {
		remove(0);
	}
}

template<typename T>
inline VectorDinamic<T>::VectorDinamic() noexcept {
	capacitate = 10;
	lungime = 0;
	elems = new T[capacitate];  // Capacitate initiala 10
}

template<typename T>
inline int VectorDinamic<T>::size() const noexcept {
	return this->lungime;
}

template<typename T>
inline VectorDinamic<T>::VectorDinamic(const VectorDinamic& de_copiat) {
	this->elems = new T[de_copiat.capacitate];
	this->lungime = de_copiat.lungime;
	this->capacitate = de_copiat.capacitate;


	for (int i = 0; i < de_copiat.lungime; i++)
		this->elems[i] = de_copiat.get(i);  // Adauga o copie la fiecare element.

}

template<typename T>
inline VectorDinamic<T>::~VectorDinamic() {
	delete[] this->elems;
}

template<typename T>
inline VectorDinamic<T>::VectorDinamic(VectorDinamic<T>&& de_copiat) {
	std::cout << "MOVE CONSTRUCTOR\n";
	this->elems = de_copiat.elems;
	this->capacitate = de_copiat.capacitate;
	this->lungime = de_copiat.lungime;

	de_copiat.elems = nullptr;
	de_copiat.capacitate = 0;
	de_copiat.lungime = 0;
}

template<typename T>
inline VectorDinamic<T>& VectorDinamic<T>::operator=(const VectorDinamic& de_copiat) {
	if (&de_copiat != this) {  // self assign guard
		delete[] this->elems;
		this->elems = new T[de_copiat.capacitate];
		this->lungime = de_copiat.lungime;
		this->capacitate = de_copiat.capacitate;
		for (int i = 0; i < de_copiat.lungime; i++) {  // Copiere fiecare element.
			this->elems[i] = de_copiat.get(i);
		}
	}

	return *this;
}

template<typename T>
inline VectorDinamic<T>& VectorDinamic<T>::operator=(VectorDinamic<T>&& de_copiat) {
	std::cout << "MOVE ASSIGNMENT\n";
	delete[] this->elems;  // Stergem vector vechi.
	this->elems = de_copiat.elems;  // Noile elemente
	this->capacitate = de_copiat.capacitate;
	this->lungime = de_copiat.lungime;

	de_copiat.elems = nullptr;
	de_copiat.capacitate = 0;
	de_copiat.lungime = 0;

	return *this;
}

template<typename T>
inline void VectorDinamic<T>::add(const T& de_adaugat) {
	this->ensure_capacity();
	this->elems[this->lungime] = de_adaugat;
	this->lungime++;
}

template<typename T>
inline void VectorDinamic<T>::remove(const int pozitie) noexcept {
	for (int i = pozitie; i < this->lungime - 1; i++) {
		this->elems[i] = this->elems[i+1];
	}
	this->lungime--;
}

template<typename T>
inline T& VectorDinamic<T>::get(const int pozitie) const noexcept {
	return this->elems[pozitie];
}


template<typename T>
inline bool IteratorSVector<T>::valid() const {
	if (this->index >= 0 and this->index < this->container.size())
		return true;
	return false;
}

template<typename T>
inline T& IteratorSVector<T>::element() const {
	if(this->valid())
		return this->container.get(this->index);
	throw std::out_of_range{ "Index out of range" };
}

template<typename T>
inline void IteratorSVector<T>::urmator() {
	this->index++;
}

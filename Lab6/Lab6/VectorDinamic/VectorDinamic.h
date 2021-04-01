#pragma once 

template <typename T>
class IteratorVector;  // Forward declaration Iterator

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
	VectorDinamic();
	
	/** Copy constructor */
	VectorDinamic(const VectorDinamic<T>& de_copiat);

	VectorDinamic& operator=(const VectorDinamic& de_copiat);

	/** Destructor */
	~VectorDinamic();

	/** Metoda adauga o copie a elementului dat in vector.
	* @param de_adaugat - elementul pe care dorim sa il adaugam.
	*/
	void add(const T& de_adaugat);

	/** Elimina elementul de pe pozitia data.
	* @param pozitie - pozitia elementului de eliminat.
	*/
	void remove(const int pozitie);

	/** Oferta elementul de pe pozitia data.
	* @param pozitia din vector.
	* @return Referinta la elementul respectiv
	*/
	T& get(const int pozitie);

	/** Returneaza dimensiunea vectorului.
	* @return Numarul de elemente stocate in vector.
	*/
	int dim() const noexcept;
};

template <typename T>
class IteratorVector {
private:
	int index;
	VectorDinamic<T>& container;  // Referinta la container parcurs.

public:
	// Constructor implicit
	IteratorVector();

	/** Determina daca pozitia curenta din iterator este valida. 
	* @return true daca pozitia curenta este valida, false altfel.
	*/
	bool valid();

	/** Incrementeaza pozitia iteratorului vectorului. */
	void urmator();

	/** Returneaza elementul curent aratat de catre iterator.
	* @return Referinta la un element din vector.
	*/
	T& element();

};

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
inline VectorDinamic<T>::VectorDinamic() {
	int capacitate = 10;
	int lungime = 0;
	elems = new T[capacitate];  // Capacitate initiala 10
}

template<typename T>
inline int VectorDinamic<T>::dim() const noexcept{
	return this->lungime;
}

template<typename T>
inline VectorDinamic<T>::VectorDinamic(const VectorDinamic& de_copiat) {
	VectorDinamic<T> nou;
	for (int i = 0; i < de_copiat.lungime; i++)
		nou.add(de_copiat.get(i));  // Adauga o copie la fiecare element.

	return nou;
}

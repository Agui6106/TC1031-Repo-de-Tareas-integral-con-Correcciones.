/* =========================================== //
    Jose Alberto Aguilar Sanchez - A01735612
    Hashes
// =========================================== */

#ifndef QUADRATIC_H
#define QUADRATIC_H

#include <string>
#include <sstream>

// -- Clase Principal --//
template <class Key, class Value>
class Quadratic {
	private:
		// Atributos 
		unsigned int (*func)(const Key);
		unsigned int size;
		unsigned int count;

		// Apuntadores
		Key *keys;
		Key initialValue;
		Value *values;

		// Indice del objeto al q apuntamos
		long indexOf(const Key) const;

	public:
		//Constructor
		Quadratic(unsigned int, Key, unsigned int (*f) (const Key));
		//Destructor
		~Quadratic();

		//Métodos
		void clear();

		bool full() const;
		bool put(Key, Value);
		Value get(const Key);

		// Convetimos a string
		std::string toString() const;
};

// Constructor 
template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f) (const Key)) {
	size = sze;
	keys = new Key[size];

	if (keys == 0) {
		return;
	}

	initialValue = init;
	for (unsigned int i = 0; i < size; i++) {
		keys[i] = init;
	}
	values = new Value[size];

	if (values == 0) {
		return;
	}

	for (int i = 0; i  < sze; i++){
        values[i] = 0;
    }

	func = f;
	count = 0;
}

// Destructor
template <class Key, class Value>
Quadratic<Key, Value>::~Quadratic() {
	// Resteamos todo  a 0
	delete[] keys;
	keys = nullptr;
	delete[] values;
	values = nullptr;
	size = 0;
	func = nullptr;
	count = 0;
}

// Llena?
template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
	return (count > size);
}

// Obtenemos el indice del objeto
template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
	unsigned int i, start;

	start = i = func(k) % size;
	do {
		if (keys[i] == k) {
			return i;
		}
		i = (i + 1) % size;
	} while (start != i);
	return -1;
}

// Agregamos un valor
template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key k, Value v) {
	unsigned int i, start, c = 1;
	long pos;

	if (full()) {
		return false;
	}

	pos = indexOf(k);
	if (pos != -1) {
		values[pos] = v;
		return true;
	}

	start = i = func(k) % size;
	do {
		if (keys[i] == initialValue) {
			keys[i] = k;
			values[i] = v;
			count++;
			return true;
		}
        i = (start + c * c) % size;
        c++;
	} while (start != i);
	return false;
}

// Obtenemos
template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k) {
	long pos = indexOf(k);

	if (pos != -1) {
		return values[pos];
	}
	return -1;
}

// Limpiamos, mas no borrramos
template <class Key, class Value>
void Quadratic<Key, Value>::clear() {
	count = 0;
	for (unsigned int i = 0; i < size; i++) {
		keys[i] = initialValue;
	}
}

// Convertimos a string
template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
	std::stringstream aux;

	for (unsigned int i = 0; i < size; i++) {
		if(keys[i] != initialValue)
			aux << "(" << i << " " << keys[i] << " : " << values[i] << ") ";
	}

	return aux.str();
}

#endif
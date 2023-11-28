/* =========================================== //
    Jose Alberto Aguilar Sanchez - A01735612
    Listas doblemente linkeadas
// =========================================== */

#ifndef DLIST_H_
#define DLIST_H_

#include <sstream>
#include <string>

// Encabezados clase amiga
template <class T> class DList;

// -- CLASE AUXILIAR DOBLE LINK -- //
template <class T>
class DLink {
private:
	// Constructor // 
	DLink(T);

	// Metodos // 
	T	    value;
	DLink<T> *previous;
	DLink<T> *next;

	// Clases compadre
	friend class DList<T>;
};

// CONSTRUCTOR //
template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}


// -- CLASE PRINCIPAL DOBLE LISTA -- //
template <class T>
class DList {
	private:
		// Atributos de la clase 
		DLink<T> *head;
		DLink<T> *tail;
		int 	 size;

	public:
		// Construoctores //
		DList();
		~DList(); // Destructor 
		void clear(); // Metodo auxiliar para el destrcuotr

		// Metodos //
		void insertion(T);
        int search(T);
        void update(int, T);
        T deleteAt(int);
		// Metodos aux para compatibilidad con el main //
        std::string toString() const;
		std::string toStringForward() const;
		std::string toStringBackward() const;
};

// Constructro por omision //
template <class T>
DList<T>::DList() : head(0), tail(0) {}

// -- Desctructor -- //
template <class T>
DList<T>::~DList() {clear();}

// Metodo auxiliar
template <class T>
void DList<T>::clear() {
	DLink<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	size = 0;
}

// -- METODOS -- //

// Insertar
template <class T>
void DList<T>::insertion(T val) {
//  Creamos un objeto nuevo y un apuntador hacia el
    DLink<T>* newVal = new DLink<T>(val);

    // Esta vacia?
    if (head == nullptr) {
        head = newVal;
		tail = newVal;

    } else { // Sino ve al final y agrega
		tail->next = newVal; // Establece next apuntando al siguiente de NewLink
		newVal->previous = tail; // Establece previous apuntando al elemnto anteriro de la lista
		tail = newVal; // La cola apunta a newLink (prev)
    }
}

// Buscar
template <class T>
int DList<T>::search(T val){
	// Variables
	DLink<T> *p = head;
	int i = 0; 
	
	// Recorremos la lista, mientras verdadero...
	while (p) {
		if (p->value == val) { //... Hasta encontrar el valor
			return i;// regresa el iterador contador 
		}
		p = p->next;
		i++; 
	}
    // Sino regresa -1
	return -1;
}

// Actualizar
template <class T>
void DList<T>::update(int index, T data) {
    // Creamos un puntero auxiliar para recorrer la lista
    DLink<T> *current = head;

    // Recorremos hasta llegar al índice deseado
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    // Actualizamos el valor en el índice dado
    current->value = data;
}

// Borar en...
template <class T>
T DList<T>::deleteAt(int index) {
	int pos;
	T val;
	DLink<T> *p;

	// Si el index es el primero
	if (index == 0) {
		p = head;
		val = p->value;

		if (head == tail) {
			head = 0;
			tail = 0;
		} else {
			head = p->next;
			p->next->previous = 0;
		}
		delete p;
		size--;

		return val;
	}

	// Variables auxiliares, para no modificar origianles
	p = head; // Apuntador
	pos = 0; // Iterador para saber donde estamos

	// Recorremos hasta encontrar el index q buscamos 
	while (pos != index) {
		p = p->next;
		pos++;
	}

	val = p->value; // Obtenemso el valor del objeto a borrar
	p->previous->next = p->next; // Asi como sus direcciones

	// Sino es el ultimo elemento de la lista modifica los apuntadores
	if (p->next != 0) {
		p->next->previous = p->previous;
	}

	// Reducimos el tamano y borramos el objeto 
	size--;
	delete p;

	return val;
}

// -- METODOS AUX PARA COMPATIBILDIAD -- //

// Transforma la lista a string
template <class T>
std::string DList<T>::toString() const {
    std::stringstream aux;
    DLink<T> *p;

    p = head;
    aux << "[";
    while (p != nullptr) {
        aux << p->value;
        if (p->next != nullptr) {
            aux << ", ";
        }
        p = p->next;
    }
    aux << "]";
    return aux.str();
}

// Transforma la lista a un string derecha a izquierda
template <class T>
std::string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

// Transformar la lista a un string de izquierda a derecha
template <class T>
std::string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}

#endif
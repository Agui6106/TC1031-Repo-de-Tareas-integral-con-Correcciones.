/* =========================================== //
    Jose Alberto Aguilar Sanchez - A01735612
    Listas linkeadas
// =========================================== */

#ifndef LIST_H_
#define LIST_H_

#include <sstream>
#include <string>

// Encabezado clase lista
template <class T> class List;

// -- Clase auxiliar Link o nodo -- //
template <class T>
class Link {
// Lo incluimos en privado, puesto que no queremos que el usario acceda a estos objetos
private:
	// Constructor 
	Link(T);

	// Operadores 
	T	    value; // Valor del objeto Link T
	Link<T> *next; // Apuntador al obejto link T 

	// Clase compadre Lista
	friend class List<T>; // Lista entra a todo lo privado de LINK
};

// CONSTRUCOTRES // 
// Default o vacio
template <class T>     
Link<T>::Link(T val) : value(val), next(0) {}

// -- Clase Principal Lista -- //
template <class T>
class List{
	// Atributos privados de lista
    private:
		// Creamos el apuntador de la lista 
		Link<T> *head;

    public:
		// -- Constructor y Destructor // 
        List(); // Vacio o por omision


        // Metodos 
        void insertion(T);
        int search(T);
        void update(int, T);
        void deleteAt(int);
        std::string toString() const;
};

// CONSTRUCOTR //
template <class T>
List<T>::List() : head(nullptr) {}

// METODOS //

template <class T>
void List<T>::insertion(T val) {
    // Creamos en el git un nuevo objeto tipo T para anadir a la lista 
    Link<T>* newVal = new Link<T>(val);

    // Si la lista esta vacia establece el valor como nuevo como header
    if (head == nullptr) {
        head = newVal;
    } else { // Sino ve al final y agregalo
        Link<T>* now  = head; // Creamos un apuntador auxiliar
        while (now ->next != nullptr) { // Recorremos hasta llegar al final  
            now = now ->next;
        }
        // Movemos el apuntador a la siguiente posicioon
        now->next = newVal;
    }
}

template <class T>
int List<T>::search(T val) {
    // creamos apuntador auxiliar apra operar
	Link<T> *current = head;
    // Iterador para recorrer la lista
	int i = 0;

    // Recorremos la lista, mientras verdadero...
	while (current) {
		if (current->value == val) { //... Hasta encontrar el valor
			return i;// regresa el iterador contador 
		}
        // Mueve el apuntador al siguiente elemento
		current = current->next;
		i++; // Suma la posicion
	}
    // Sino regresa -1
	return -1;

}

// Cambiar el valor de un index dado
template <class T>
void List<T>::update(int index, T data) {
    // Creamos variables auxiliares para recorrer los datos
    Link<T> *current = head;
    int currentIndex = 0;

    // Recorremos hatsa encontrar el index que nos dieron
    while (current) {
        // Si hayamos el index, cambia por el nuevo valor
        if (currentIndex == index) {
            current->value = data;
            return;
        }
        current = current->next;
        currentIndex++;
    }
}

template <class T>
void List<T>::deleteAt(int index) {
    // Si el index es 0, borra el header
    if (index == 0) {
        // Pasa el heaader al apuntador siguinete
        Link<T> *temp = head;
        head = head->next;
        delete temp;

    } else {
        // Variables auxiliares apra no modificar origanles
        Link<T> *current = head;
        int currentIndex = 0;
        
        // Reocrremos la lista hasta hayar el index dado
        while (current) {
            if (currentIndex == index - 1) {
                // Cambiamos el apuntador para no perder la lista 
                Link<T> *temp = current->next;
                current->next = temp->next;
                // Borramos lop que habia ahi
                delete temp;
               }
            current = current->next;
            currentIndex++;
        }
    }
}

template <class T>
std::string List<T>::toString() const {
    std::stringstream aux;
    Link<T> *p;

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

#endif

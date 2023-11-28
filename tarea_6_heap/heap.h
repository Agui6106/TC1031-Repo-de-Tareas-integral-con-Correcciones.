/* =========================================== //
    Jose Alberto Aguilar Sanchez - A01735612
    Heap
// =========================================== */

#ifndef HEAP_H
#define HEAP_H

// -- CLASE HEAP -- //
template <class T>
class Heap {
    private:
        // Propiedades del Heap //
	    T *data; // Dato
        unsigned int Size; //Longitud
        unsigned int count; // Contador

        // Metodos auxilaires //
        unsigned int parent(unsigned int) const;
        unsigned int left(unsigned int) const;
        unsigned int right(unsigned int) const;
        void heapify(unsigned int);
        void swap(unsigned int, unsigned int);

    public:
        //Constructor
        Heap(unsigned int) ;
        //Destructor
        ~Heap();

        // Metodos Principales //
        bool empty() const; // Vacio?
        bool full() const; // Lleno?
        void clear(); // Limpiamos
        
        // Metdos especificos 
        void push(T);
        void pop();
        T top() const;
        unsigned int size() const;
        
        // Metodo para convertir en string
        std::string toString() const;

};

//Constructor 
template <class T>
Heap<T>::Heap(unsigned int sze)  {
    // Creamos en el git
    Size = sze;
    data = new T[Size];
    count = 0;
}

//Descrutor 
template <class T>
Heap<T>::~Heap() {
    // Borramos del git
    delete [] data;
    data = 0;
    Size = 0;
    count = 0;
}

// -- METODOS -- //

// Vacio?
template <class T>
bool Heap<T>::empty() const {
    return (count == 0);
}

// Lleno?
template <class T>
bool Heap<T>::full() const {
    return (count == Size);
}

// Limpiamos lo que haya en el heap
template <class T>
void Heap<T>::clear() {
    count = 0;
}

// Obtenemos el padre de un nodo
template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
    return ((pos - 1) / 2);
}

// Obtenemos el hijo izquierdo 
template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
    return ((2 * pos) + 1);
}

//M Obtenemos el hijo derecho
template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
    return ((2 * pos) + 2);
}

// Intercambiamops 2 dos nodos
template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
    T aux = data[i];
    data[i] = data[j];
    data[j] = aux;
}

// Metodo heapify para ordenar el heap
template <class T>
void Heap<T>::heapify(unsigned int pos) {
    unsigned int le = left(pos);
    unsigned int ri = right(pos);
    unsigned int min = pos;

    if (le <= count && data[le] < data[min]) {
        min = le;
    }
    if (ri <= count && data[ri] < data[min]) {
        min = ri;
    }
    if (min != pos) {
        swap(pos, min);
        heapify(min);
    }
}

// "Empujamos" Para agregar iun nuevo valor
template <class T>
void Heap<T>::push(T val)  {
	unsigned int pos;

	pos = count;
	count++;
	while (pos > 0 && val < data[parent(pos)]) {
		data[pos] = data[parent(pos)];
		pos = parent(pos);
	}
	data[pos] = val;
}

// Explortamos un nodo para eliminarlo >:) 
template <class T>
void Heap<T>::pop()  {
    T aux;

    aux = data[0];
    data[0] = data[--count]; // Decrementamos el contador
    heapify(0); // Llamamos a heapify
}

// Obtenemos el nodo campeon (El que esta en la cima)
template <class T>
T Heap<T>::top() const {
    return data[0];
}

// Obtenemos la longitud del heap
template <class T>
unsigned int Heap<T>::size() const {
    return count;
}

//Metodo para compatibilidad con el main
template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;

	aux << "[";	
    
    for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} 
        aux << data[i];
	} 
    
    aux << "]";
	return aux.str();
}

#endif
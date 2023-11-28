/*
Jose Alberto Aguilar Sanchez - A01735612

Algortimos de ordenamiento

Sorts.h
*/

#ifndef SORTS_H_
#define SORTS_H_

// Incluimos vector
#include <vector>

// Haceos una plantilla para recibir todo tipo de datos dentro de la clase sorts
template <class T> // Como tenemos en el main class T, utilizamso el mismo para compatibilidad
class Sorts {
private:
// FUncion Auxiliar recursiva 
    int bs_aux(std::vector<T> &v, int min, int max, int val);
public:
    // Declaramos las funciones de la plantilla
    void ordenaSeleccion(std::vector<T> &v);
    void ordenaBurbuja(std::vector<T> &v);
    void ordenaMerge(std::vector<T> &v);
    int busqSecuencial(const std::vector<T> &v, const T &target);
    // Declaramos un objeto comodin que acepte cuaqlueir tipo de valor
    T busqBinaria(const std::vector<T> &v, int val);
    
};

// -- MAIN FUNCTIONS -- //

// -- Funcion ordena sleccion -- //
template <class T>
void Sorts<T>::ordenaSeleccion(std::vector<T> &v) {
    // Ordene en forma ascendente los datos con el método de Selccion
    // Acepta un vector N
    // No output

    /*
    Recuerdese que este alogrtimo va comparando de uno en uno hasta encontra un numero
    menor y lo mantiene hasta que recorra el array y lo mueva a la posicion
    */
    
    // N = tamano del array
    int n = v.size();

    // Declaramso un for que recorra todo el array
    for (int i = 0; i < n - 1; i++) {
        // Nuestro min es el index mas chikito
        int min = i; 

        //
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[min]) {
                min = j;
            }
        }
        if (min != i) {
            //Voltea los valores
            std::swap(v[i], v[min]);
        }
    }
}

// Funcion ordena burbuja
template <class T>
void Sorts<T>::ordenaBurbuja(std::vector<T> &v) {
    // Ordene en forma ascendentelos datos con el método de Burbuja
    // Recibimso un vector con N distancia

    // Creamos nuestro For para recocrer el array
    for (int j = 0; j < v.size() - 1; ++j) {
        // Ciclamos la comparacion de los elemnetos
        for (int i = 0; i < v.size() - j - 1; ++i) {
            // EL anterior es mayor que el actual?
            if (v[i] > v[i + 1]) {
                // Realizamos el swap. Si si
                std::swap(v[i], v[i+1]);
            }
        }
      }

}
    

// -- Funcion Merge -- //
template <class T>
void Sorts<T>::ordenaMerge(std::vector<T> &v) {
    /*
    Recuerdese que este algortimo utliza la logica de divbide y venceras 
    En etse caso divideimos el algortimo en partes eseciales.

    1. Dividir el array original en 2
    2. Sorteqar los arrays chikitos y mezclarlos en uno nuevo
    
    */

   int n = v.size();
   int mid = n / 2;

    // Caso base: si el vector tiene 0 o 1 elemento, ya está ordenado
    if (n <= 1) {
        return;
    }
    
    // Creamos dos vectores auxiliares para dividir el vector original
    std::vector<T> left(v.begin(), v.begin() + mid);
    std::vector<T> right(v.begin() + mid, v.end());

    // Llamadas recursivas para ordenar las dos mitades
    ordenaMerge(left);
    ordenaMerge(right);

    int i = 0; // Índice para recorrer el vector 'left'
    int j = 0; // Índice para recorrer el vector 'right'
    int k = 0; // Índice para recorrer el vector original 'v'

    // Combinamos las dos mitades ordenadas en el vector original 'v'
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            v[k] = left[i];
            i++;
        } else {
            v[k] = right[j];
            j++;
        }
        k++;
    }

    // Copiamos los elementos restantes de 'left', en el vector final
    while (i < left.size()) {
        v[k] = left[i];
        i++;
        k++;
    }

    // Copiamos los elementos restantes de 'right', en el vector final
    while (j < right.size()) {
        v[k] = right[j];
        j++;
        k++;
    }
} // -- FIN DE LA FUNCION MERGE -- //

// -- Funcion busqueda secuencial -- //
template <class T>
int Sorts<T>::busqSecuencial(const std::vector<T> &v, const T &val){
    // Creamso la vraible high 
    int high = v.size() - 1;

	for(int i = 0; i <= high; i++) {
		if (val == v[i]) {
            return i;
        } 
	}
	return -1;

}    

// -- Funcion Recursiva busqueda Binaria Auxiliar -- //
template <class T>
int Sorts<T>::bs_aux(std::vector<T> &v, int min, int max, int val) {
    // Creamos la variable de la mitad del arreglo
	int mid;

    // Comparamos si el minimo es el menor (Caso Base)
	if (min <= max) {
        // Si si, Obtenemos la mitad
		mid = (min + max) / 2;

        // Si el valor es esta en al mitad, regresamos la mitad
		if (val == v[mid]) {
			return mid;
        
        // Sino Y si el valor es menor que mid, recorre la parte baja del array
		} else if (val < v[mid]) {
			return bs_aux(v, min, mid - 1, val);

        // Sino Y si el valor es Mayor que mid, recorre la parte alta del array
		} else if (val > v[mid]) {
			return bs_aux(v, mid + 1, max, val);
		}
	}

    // Si el valro ingeesado es mayor a los que hay en el array, Regresa el mas alto
	if (v[min]==val) {return min;}
	else return -1;
}

// -- Funcion busqueda binaria Recursiva -- //
template <class T>
T Sorts<T>::busqBinaria(const std::vector<T> &source, int valor) {
	std::vector<T> v(source);
	return bs_aux(v, 0, v.size() - 1, valor);
}




#endif
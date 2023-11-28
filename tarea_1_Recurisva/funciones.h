/*
Jose Alberto Aguilar Sanchez - A01735612

Funciones Iterativas y Recursivas
*/

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>

// Creamos la clase Funciones para compatibilidad con el main
class Funciones{
    public: // Dentro del public para evitar complicaciones

        // Funcion Suma iterativa
        // Utilizamos la palbra base unsigned para solo recibir ints positivos
        unsigned int sumaIterativa(int n){
            int cont = 0;
            for(int i = 1; i<=n; i++){
                cont+= i;
            }
            return cont;
        }

        // Funcion suma recursiva
        unsigned long sumaRecursiva(int n){
            // Establecemos nuestro caso base
            if (n <= 0) {
                return 0;

            } else { // SIno procedemos
                return n + sumaRecursiva(n-1);
            }
        }

        // FUncion Suma directa
        unsigned long sumaDirecta(int n){
            // Utilizaremos la sumatoria de Gauss. Para este ejercicio tal que
            return (n * (n+1))/2;
        }
};


#endif

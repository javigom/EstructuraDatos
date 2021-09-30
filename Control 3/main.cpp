/*
    Javier Gómez Moraleda
    Mario Alcolea Alcolea

*/

#include <iostream>
#include <string>

#include "pila.h"

using namespace std;

bool esEquilibrada(const string& cadena) {
    bool equilibrada = true;
    unsigned int i = 0;
    Pila<char> p;

    //Si aun quedan elementos en la cadena y equilibrada es true, sigo avanzando
    while (i < cadena.size() && equilibrada) {

        //Apilo solo los simbolos de apertura (, { y [
        if (cadena[i] == '(' || cadena[i] == '{' || cadena[i] == '[') {
            p.apila(cadena[i]);
        }

        //Si es un simbolo cerrado
        else if (cadena[i] == ')' || cadena[i] == '}' || cadena[i] == ']') {

            //Compruebo que la pila no esta vacia (en el caso en el que haya más cerrados que abiertos)
            if ( !p.esVacia() && ((cadena[i] == ')' && p.cima() == '(') || 
                (cadena[i] == '}' && p.cima() == '{') || 
                (cadena[i] == ']' && p.cima() == '['))) {

                p.desapila();
            }

            //Si un simbolo no coincide, dejo de avanzar
            else {
                equilibrada = false;
            }
        }

        i++;
    }

    //Compruebo si la cadena no es vacia y libero la memoria (si he parado la busqueda)
    //Por ejemplo, si existen mas simbolos abiertos que cerrados '([{}]' (no entraria en el else y queda un simbolo en la pila)
    if (!p.esVacia()) {
        p.~Pila();
        equilibrada = false;
    }

    return equilibrada;
}

int main() {
	string cadena;
    while(getline(cin, cadena)) {
        if (esEquilibrada(cadena))
            cout << "EQUILIBRADA" << endl;
        else
            cout << "NO_EQUILIBRADA" << endl;
	}
	return 0;
}	

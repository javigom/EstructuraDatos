/*
	JAVIER GÓMEZ MORALEDA
	MARIO ALCOLEA ALCOLEA
*/


#include "Arbin.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Implementar aquí la funciones auxiliares que se consideren necesarias

/*
	Función auxiliar que calcula la suma de todas las ramas de un árbol, así como su altura, es decir, la rama más "larga"

	Habíamos considerado pasar por parámetros por referencia las alturas, pero nos ha parecido más cómodo que la función
	devuelva la altura máxima del árbol a.
*/
int recorreHijos(Arbin<int> a, int& suma) {
	
	//Las inicializo a 1 para el caso base, suponiendo que esté en una hoja no se modifica (por la derecha y por la izquierda)
	int altura1 = 1, altura2 = 1;

	//Si tengo hijo derecho, sigo recurriendo
	if (!a.hijoDer().esVacio()) {
		suma = suma + a.hijoDer().raiz();
		altura1 = recorreHijos(a.hijoDer(), suma);
		altura1++;
	}

	//Si tengo hijo izquierdo, sigo recurriendo
	if (!a.hijoIz().esVacio()) {
		suma = suma + a.hijoIz().raiz();
		altura2 = recorreHijos(a.hijoIz(), suma);
		altura2++;
	}

	//Me quedo con la altura máxima
	if (altura1 < altura2) {
		altura1 = altura2;
	}
	
	return altura1;
}

// Función principal a implementar, que determina si
// el árbol dado como entrada es o no zurdo (devuelve true si es
// zurdo, false en otro caso)
bool es_zurdo(Arbin<int> a) {

	bool zurdo = false;

	if (!a.esVacio()) {
		
		//Inicialmente las sumas están a 0
		int sumaDer = 0, sumaIzq = 0;

		//Altura inicializado a 1 para incluir el nodo raíz
		int altura1 = 1, altura2 = 1;

		//Si existe hijo derecho
		if (!a.hijoDer().esVacio()) {
			sumaDer = a.hijoDer().raiz();
			altura1 += recorreHijos(a.hijoDer(), sumaDer);
		}

		//Si existe hijo izquierdo
		if (!a.hijoIz().esVacio()) {
			sumaIzq = a.hijoIz().raiz();
			altura2 += recorreHijos(a.hijoIz(), sumaIzq);
		}
	
		//Me guardo la altura máxima
		if (altura1 < altura2) {
			altura1 = altura2;
		}

		if ((sumaIzq - sumaDer) >= (altura1 - 1)) {
			zurdo = true;
		}
	}

	return zurdo;
}


//-----------------------------------------------------------------------
// Código que se encarga de la e/s: no tocar
//

Arbin<int> lee_arbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<int>();
	case '[': {
		int raiz;
		in >> raiz;
  		in >> c;
		return Arbin<int>(raiz);
	}
	case '(': {
		Arbin<int> iz = lee_arbol(in);
		int raiz;
		in >> raiz;
		Arbin<int> dr = lee_arbol(in);
		in >> c;
		return Arbin<int>(iz, raiz, dr);
	}
	default: return Arbin<int>();
	}
}


/**
La entrada al programa consiste de líneas formadas por árboles de enteros
codificados de acuerdo con las siguientes reglas:
(1) El árbol vacío se codifica como #
(2) Los árboles simples se codifican como [v], con  
    v el valor del nodo
(3) Los árboles complejos se codifican como (IvD),
    con I la codificación del hijo izquierdo,
	v el valor de la raíz, y D la codificación
	del hijo derecho.
Para cada línea leida, escribe en la salida estádar
ZURDO si el árbol es zurdo, y NO_ZURDO en otro caso

Ejemplo de entrada:
#
[5]
([17]5([2]1[3]))
(([2]1[3])5[17])

Salida asociada:
NO_ZURDO
ZURDO
ZURDO
NO_ZURDO


*/

int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		Arbin<int> a = lee_arbol(cin);
		string resto_linea;
		getline(cin, resto_linea);
		if (es_zurdo(a)) cout << "ZURDO";
		else cout << "NO_ZURDO";
		cout << endl;
	}
	return 0;
}

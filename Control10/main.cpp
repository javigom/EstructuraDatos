/**
  Nº DE GRUPO: D25
  NOMBRE Y APELLIDOS DE LOS ALUMNOS QUE HAN REALIZADO EL CONTROL:
	JAVIER GÓMEZ MORALEDA
	MARIO ALCOLEA ALCOLEA
*/


#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;

//Función que devuelve si un nodo es hoja, es decir, no tiene hijos.
bool esHoja(Arbin<int> a) {
	return a.hijoDer().esVacio() && a.hijoIz().esVacio();
}

/* 

Generalización: Funcíon recursiva que va recorriendo el árbol. 
LISTA DE PARÁMETROS:
	- Arbin<int> a: árbol binario de enteros
	- int& numSingu: contador por referencia de nodos que son singulares
	- int sumaAnte: variable que se usa para llevar la suma de los antepasados
	- int sumaDesc: valor devuelto por la función. Representa la suma de los descendientes

Breve descripción del algoritmo:
	El funcionamiento es el siguiente: al realizar la llamada de la función, estamos en el nodo raíz. De esta forma si el nodo no es hoja, llamamos a la recursión,
	sumándole el nodo actual a sumaAnte. Esta función devuelve sumaDesc, es decir, cuando lleguemos a una hoja, devolveremos el valor de la misma para poder realizar
	la comparación con la suma de los antepasados. Evaluamos la condición a la vuelta de la recursión, cuando ya tenemos calculadas ambas sumas.

*/

int calcula_singulares(Arbin<int> a, int& numSingu, int sumaAnte) {
	
	//Se inicializa a 0, ya que al llegar a una hoja, no tiene descendientes
	int sumaDesc = 0;

	if(!esHoja(a)) {

		if (!a.hijoDer().esVacio()) {
			sumaDesc += calcula_singulares(a.hijoDer(), numSingu, sumaAnte + a.raiz());
		}

		if (!a.hijoIz().esVacio()) {
			sumaDesc += calcula_singulares(a.hijoIz(), numSingu, sumaAnte + a.raiz());
		}
	}

	if (sumaDesc == sumaAnte) {
		numSingu++;
	}

	return sumaDesc + a.raiz();
}

unsigned int numero_singulares(Arbin<int> a) {
	int numSingulares = 0;

	//Si el árbol es vacío, devuelvo 0
	if (!a.esVacio()) {
		calcula_singulares(a, numSingulares, 0);
	}

	return numSingulares;
}

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


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		cout << numero_singulares(lee_arbol(cin));
		string resto_linea;
		getline(cin, resto_linea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}

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

//Función que devuelve true si el nodo es hoja, es decir, no tiene hijo izquierdo ni derecho
bool esHoja(Arbin<int> a) {
	return a.hijoDer().esVacio() && a.hijoIz().esVacio();
}

/*

Generalización: Función que calcula el numero de hojas profundas
Parámetros:
	- Arbin<int> a: árbol binario con los datos
	- unsigned int k: valor entero no negativo que debe ser superado por el nivel del árbol
	- unsigned int nivel: valor entero en el que voy acumulando el nivel hasta llegar a una hoja
	- unsigned int& numHojas: valor entero por referencia en el que guardo el número de hojas profundas

No tiene valor de retorno. Otra implementación posible sería cambiando la función a tipo int y devolver 1 cuando es hoja y cumpla que nivel > k. Luego tendría
que recoger el valor devuelto de ambas recursiones de los hijos con una variable local y a su vez volver a devolverlo (Está escrita justo debajo, hemos decidido
dejar la primera ya que es como se nos ha ocurrido la primera vez).

Breve descripción: Al llamar a la función, estoy en la raíz, la idea es ir realizando la recursión por el hijo izquierdo e hijo derecho, aumentando el nivel en 1 en 
cada llamada hasta llegar a una hoja. Una vez estemos en una hoja, comparamos el valor k con el nivel en el que me encuentro. En el caso de ser superado, aumento 
el contador de hojas profundas.

*/


void calcula_hojas_profundas(Arbin<int> a, unsigned int k, unsigned int nivel, unsigned int& numHojas) {

	if (esHoja(a)) {
		if (nivel > k) {
			numHojas = numHojas + 1;
		}
	}

	else {
		if (!a.hijoDer().esVacio()) {
			calcula_hojas_profundas(a.hijoDer(), k, nivel + 1, numHojas);
		}

		if (!a.hijoIz().esVacio()) {
			calcula_hojas_profundas(a.hijoIz(), k, nivel + 1, numHojas);
		}
	}
}

/*
IMPLEMENTACIÓN 2

int calcula_hojas_profundas(Arbin<int> a, unsigned int k, unsigned int nivel) {

	int numHojas1 = 0, numHojas2 = 0;

	if (esHoja(a)) {
		if (nivel > k) {
			return 1;
		}
	}

	else {

		if (!a.hijoDer().esVacio()) {
			numHojas1 = calcula_hojas_profundas(a.hijoDer(), k, nivel + 1);
		}

		if (!a.hijoIz().esVacio()) {
			numHojas2 = calcula_hojas_profundas(a.hijoIz(), k, nivel + 1);
		}
	}
	return numHojas1 + numHojas2;
}
*/

unsigned int numero_hojas_mas_profundas_que(Arbin<int> a, unsigned int k) {
	unsigned int numHojas = 0;

	//Si es vacío devuelvo 0
	if (!a.esVacio()) {
		calcula_hojas_profundas(a, k, 1, numHojas);
	}

	return numHojas;
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
		Arbin<int> a = lee_arbol(cin);
		int k;
		cin >> k;
		cout << numero_hojas_mas_profundas_que(a,k) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}

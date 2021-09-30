/*
	D25
	JAVIER GÓMEZ MORALEDA
	MARIO ALCOLEA ALCOLEA	
*/

#include "Arbin.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
Funcion recursiva que calcula el numero de tramos navegables. Su valor de retorno es el caudal, de tal forma que
se va recurriendo hasta llegar a los afluentes (hojas del árbol).

*/
int recursion(const Arbin<int>& cuenca, int& numNavegables) {

	int caudal = 0;

	//Caso base: si he llegado a una hoja, el caudal siempre es 1
	if (cuenca.hijoDer().esVacio() && cuenca.hijoIz().esVacio()) {
		caudal = 1;
	}

	//Caso recursivo
	else {
		if (!cuenca.hijoDer().esVacio()) {
			caudal += recursion(cuenca.hijoDer(), numNavegables);
		}

		if (!cuenca.hijoIz().esVacio()) {
			caudal += recursion(cuenca.hijoIz(), numNavegables);
		}
	}
	
	//Le sumo el valor del nodo ya que si es un embalse, restan al caudal total 
	caudal += cuenca.raiz();

	//Me aseguro de que el caudal nunca sea negativo
	if (caudal < 0) {
		caudal = 0;
	}

	//Si es mayor que 3, es navegable
	if (caudal >= 3) {
		numNavegables++;
	}

	return caudal;
}

int numeroTramosNavegables(const Arbin<int>& cuenca) {

	int numeroTramos1 = 0, numeroTramos2 = 0;

	//Si tiene hijo en la izquierda, llamo a la funcion que calcule el numero de tramos 
	if (!cuenca.hijoIz().esVacio()) {
		recursion(cuenca.hijoIz(), numeroTramos1);
	}

	//Si tiene hijo en la derecha, llamo a la funcion que calcule el numero de tramos 
	if (!cuenca.hijoDer().esVacio()) {
		recursion(cuenca.hijoDer(), numeroTramos2);
	}
	
	//Devuelvo la suma de ambos tramos
	return numeroTramos1 + numeroTramos2;
}

Arbin<int> leeArbol(istream& in) {
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
		Arbin<int> iz = leeArbol(in);
		int raiz;
		in >> raiz;
		Arbin<int> dr = leeArbol(in);
		in >> c;
		return Arbin<int>(iz, raiz, dr);
	}
	default: return Arbin<int>();
	}
}

int main() {
	Arbin<int> cuenca;
	while (cin.peek() != EOF)  {
		cout << numeroTramosNavegables(leeArbol(cin));
		string restoLinea;
		getline(cin, restoLinea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}
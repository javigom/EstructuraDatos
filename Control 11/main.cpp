/*
Nº GRUPO: D25

NOMBRE Y APELLIDOS DE LOS COMPONENTES QUE HAN REALIZADO EL CONTROL:
	JAVIER GÓMEZ MORALEDA
	MARIO ALCOLEA ALCOLEA
*/

#include <iostream>
#include <string>
#include "diccionario.h"
#include "lista.h"
using namespace std;


// Clase Puntuacion. Sirve para representar la puntuacion final  (nota)
// obtenida por un alumno.
class Puntuacion {
  public:
    string alumno;
    int nota;	
	Puntuacion(const string& nombre, int puntuacion): alumno(nombre), nota(puntuacion) {}
};

/*

Función auxiliar que dado un diccionario y una lista, recorre el diccionario con un iterador y devuelve la lista con todos aquellos
alumnos cuya nota sea distinta de cero.

*/
void recorreDiccionario(const Diccionario<string, int>& diccionario, Lista<Puntuacion>& listado) {

	Diccionario<string, int> ::ConstIterator itDiccionario = diccionario.cbegin();
	Diccionario<string, int> ::ConstIterator endDiccionario = diccionario.cend();

	Lista<Puntuacion> ::Iterator itLista = listado.begin();

	while (itDiccionario != endDiccionario) {

		if (itDiccionario.valor() != 0) {
			listado.insertar(Puntuacion(itDiccionario.clave(), itDiccionario.valor()), itLista);
		}

		itDiccionario.next();
	}
}

/*

Función califica: recibe dos listas con los alumnos que han aprobado y suspendido y devuelve una con la nota.

Para ello hacemos uso de iteradores, recorremos la primera lista y añadimos los alumnos al diccionario (por orden alfabético). Lo mismo con la segunda.
Si un alumno ya existe en el diccionario, sumamos o restamos 1 en función de que lista estemos recorriendo.

Una vez tenemos el diccionario completado, hacemos uso de una función externa que recorre el mismo y rellena la lista de salida.

*/
void califica(const Lista<string>& bien, const Lista<string>& mal, Lista<Puntuacion>& listado) {
	
	Diccionario <string, int> diccionario;

	Lista<string> ::ConstIterator itBien = bien.cbegin();
	Lista<string> ::ConstIterator endBien = bien.cend();

	while (itBien != endBien) {

		if (diccionario.contiene(itBien.elem())) {
			diccionario.inserta(itBien.elem(), diccionario.valorPara(itBien.elem()) + 1);
		}

		else {
			diccionario.inserta(itBien.elem(), 1);
		}

		itBien.next();
	}

	Lista<string> ::ConstIterator itMal = mal.cbegin();
	Lista<string> ::ConstIterator endMal = mal.cend();

	while (itMal != endMal) {

		if (diccionario.contiene(itMal.elem())) {
			diccionario.inserta(itMal.elem(), diccionario.valorPara(itMal.elem()) - 1);
		}

		else {
			diccionario.inserta(itMal.elem(), - 1);
		}

		itMal.next();
	}

	recorreDiccionario(diccionario, listado);
}

void imprimePuntuaciones(Lista<Puntuacion>& listado) {
  Lista<Puntuacion>::ConstIterator i = listado.cbegin();
  Lista<Puntuacion>::ConstIterator e = listado.cend();
  while (i != e) {
	  cout << "[" << i.elem().alumno << ":" << i.elem().nota << "]";
      i.next();	  
  }  
  cout << endl;
}

void leeResultados(Lista<string>& bien, Lista<string>& mal) {
	string nombre;
	do {
		cin >> nombre;
		if (nombre != "#") {
			string resultado;
			cin >> resultado;
			if (resultado == "+")
				bien.pon_final(nombre);
			else
				mal.pon_final(nombre);
		}
	} while (nombre != "#");
}

int main() {
  string comienzo;
  while (cin >> comienzo) {
	 Lista<string> bien;
	 Lista<string> mal;
	 Lista<Puntuacion> listado;
	 leeResultados(bien, mal);
	 califica(bien, mal,listado);
	 imprimePuntuaciones(listado);
  }
  return 0;   
}
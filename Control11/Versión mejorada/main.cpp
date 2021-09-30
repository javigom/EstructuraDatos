/*
Nº GRUPO:

NOMBRE Y APELLIDOS DE LOS COMPONENTES QUE HAN REALIZADO EL CONTROL:

*/

#include "diccionario.h"
#include "lista.h"
#include <iostream>
#include <string>
using namespace std;


// Clase Puntuacion. Sirve para representar la puntuacion final  (nota)
// obtenida por un alumno.
class Puntuacion {
  public:
    string alumno;
    int nota;	
	Puntuacion(const string& nombre, int puntuacion): alumno(nombre), nota(puntuacion) {}
};

void califica(const Lista<string>& bien, const Lista<string>& mal, Lista<Puntuacion>& listado) {
	  
	Diccionario<string, int> diccionario;

	Lista<string>::ConstIterator itBien = bien.cbegin();
	Lista<string>::ConstIterator itBienFin = bien.cend();

	while (itBien != itBienFin) {
		Diccionario<string, int>::Iterator itDiccionario = diccionario.busca(itBien.elem());
		Diccionario<string, int>::Iterator itDiccionarioFin = diccionario.end();

		if (itDiccionario != itDiccionarioFin) {
			itDiccionario.setVal(itDiccionario.valor() + 1);
		}

		else {
			diccionario.inserta(itBien.elem(), 1);
		}

		itBien.next();
	}

	Lista<string>::ConstIterator itMal = mal.cbegin();
	Lista<string>::ConstIterator itMalFin = mal.cend();

	while (itMal != itMalFin) {
		Diccionario<string, int>::Iterator itDiccionario = diccionario.busca(itMal.elem());
		Diccionario<string, int>::Iterator itDiccionarioFin = diccionario.end();

		if (itDiccionario != itDiccionarioFin) {
			itDiccionario.setVal(itDiccionario.valor() - 1);
		}

		else {
			diccionario.inserta(itMal.elem(), - 1);
		}

		itMal.next();
	}

	Diccionario<string, int>::Iterator itDiccionario = diccionario.begin();
	Diccionario<string, int>::Iterator itDiccionarioFin = diccionario.end();

	Lista<Puntuacion>::Iterator itPuntuacion = listado.begin();

	while (itDiccionario != itDiccionarioFin) {

		if (itDiccionario.valor() != 0) {
			Puntuacion p = Puntuacion(itDiccionario.clave(), itDiccionario.valor());
			listado.insertar(p, itPuntuacion);
		}
		
		itDiccionario.next();
	}

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
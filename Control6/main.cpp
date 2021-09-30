/*
	JAVIER GÓMEZ MORALEDA
	MARIO ALCOLEA ALCOLEA
*/

#include <iostream>
using namespace std;
#include <string>

#include "lista.h"
// INCLUIR EL RESTO DE TADS QUE SE CONSIDEREN OPORTUNOS

//Comprueba si un caracter es vocal
bool esVocal(char c) {
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
		c == 'A' ||  c == 'E' || c == 'I' || c == 'O' || c == 'U') {
		return true;
	}

	else return false;
}

void invierteSecuenciasNoVocales(Lista<char> &mensaje) {
	 
	Lista<char>::Iterator recorre = mensaje.begin();
	Lista<char>::Iterator final = mensaje.end();
	
	Lista<char> aux;

	Lista<char>::Iterator rAux = aux.begin();
	Lista<char>::Iterator fAux = aux.end();

	while (recorre != final) {

		rAux = aux.begin();
		fAux = aux.end();

		if (esVocal(recorre.elem())) {

			while (rAux != fAux) {
				mensaje.insertar(rAux.elem(), recorre);
				rAux = aux.eliminar(rAux);
			}
			recorre.next();
		} 

		else {
			aux.pon_ppio(recorre.elem());
			recorre = mensaje.eliminar(recorre);
		}
	
	}

	rAux = aux.begin();
	fAux = aux.end();

	
	while (rAux != fAux) {
		mensaje.insertar(rAux.elem(), recorre);
		rAux = aux.eliminar(rAux);
	}

}
 
  // Imprime la lista por la salida estandar
void imprime(const Lista<char>& l) {
	Lista<char>::ConstIterator it = l.cbegin();
	while (it != l.cend()) {
		cout << it.elem();
		it.next();
	}
	cout << endl;
}

// Codifica el mensaje
void codifica(Lista<char>& mensaje) {
	invierteSecuenciasNoVocales(mensaje);
	mensaje.enredar();    // Esta operacion debe ser implementada como
	                      // un nuevo metodo de Lista
}

  // Transforma la linea en una lista de caracteres
void construyeMensaje(const string& linea, Lista<char>& mensaje) {
	for(unsigned int i=0; i < linea.size(); i++)
		mensaje.pon_final(linea[i]);  
}

int main() {
	string linea;
	while(getline(cin,linea)) {
	   Lista<char> mensaje;
	   construyeMensaje(linea,mensaje);
       codifica(mensaje);
	   imprime(mensaje);
	}
	return 0;
}	

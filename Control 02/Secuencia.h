/*
	MARIO ALCOLEA ALCOLEA
	JAVIER GOMEZ MORALEDA
*/

using namespace std;

#ifndef _SECUENCIA_H_
#define _SECUENCIA_H_

/// Excepción de elemento inexistente
class ElementoInvalido {};


template<class T>
class Secuencia {
public:

	//Constructor por defecto

	Secuencia(int tam = TAM_INICIAL) {
		_elementos = new T(tam);
		_tam = tam;
		_nelems = 0;
	}

	//Destructor

	~Secuencia() {
		delete[] _elementos;
	}

	//Constructor de copia

	Secuencia(const Secuencia& s) {
		_elementos = duplica(s._elementos, s._tam, s._nelems);
		_tam = s._tam;
		_nelems = s._nelems;
	}

	//Sobrecarga operador =

	Secuencia& operator = (const Secuencia &s) {
		if (&s != this) {
			if (s._nelems < _tam) {
				copia(_elementos, s._elementos, s._nelems);
				_nelems = s._nelems;
			}
			else {
				delete[] _elementos;
				_elementos = duplica(s._elementos, s._tam, s._nelems);
				_tam = s._tam;
				_nelems = s._nelems;
			}
		}

		return *this;
	}

	void pon(const T& e) {
		//Si no cabe se duplica el array
		if (_tam == _nelems) {
			T* aux = _elementos;
			_elementos = duplica(aux, _tam*2, _nelems);
			_tam *= 2;
			delete[] aux;
		}

		//Se añade el elemento
		_elementos[_nelems] = e;
		_nelems++;

	}

	const T& elem(int i) {
		if (i >= _nelems) {
			throw ElementoInvalido();
		}
		else {
			return _elementos[i];
		}
	}

	int num_elems() const {
		return _nelems;
	}

     // DEBEN INCLUIRSE E IMPLEMENTARSE 
	 // LAS OPERACIONES ADICIONALES
	 // NECESARIAS PARA GARANTIZAR EL CORRECTO
	 // FUNCIONAMIENTO DEL TAD


private:
  // INCLUIR DETALLES DE REPRESENTACION Y OPERACIONES AUXILIARES
	static const unsigned int TAM_INICIAL = 2;
	int _tam;
	int _nelems;
	T* _elementos;

	static T* duplica(T* elementos, int tam, int nelems) {
		
		T* dup = new T[tam];
		copia(dup, elementos, nelems);
		return dup;
	}

	static void copia(T* destino, T* origen, int nelems) {
		
		for (int i = 0; i < nelems; i++) {
			destino[i] = origen[i];
		}
	}

};


#endif



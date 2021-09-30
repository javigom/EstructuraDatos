/*
D25
Mario Alcolea Alcolea
Javier Gómez Moraleda
*/

#include "Racional.h"
#include <cmath>

  //Metodos publicos

  	//**** COMPLETAR
	//  Deben implementarse los metodos publicos de la clase
	//****

Racional::Racional() {
	_numer = 0;
	_denom = 1;
	this->reduce(); //no es necesario
}

Racional::Racional(long numer, long denom) {
	if (denom == 0){
		throw EDenominadorCero();
	}
	else {
		_numer = numer;
		_denom = denom;
	}
	this->reduce();
}

Racional Racional::suma(const Racional& r) {

	Racional resul;
	
	resul._numer = (this->_numer*(mcm(this->_denom, r._denom)/this->_denom)) + 
					(r._numer*(mcm(this->_denom, r._denom)/r._denom));
	resul._denom = mcm(this->_denom, r._denom);

	resul.reduce();
	return resul;
}

Racional Racional::operator-(const Racional& r) const {
	Racional resul;

	resul._numer = (this->_numer * (mcm(this->_denom, r._denom) / this->_denom)) -
		(r._numer * (mcm(this->_denom, r._denom) / r._denom));
	resul._denom = mcm(this->_denom, r._denom);
	
	resul.reduce();
	return resul;
}

Racional& Racional::operator*=(const Racional& r) {
	/*
	Racional resul;
	resul._numer = this->_numer * r._numer;
	resul._denom = this->_denom * r._denom;
	resul.reduce();
	_numer = resul._numer;
	_denom = resul._denom;
	*/

	_numer = _numer * r._numer;
	_denom = _denom * r._denom;

	this->reduce();

	return *this;
}

/* SOLUCION PROFESOR

void Racional::operator*=(const Racional& r) {
	_numer = _numer * r._numer;
	_denom = _denom * r._denom;
	reduce();
}
*/


Racional Racional::divideYActualiza(const Racional& r) {
	
	Racional resul;

	if (r._numer == 0 && r._denom == 1) {
		throw EDivisionPorCero();
	}

	else {
		resul._numer = this->_numer * r._denom;
		resul._denom = this->_denom * r._numer;
		resul.reduce();
	}

	*this = resul;

	return *this;
}

/* SOLUCIÓN PROFESOR

void Racional::divideYActualiza(const Racional& r) {
	if (r._numer == 0) throw EDivisionPorCero();
	else {
		_numer = _numer * r._denom;
		_denom = _denom * r._numer;
		reduce();
	}
}
*/


bool Racional::operator==(const Racional& r) {
	if ((this->_numer == r._numer) && this->_denom == r._denom) {
		return true;
	}
	else {
		return false;
	}
}
  
  // Funciones amigas
ostream& operator<<(ostream& out, const Racional& f) {
	out << f._numer << "/" << f._denom;
	return out;
}

// Metodos privados
void Racional::reduce() {
	  // Se asegura que el denominador siempre sea positivo   
	if (_denom < 0) {
		_numer = -_numer;
		_denom = -_denom;
	}
	  // Se divide numerador y denominador por el maximo comun divisor de ambos
	long fsimp = mcd(_numer, _denom);
	_numer /= fsimp;
	_denom /= fsimp;
}

long Racional::mcd(long v1, long v2) {
	  // El calculo del maximo comun divisor se hace por el algoritmo de Euclides
	v1 = abs(v1); 
    v2 = abs(v2);	
	if (v1 < v2) {
		long tmp = v1;
		v1 = v2;
		v2 = tmp;
	}
	while (v2 != 0) {
		long nv2 = v1%v2;
		v1 = v2;
		v2 = nv2;
	}
	return v1;
}

long Racional::mcm(long v1, long v2) {
	return v1*v2 / mcd(v1, v2);
}
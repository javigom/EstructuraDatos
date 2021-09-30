/*
Nº GRUPO:
NOMBRES Y APELLIDOS DE LAS PERSONAS QUE HAN REALIZADO EL CONTROL:
*/

#include "ParqueDeAtracciones.h"

ParqueDeAtracciones::ParqueDeAtracciones() {}

void ParqueDeAtracciones::an_atraccion(const string& nombre_atraccion) {

	DiccionarioHash<tAtraccion, Cola<tNinio>>::Iterator it = _atracciones.busca(nombre_atraccion);
	DiccionarioHash<tAtraccion, Cola<tNinio>>::Iterator fin = _atracciones.end();

	if (it == fin) {
		_atracciones.inserta(nombre_atraccion, Cola<tNinio>());
	}
	else {
		throw EAtraccionYaExiste();
	}
	
}

void ParqueDeAtracciones::an_ninio(const string& nombre_ninio) {
	  
	DiccionarioHash<tNinio, tInfoNinio>::Iterator it = _ninios.busca(nombre_ninio);
	DiccionarioHash<tNinio, tInfoNinio>::Iterator fin = _ninios.end();

	if (it == fin) {
		tInfoNinio t;
		_ninios.inserta(nombre_ninio, t);
	}

	else {
		throw ENinioYaRegistrado();
	}
}

void ParqueDeAtracciones::poner_en_fila(const string& nombre_ninio, const string& nombre_atraccion) {

	DiccionarioHash<tNinio, tInfoNinio>::Iterator itNinios = _ninios.busca(nombre_ninio);
	DiccionarioHash<tNinio, tInfoNinio>::Iterator itNiniosFin = _ninios.end();

	DiccionarioHash<tAtraccion, Cola<tNinio>>::Iterator itAtraccion = _atracciones.busca(nombre_atraccion);
	DiccionarioHash<tAtraccion, Cola<tNinio>>::Iterator itAtraccionFin = _atracciones.end();


	if (itNinios != itNiniosFin && itAtraccion != itAtraccionFin && !itNinios.valor()._esperando) {
		itAtraccion.valor().pon(itNinios.clave());
		itNinios.valor()._esperando = true;
	}

	else {
		throw EAccesoAtraccion();
	}
}	

void ParqueDeAtracciones::avanzar(const string& nombre_atraccion) {
	  
	DiccionarioHash<tAtraccion, Cola<tNinio>>::Iterator itAtraccion = _atracciones.busca(nombre_atraccion);
	DiccionarioHash<tAtraccion, Cola<tNinio>>::Iterator itAtraccionFin = _atracciones.end();

	if (itAtraccion == itAtraccionFin) {
		throw EAtraccionNoExiste();
	}

	else if (!itAtraccion.valor().esVacia()){
		tNinio aQuitar = itAtraccion.valor().primero();
		itAtraccion.valor().quita();

		DiccionarioHash<tNinio, tInfoNinio>::Iterator it = _ninios.busca(aQuitar);

		it.valor()._esperando = false;
		
		Diccionario<tAtraccion, int>::Iterator it2 = it.valor()._visitadas.busca(itAtraccion.clave());
		Diccionario<tAtraccion, int>::Iterator fin = it.valor()._visitadas.end();

		if (it2 != fin) {
			it2.setVal(it2.valor() + 1);
		}
		else {
			it.valor()._visitadas.inserta(itAtraccion.clave(), 1);
		}
	}
}


Lista<string> ParqueDeAtracciones::atracciones_visitadas(const string& nombre_ninio) const {

	DiccionarioHash<tNinio, tInfoNinio>::ConstIterator it = _ninios.cbusca(nombre_ninio);
	DiccionarioHash<tNinio, tInfoNinio>::ConstIterator fin = _ninios.cend();

	Lista<string> listado;
	Lista<string>::Iterator itLista = listado.begin();

	if (it == fin) {
		throw ENinioNoRegistrado();
	}

	else {
		Diccionario<tAtraccion, int>::ConstIterator it2 = it.valor()._visitadas.cbegin();
		Diccionario<tAtraccion, int>::ConstIterator fin2 = it.valor()._visitadas.cend();

		while (it2 != fin2) {
			listado.insertar(it2.clave(), itLista);
			it2.next();
		}
	}

	return listado;
}
   
int ParqueDeAtracciones::numero_visitas(const string& nombre_ninio, const string& nombre_atraccion) const {

	DiccionarioHash<tNinio, tInfoNinio>::ConstIterator itNinios = _ninios.cbusca(nombre_ninio);
	DiccionarioHash<tNinio, tInfoNinio>::ConstIterator itNiniosFin = _ninios.cend();

	DiccionarioHash<tAtraccion, Cola<tNinio>>::ConstIterator itAtraccion = _atracciones.cbusca(nombre_atraccion);
	DiccionarioHash<tAtraccion, Cola<tNinio>>::ConstIterator itAtraccionFin = _atracciones.cend();

	if (itNinios == itNiniosFin || itAtraccion == itAtraccionFin) {
		throw EConsultaNumViajes();
	}

	else {
		Diccionario<tAtraccion, int>::ConstIterator it = itNinios.valor()._visitadas.cbusca(nombre_atraccion);
		Diccionario<tAtraccion, int>::ConstIterator fin = itNinios.valor()._visitadas.cend();

		if (it == fin) {
			return 0;
		}
		
		else {
			return it.valor();
		}
	}
}
   
 
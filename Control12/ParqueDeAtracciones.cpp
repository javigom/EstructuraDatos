/*
Nº GRUPO: D25
NOMBRES Y APELLIDOS DE LAS PERSONAS QUE HAN REALIZADO EL CONTROL:
	JAVIER GÓMEZ MORALEDA
	MARIO ALCOLEA ALCOLEA
*/

#include "ParqueDeAtracciones.h"

ParqueDeAtracciones::ParqueDeAtracciones() {}

/*
	Función que añade una atraccion al Diccionario de atracciones. Para ello hace uso de iteradores.
 */
void ParqueDeAtracciones::an_atraccion(const string& nombre_atraccion) {

	//Iterador que busca en el diccionario de atracciones el valor nombre_atraccion
	Diccionario<tAtraccion, Cola<tNinio>> ::Iterator iAtraccion = _atracciones.busca(nombre_atraccion);
	Diccionario<tAtraccion, Cola<tNinio>> ::Iterator iAtraccionFin = _atracciones.end();

	//Compruebo si la atracción NO existe para añadirla
	if(iAtraccion == iAtraccionFin){
		Cola<tNinio> c;
		_atracciones.inserta(nombre_atraccion, c);
	}
	else {
		throw EAtraccionYaExiste();
	}

}

/*
 	Función que añade un niño al Diccionario de niño. Para ello hace uso de iteradores.
 */
void ParqueDeAtracciones::an_ninio(const string& nombre_ninio) {

	//Iterador que busca en el diccionario de niños el valor nombre_ninio
	Diccionario<tNinio, Diccionario<tAtraccion, int>> ::Iterator iNinio = _ninios.busca(nombre_ninio);
	Diccionario<tNinio, Diccionario<tAtraccion, int>> ::Iterator iNinioFin = _ninios.end();

	//Compruebo si el niño NO existe para añadirlo
	if (iNinio == iNinioFin) {
		Diccionario<tAtraccion, int> d;
		_ninios.inserta(nombre_ninio, d);
	}
	else {
		throw ENinioYaRegistrado();
	}
}

/*
	Función que añade un niño a la fila de una atracción
 */
void ParqueDeAtracciones::poner_en_fila(const string& nombre_ninio, const string& nombre_atraccion) {
	
	//Iterador que busca en el diccionario de niños el valor nombre_ninio
	Diccionario<tNinio, Diccionario<tAtraccion, int>> ::Iterator iNinio = _ninios.busca(nombre_ninio);
	Diccionario<tNinio, Diccionario<tAtraccion, int>> ::Iterator iNinioFin = _ninios.end();
	
	//Iterador que busca en el diccionario de atracciones el valor nombre_atraccion
	Diccionario<tAtraccion, Cola<tNinio>> ::Iterator iAtraccion = _atracciones.busca(nombre_atraccion);
	Diccionario<tAtraccion, Cola<tNinio>> ::Iterator iAtraccionFin = _atracciones.end();

	//Si tanto el niño como la atracción existe
	if (iNinio != iNinioFin && iAtraccion != iAtraccionFin) {

		//Iterador para el diccionario hash en el que busco si el niño está ya esperando
		DiccionarioHash<tNinio, tAtraccion> ::ConstIterator iNinioEsperando = _esperando.cbusca(nombre_ninio);
		DiccionarioHash<tNinio, tAtraccion> ::ConstIterator iNinioEsperandoFin = _esperando.cend();

		//Si son iguales, es decir, el niño no está esperando, lo añado al diccionario hash y a la cola del diccionario de atracciones
		if (iNinioEsperando == iNinioEsperandoFin) {

			iAtraccion.valor().pon(nombre_ninio);
			_esperando.inserta(nombre_ninio, nombre_atraccion);
		}

		else {
			throw EAccesoAtraccion();
		}
	}
	
	else {
		throw EAccesoAtraccion();
	}
}	

/*
 	Función que avanza una atracción 
 */
void ParqueDeAtracciones::avanzar(const string& nombre_atraccion) {

	//Iterador que busca en el diccionario de atracciones el valor nombre_atraccion
	Diccionario<tAtraccion, Cola<tNinio>> ::Iterator iAtraccion = _atracciones.busca(nombre_atraccion);
	Diccionario<tAtraccion, Cola<tNinio>> ::Iterator iAtraccionFin = _atracciones.end();

	//Si eiste la atracción
	if (iAtraccion != iAtraccionFin) {

		//Compruebo que la cola no esté vacía
		if (!iAtraccion.valor().esVacia()) {

			tNinio ninio = iAtraccion.valor().primero();

			//Elimino al niño de la tabla hash
			_esperando.borra(ninio);

			//Iterador que busca al niño (asumo que existe, de otra forma no podría haberlo encolado)
			Diccionario<tNinio, Diccionario<tAtraccion, int>> ::Iterator iNinio = _ninios.busca(ninio);

			//Si el niño ya ha subido en la atracción, aumento el valor de dicha atracción en 1
			if (iNinio.valor().contiene(iAtraccion.clave())) {
				iNinio.valor().inserta(iAtraccion.clave(), iNinio.valor().valorPara(iAtraccion.clave()) + 1);
			}
			//En otro caso, la inicializo a 1
			else {
				iNinio.valor().inserta(iAtraccion.clave(), 1);
			}
			
			//Quito al niño de la cola de la atracción
			iAtraccion.valor().quita();
		}
	}

	else {
		throw EAtraccionNoExiste();
	}
}

/*
	Función que muestra las atraccíones visitadas por un niño
 */
Lista<string> ParqueDeAtracciones::atracciones_visitadas(const string& nombre_ninio) const {

	Lista<string> listado;
	Lista<string> ::Iterator it = listado.begin();

	//Iterador que busca en el diccionario de niños el valor nombre_ninio
	Diccionario<tNinio, Diccionario<tAtraccion, int>> ::ConstIterator iNinio = _ninios.cbusca(nombre_ninio);
	Diccionario<tNinio, Diccionario<tAtraccion, int>> ::ConstIterator iNinioFin = _ninios.cend();

	//Si existe el niño
	if (iNinio != iNinioFin) {

		//Iterador para recorrer las atracciones visitadas por el niño
		Diccionario<tAtraccion, int> ::ConstIterator iAtracciones = iNinio.valor().cbegin();
		Diccionario<tAtraccion, int> ::ConstIterator iAtraccionesFin = iNinio.valor().cend();

		//Inserto las atracciones en la lista
		while (iAtracciones != iAtraccionesFin) {
			listado.insertar(iAtracciones.clave(), it);
			iAtracciones.next();
		}
	}

	else {
		throw ENinioNoRegistrado();
	}
	
	return listado;
}
   
/*
	Función que muestra el número de visitas de un niño en una atracción
 */
int ParqueDeAtracciones::numero_visitas(const string& nombre_ninio, const string& nombre_atraccion) const {

	int contador = 0;

	//Iterador que busca en el diccionario de niños el valor nombre_ninio
	Diccionario<tNinio, Diccionario<tAtraccion, int>> ::ConstIterator iNinio = _ninios.cbusca(nombre_ninio);
	Diccionario<tNinio, Diccionario<tAtraccion, int>> ::ConstIterator iNinioFin = _ninios.cend();

	//Iterador que busca en el diccionario de atracciones el valor nombre_atraccion
	Diccionario<tAtraccion, Cola<tNinio>> ::ConstIterator iAtraccion = _atracciones.cbusca(nombre_atraccion);
	Diccionario<tAtraccion, Cola<tNinio>> ::ConstIterator iAtraccionFin = _atracciones.cend();

	//Si tanto el niño como la atracción existen
	if (iNinio != iNinioFin && iAtraccion != iAtraccionFin) {

		//Iterador que busca la atracción en el diccionario de atracciones de un niño
		Diccionario<tAtraccion, int> ::ConstIterator iAtracciones = iNinio.valor().cbusca(nombre_atraccion);
		Diccionario<tAtraccion, int> ::ConstIterator iAtraccionesFin = iNinio.valor().cend();
		
		//Si el niño ha visitado esa atracción, guardo su valor en el contador
		if (iAtracciones != iAtraccionesFin) {
			contador = iAtracciones.valor();
		}
		
	}

	else {
		throw EConsultaNumViajes();
	}
	

	return contador;
}

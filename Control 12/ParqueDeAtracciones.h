/*
Nº GRUPO: D25
NOMBRES Y APELLIDOS DE LAS PERSONAS QUE HAN REALIZADO EL CONTROL:
    JAVIER GÓMEZ MORALEDA
    MARIO ALCOLEA ALCOLEA
*/

#include "lista.h"
#include "DiccionarioHash.h"
#include "hash.h"
#include "diccionario.h"
#include "cola.h"

#ifndef _PARQUE_ATRACCIONES_H
#define _PARQUE_ATRACCIONES_H
#include <string>

typedef string tNinio;
typedef string tAtraccion;

// Realizar los 'include' adicionales
// que se estimen oportuno.

using namespace std;

class EAtraccionYaExiste {};

class ENinioYaRegistrado {};

class EAtraccionNoExiste {};

class ENinioNoRegistrado {};

class EAccesoAtraccion {};

class EConsultaNumViajes {};


class ParqueDeAtracciones {
public:
   ParqueDeAtracciones();
   void an_atraccion(const string& nombre_atraccion);
   void an_ninio(const string& nombre_ninio);
   void poner_en_fila(const string& nombre_ninio, const string& nombre_atraccion);
   void avanzar(const string& nombre_atraccion);
   Lista<string> atracciones_visitadas(const string& nombre_ninio) const;
   int numero_visitas(const string& nombre_ninio,const string& nombre_atraccion) const;
private:

    //Diccionario con las atracciones como clave y cuyo valor es una cola de niños
    Diccionario<tAtraccion, Cola<tNinio>> _atracciones;

    //Diccionario con los niños como clave y cuyo valor es otro diccionario que contiene las atracciones en las que ha estado junto con un entero que determina el número de veces
    Diccionario <tNinio, Diccionario <tAtraccion, int>> _ninios;

    //Diccionario hash en el que se guarda un par clave-valor de los niños que están esperando en una cola
    DiccionarioHash<tNinio, tAtraccion> _esperando;
};

#endif
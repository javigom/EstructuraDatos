/*
Nº GRUPO:
NOMBRES Y APELLIDOS DE LAS PERSONAS QUE HAN REALIZADO EL CONTROL:
*/

#include "lista.h"
#include "DiccionarioHash.h"
#include "hash.h"
#include "diccionario.h"
#include "cola.h"

#ifndef _PARQUE_ATRACCIONES_H
#define _PARQUE_ATRACCIONES_H
#include <string>

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
   // Definir la representación que se estime oportuna, así como declarar los métodos
   // auxiliares que se consideren oportunos (si se estima necesario). 
   
    typedef string tNinio;
    typedef string tAtraccion;

    class tInfoNinio {
        public:
        Diccionario<tAtraccion, int> _visitadas;
        bool _esperando;

        tInfoNinio() {
            _visitadas = Diccionario<tAtraccion, int>();
            _esperando = false;
        }
    };

    DiccionarioHash<tAtraccion, Cola<tNinio>> _atracciones;
    DiccionarioHash<tNinio, tInfoNinio> _ninios;
  
};

#endif
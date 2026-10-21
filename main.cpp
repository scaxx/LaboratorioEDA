#include <iostream>
#include <string>

using namespace std;

#define MAX_CANT_PALABRAS_X_LINEA 3

typedef unsigned int Posicion;

enum _retorno {OK,ERROR,NO_IMPLEMENTADA};

typedef enum _retorno TipoRetorno;

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////ESTRUCTURAS///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

//una palabra del texto (lista simple dentro de cada linea)
struct nodoPalabra{
    string palabra;
    nodoPalabra *sig;
}

//una linea del texto (lista simple de lineas)
struct nodoLinea{
    nodoPalabra *primeraPalabra;
    nodoPalabra *ultimaPalabra;
    int cantPalabras;
    nodoLinea *sig;
    nodoLinea *ant;
};

struct Texto{
Linea *primera;
Linea *ultima;
int cantidadLineas;
};

struct nodoDiccionario{
string palabra;
nodoDiccionario *izq;
nodoDiccionario *der;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////FIRMAS/////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

//FIRMAS//
//1
void Inicializar();
void ImprimirTexto();
void ImprimirDiccionario();

// 2
void Destruir();

//3
TipoRetorno InsertarLinea();
void InsertarLinea();
void ImprimirTexto();

// 4
TipoRetorno BorrarLinea(Posicion linea);

//5
TipoRetorno InsertarPalabra(Posicion linea, Posicion pos, std::string palabra);
InsertarPalabra();

//6
TipoRetorno BorrarPalabra(Posicion linea, Posicion pos);

//7
TipoRetorno ImprimirTexto();

//8
TipoRetorno IngresarPalabraDiccionario(std::string palabra);

//9
TipoRetorno ImprimirDiccionario();

//10
TipoRetorno ImprimirTextoIncorrecto();

//11
TipoRetorno AgregarIncorrectasAlDiccionario();




///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////FUNCIONES/////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////


void Inicializar(){

}
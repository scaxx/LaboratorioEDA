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

//una palabra del texto (lista doble dentro de linea)
struct nodoPalabra{
    string palabra;
    nodoPalabra *sig;
    nodoPalabra *ant;
};

//una linea del texto (lista doble con cola)
struct nodoLinea{
    nodoPalabra *primeraPalabra;
    nodoPalabra *ultimaPalabra;
    unsigned int cantPalabras;
    nodoLinea *sig;
    nodoLinea *ant;
};

struct Texto{
    nodoLinea *primera;
    nodoLinea *ultima;
    unsigned int cantLineas;
};

struct nodoDiccionario{
    string palabra;
    nodoDiccionario *izq;   
    nodoDiccionario *der;
};
typedef nodoDiccionario * Diccionario; 


///////////////////VARIABLES GLOBALES///////////////////

nodoDiccionario * Diccionario = nullptr;
Texto * texto = nullptr; 

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
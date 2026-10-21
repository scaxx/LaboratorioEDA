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

nodoDiccionario * diccionario = nullptr;
Texto texto = nullptr; 

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
    texto.primera = nullptr;
    texto.ultima = nullptr;
    texto.cantLineas = 0;
}






TipoRetorno IngresarPalabraDiccionario(string palabra){
   
    if(palabra == ""){ //palabra está vacía
        return ERROR;
    }
    int posicion = 0;
    while (palabra[posicion] != '\0') {
        if (palabra[posicion] == ' ') { //la palabra es un espacio o existe un espacio en el medio
            return ERROR;
        }
        posicion++;
    }
    // arbol vacío u hoja. 
    if (diccionario == nullptr){
        diccionario = new nodoDiccionario;
        diccionario->palabra = palabra;
        diccionario->izq= NULL;
        diccionario->der = NULL;
        return OK;
    }
    // la palabra ya existe
    if(palabra == diccionario->palabra){
        return ERROR;
    }

    Diccionario raiz = diccionario;
    TipoRetorno res;
    //buscamos si existe la palabra en sus hijos.
    if (palabra < raiz->palabra){
        diccionario = raiz->izq;
        res= IngresarPalabraDiccionario(palabra);
        raiz->izq = diccionario;
    }
    else{
        diccionario = raiz->der;
        res= IngresarPalabraDiccionario (palabra);
        raiz->der = diccionario;
    }

    diccionario = raiz;
    return res; 

}; 
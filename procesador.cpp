#include <iostream>
#include <string>

using namespace std;

#define MAX_CANT_PALABRAS_X_LINEA 3

typedef unsigned int Posicion;

enum _retorno {OK,ERROR,NO_IMPLEMENTADA};

typedef enum _retorno TipoRetorno;

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////ESTRUCTURAS////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

//Una palabra del texto (lista doble dentro de linea)
struct nodoPalabra{
    string palabra;
    nodoPalabra *sig;
    nodoPalabra *ant;
};

//Una linea del texto (lista doble con cola)
struct nodoLinea{
    nodoPalabra *primeraPalabra;
    nodoPalabra *ultimaPalabra;
    unsigned int cantPalabras;
    nodoLinea *sig;
    nodoLinea *ant;
};

//Estructura del texto. Tiene punteros a la primera línea y a la última para haccer más fácil el recorrido
struct Texto{
    nodoLinea *primera;
    nodoLinea *ultima;
    unsigned int cantLineas;
};

//Estructura diccionario (árbol binario de búsqueda)
struct nodoDiccionario{
    string palabra;
    nodoDiccionario *izq;   
    nodoDiccionario *der;
};
typedef nodoDiccionario * Diccionario; 


///////////////////VARIABLES GLOBALES///////////////////

nodoDiccionario * diccionario = nullptr; //Puntero a la raíz del diccionario
Texto texto; //Estructura texto, no es un puntero

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////FIRMAS/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

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


void Inicializar(){ //Creo que se hace así pero no sé si entendí bien, habría que revisarla
    //Texto no tiene líneas para comenzar de cero
    texto.primera = nullptr;
    texto.ultima = nullptr;
    texto.cantLineas = 0;

    //Diccionario no tiene palabras y sus punteros apuntan a nullptr para comenzar de cero
    diccionario->palabra = "\0";
    diccionario->izq = nullptr;
    diccionario->der = nullptr;
}






TipoRetorno IngresarPalabraDiccionario(string palabra){
   
    if(palabra == ""){ //La palabra está vacía

        return ERROR;

    }

    int posicion = 0;

    while (palabra[posicion] != '\0') {

        if (palabra[posicion] == ' ') { //La palabra es un espacio o existe un espacio en el medio
            return ERROR;
        }
        posicion++;

    }
    // Árbol vacío u hoja. 
    if (diccionario == nullptr){

        diccionario = new nodoDiccionario;
        diccionario->palabra = palabra;
        diccionario->izq= nullptr;
        diccionario->der = nullptr;
        return OK;

    }
    //La palabra ya existe
    if(palabra == diccionario->palabra){

        return ERROR;
    
    }

    //Hacemos una copia del puntero al diccionario e inicializamos la variable res que guarda lo que devuelve la llamada interna (OK, ERROR)
    Diccionario raiz = diccionario;
    TipoRetorno res;

    //La palabra no está en la raíz, si es menor a la palabra que tiene el nodo actual vamos a buscar por la izquierda
    if (palabra < raiz->palabra){

        diccionario = raiz->izq; //Trabajamos con el subárbol izquierdo
        res= IngresarPalabraDiccionario(palabra); //Llamamos a la función para trabajar con el siguiente nodo del árbol
        raiz->izq = diccionario; //Si se agregó otro nodo al árbol, enganchamos el nodo nuevo a su padre

    } else { //Si la palabra no es menor al nodo actual, entonces buscamos por la derecha

        diccionario = raiz->der; //Trabajamos con el subárbol derecho
        res= IngresarPalabraDiccionario (palabra); //Llamamos a la función para trabajar con el siguiente nodo del árbol
        raiz->der = diccionario; //Si se agregó otro nodo al árbol, enganchamos el nodo nuevo a su padre

    }

    //El puntero del diccionario había quedado apuntando a un hijo, ahora lo devolvemos a la raíz y devolvemos lo que dio la llamada interna (OK, ERROR)
    diccionario = raiz;
    return res; 

}

TipoRetorno ImprimirDiccionario() {

    //Si el diccionario está vacío
    if (diccionario == nullptr) {

        cout << "El diccionario está vacío" << endl;
        return OK;

    }

    //Guardamos la raíz para no perderla
    Diccionario raiz = diccionario;

    //Primero devolvemos todo lo de la izquierda
    if (raiz->izq != nullptr) { //Verifico que el siguiente nodo a la izquierda no sea nullptr porque sino se ejecuta el caso base (diccionario vacío)

        diccionario = raiz->izq; //Guardo el nuevo subárbol que voy a utilizar
        ImprimirDiccionario(); //Llamo a la función para imprimir el subárbol
        diccionario = raiz; //Vuelvo a ubicar la raíz para no perderla

    }

    //Ahora imprimimos la palabra actual
    cout << raiz->palabra << endl;

    //Ahora devolvemos todo lo del lado derecho
    if (raiz->der != nullptr) { //Verifico que el siguiente nodo a la derecha no sea nullptr (mismo caso que hacia la izquierda)

        diccionario = raiz->der; //Guardo el nuevo subárbol que voy a utilizar
        ImprimirDiccionario(); //Llamo a la función para imprimir el subárbol
        diccionario = raiz; //Vuelvo a ubicar la raíz para no perderla

    }

    return OK;

}
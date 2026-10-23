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
typedef nodoPalabra * Palabra; 

//Una linea del texto (lista doble con cola)
struct nodoLinea{
    nodoPalabra *primeraPalabra;
    nodoPalabra *ultimaPalabra;
    unsigned int cantPalabras;
    nodoLinea *sig;
    nodoLinea *ant;
};
typedef nodoLinea * Linea; 

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
//void ImprimirTexto();
//void ImprimirDiccionario();

// 2
void Destruir();

//3
TipoRetorno InsertarLinea();
//void InsertarLinea();
//void ImprimirTexto();

// 4
TipoRetorno BorrarLinea(Posicion linea);

//5
TipoRetorno InsertarPalabra(Posicion linea, Posicion pos, std::string palabra);
//void InsertarPalabra();

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
////////////////////////////////////////FIRMAS AUXILIARES&/////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

//Función auxiliar que recibe el diccionario y elimina todo su contenido
void DestruirDiccionario();
//Función auxiliar que recibe el texto y elimina todo su contenido
void DestruirTexto();

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////FUNCIONES/////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

//Función auxiliar que trabaja con el diccionario y elimina todo su contenido
void DestruirDiccionario() {

    //Vaciamos el diccionario
    if (diccionario != nullptr) { //Si el diccionario no está vacío comenzamos a operar

        Diccionario raiz = diccionario; //Guardamos la raíz del diccionario para operar

        //Revisamos que el lado izquierdo no esté vacío
        if (raiz->izq != nullptr) {

            //Nos movemos hacia la izquierda
            diccionario = raiz->izq;
            DestruirDiccionario(); //Llamamos a la función para seguir recorriendo recursivamente

        }

        //Ahora revisamos que el lado derecho no esté vacío
        if (raiz->der != nullptr) {

            //Nos movemos hacia la derecha
            diccionario = raiz->der;
            DestruirDiccionario(); //Llamamos a la función para seguir recorriendo recursivamente

        }

        //Borramos el nodo actual
        delete raiz;
        diccionario = nullptr; //Dejamos el nodo en null

    }

}

//Función auxiliar que trabaja con el texto y elimina todo su contenido
void DestruirTexto() {

    //Vaciamos el texto
    if (texto.cantLineas != 0) { //Si el texto tiene 1 o más líneas

        //Un contador para saber en qué línea estoy
        Posicion linea = texto.cantLineas;
        //Un puntero a la última línea del texto
        Linea auxLinea = texto.ultima;
        //Un puntero auxiliar para eliminar líneas
        Linea aBorrarL = nullptr;
        //Un puntero a null para manejar las palabras de las líneas
        nodoPalabra * auxPalabra = nullptr;
        //Un puntero auxiliar para eliminar palabras;
        nodoPalabra * aBorrarP = nullptr;
        
        //Bucle para recorrer las líneas del texto
        while (linea > 0) {

            //Miramos la nueva palabra que vamos a utilizar
            auxPalabra = auxLinea->ultimaPalabra;

            //Bucle para recorrer las palabras de cada línea
            while (auxPalabra != nullptr) {

                //Guardamos la última palabra de la línea
                aBorrarP = auxPalabra;
                //Nos movemos a la palabra anterior
                auxPalabra = auxPalabra->ant;
                //Borramos la última palabra
                delete aBorrarP;

            }
            
            //Guardamos la línea
            aBorrarL = auxLinea;
            //Nos movemos a la línea anterior
            auxLinea = auxLinea->ant;
            //Disminuimos el contador de líneas
            linea--;
            //Borramos la última línea
            delete aBorrarL;

        }

        //Dejamos el puntero en nullptr
        aBorrarP = nullptr;
        //Dejamos el puntero en null
        aBorrarL = nullptr;

    }

    //Seteo los valores del texto a cero
    texto.cantLineas = 0;
    texto.primera = nullptr;
    texto.ultima = nullptr;

}

//Función para limpiar texto y diccionario
void Destruir () {

    //LLamamos a las funciones auxiliares que me permiten liberar el diccionario y el texto
    DestruirDiccionario();
    DestruirTexto();    

}

void Inicializar(){ //Iniciamos de cero, se liberan los valores anteriores antes de comenzar
    
    //Llamo a esta función para vaciar el texto y el diccionario
    Destruir();
    
    
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
    TipoRetorno res; //Inicializamos esta variable para guardar el resultado de cada llamada, al final retornamos este resultado

    //La palabra no está en la raíz, si es menor a la palabra que tiene el nodo actual vamos a buscar por la izquierda
    if (palabra < raiz->palabra){

        diccionario = raiz->izq; //Trabajamos con el subárbol izquierdo
        res = IngresarPalabraDiccionario(palabra); //Llamamos a la función para trabajar con el siguiente nodo del árbol
        raiz->izq = diccionario; //Si se agregó otro nodo al árbol, enganchamos el nodo nuevo a su padre

    } else { //Si la palabra no es menor al nodo actual, entonces buscamos por la derecha

        diccionario = raiz->der; //Trabajamos con el subárbol derecho
        res = IngresarPalabraDiccionario (palabra); //Llamamos a la función para trabajar con el siguiente nodo del árbol
        raiz->der = diccionario; //Si se agregó otro nodo al árbol, enganchamos el nodo nuevo a su padre

    }

    //El puntero del diccionario había quedado apuntando a un hijo, ahora lo devolvemos a la raíz y devolvemos lo que dio la llamada interna (OK, ERROR)
    diccionario = raiz;
    return res; 

}

TipoRetorno ImprimirDiccionario() {

    //Si el diccionario está vacío
    if (diccionario == nullptr) {

        cout << "Diccionario vacio" << endl;
        return OK;

    }

    //Guardamos la raíz para no perderla
    Diccionario raiz = diccionario;

    //Primero imprimimos todo lo de la izquierda
    if (raiz->izq != nullptr) { //Verifico que el siguiente nodo a la izquierda no sea nullptr porque sino se ejecuta el caso base (diccionario vacío)

        diccionario = raiz->izq; //Guardo el nuevo subárbol que voy a utilizar
        ImprimirDiccionario(); //Llamo a la función para imprimir el subárbol
        diccionario = raiz; //Vuelvo a ubicar la raíz para no perderla

    }

    //Ahora imprimimos la palabra actual
    cout << raiz->palabra << endl;

    //Ahora imprimimos todo lo del lado derecho
    if (raiz->der != nullptr) { //Verifico que el siguiente nodo a la derecha no sea nullptr (mismo caso que hacia la izquierda)

        diccionario = raiz->der; //Guardo el nuevo subárbol que voy a utilizar
        ImprimirDiccionario(); //Llamo a la función para imprimir el subárbol
        diccionario = raiz; //Vuelvo a ubicar la raíz para no perderla

    }

    return OK;

}

/*Definimos la función para insertar líneas con O(1),
por lo que no recorremos el texto cada vez que deseamos insertar
una nueva línea, sólo miramos la última*/
TipoRetorno InsertarLinea() {

    //Creo la nueva línea que se va a insertar
    Linea nuevaLinea = new nodoLinea;
    //Agregamos la línea en nullptr
    nuevaLinea->sig = nullptr; 
    //Agregamos la línea en nullptr
    nuevaLinea->ant = nullptr; 
    //Marco a dónde apuntan los punteros de primera y última palabra
    nuevaLinea->primeraPalabra = nullptr;
    nuevaLinea->ultimaPalabra = nullptr;
    //Seteamos la cantidad de palabras que tiene la línea
    nuevaLinea->cantPalabras = 0;

    //Si es la primera línea de todo el texto
    if (texto.cantLineas == 0) {
        
        //Ubico la nueva línea en su posición en el texto
        texto.primera = nuevaLinea;
        texto.ultima = nuevaLinea;
        texto.cantLineas++;

    } else { //No es la primera línea del texto

        //Ubico la nueva línea al final del texto
        nuevaLinea->ant = texto.ultima; //Engancho el ant de la línea nueva apunta a la última que está en el texto 
        texto.ultima->sig = nuevaLinea; //Engancho el sig de la última línea apunta a la línea nueva
        texto.ultima = nuevaLinea; //Ahora la última línea del texto es la línea que acabamos de agregar
        texto.cantLineas++; //Aumentamos el contador de líneas
    
    }

    //La consigna dice "Siempre retorna OK"
    return OK; 

}

TipoRetorno ImprimirTexto() {

    //Primero verificamos si el texto está vacío
    if (texto.cantLineas == 0) {

        cout << "Texto vacio" << endl;
        //La consigna dice "Retorna OK"
        return OK;

    }

    //Un contador para saber en qué línea estoy
    Posicion linea = 1;
    //Un puntero a la primera línea del texto
    Linea auxLinea = texto.primera;
    //Un puntero a null para manejar las palabras de las líneas
    nodoPalabra * auxPalabra = nullptr;
    
    //Bucle para recorrer las líneas del texto
    while (linea <= texto.cantLineas) {

        //Imprimimos el número de línea
        cout << linea << ":";
        //Miramos la nueva palabra que vamos a utilizar
        auxPalabra = auxLinea->primeraPalabra;

        //Bucle para recorrer las palabras de cada línea
        while (auxPalabra != nullptr) {

            //Imprimo la palabra y un espacio
            cout << " " << auxPalabra->palabra;

            //Nos movemos a la siguiente palabra
            auxPalabra = auxPalabra->sig;

        }
        
        //Pasamos a la siguiente línea
        cout << endl;
        //Nos movemos a la siguiente línea
        auxLinea = auxLinea->sig;
        //Aumentamos el contador de líneas
        linea++;

    }

    //La consigna dice "Retorna OK"
    return OK;

}

int main() {

    //Pruebas
    Inicializar();
    ImprimirTexto();
    InsertarLinea();
    InsertarLinea();
    ImprimirTexto();
    ImprimirDiccionario();
    IngresarPalabraDiccionario("llueve");
    IngresarPalabraDiccionario("Hoy");
    IngresarPalabraDiccionario("poco");
    IngresarPalabraDiccionario("paraguas");
    IngresarPalabraDiccionario("y");
    IngresarPalabraDiccionario("hoy");
    ImprimirDiccionario();
    return 0;

}
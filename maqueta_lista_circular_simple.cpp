#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct Nodo{
    int dato;
    struct Nodo* sig;
}NodoA;


NodoA* crear_nodo(NodoA* cabecera, int dato);
void insertar_cabeza(NodoA*& cabecera, int dato);
void insertar_cola(NodoA*& cabecera, int dato);
NodoA* buscar(NodoA* cabecera, int dato);
void mostrar(NodoA* cabecera);
void eliminar(NodoA*& cabecera, int dato);
// Ejercicios
void insertar_despues(NodoA*& cabecera, int despues_de, int dato_nuevo);
void insertar_antes(NodoA*& cabecera, int antes_de, int dato_nuevo);

int main() {
    NodoA* puntero_lista = NULL;
    mostrar(puntero_lista);
    insertar_cola(puntero_lista, 1);
    mostrar(puntero_lista);
    insertar_cola(puntero_lista, 2);
    mostrar(puntero_lista);
    insertar_cola(puntero_lista, 3);
    mostrar(puntero_lista);
    insertar_cola(puntero_lista, 4);
    mostrar(puntero_lista);
    insertar_cola(puntero_lista, 5);
    mostrar(puntero_lista);
    eliminar(puntero_lista, 1);
    mostrar(puntero_lista);

    return 0;
}

NodoA* crear_nodo(NodoA* cabecera, int dato){
    NodoA* nuevo_nodo = (NodoA*) malloc (sizeof(NodoA));
    nuevo_nodo->dato = dato;
    nuevo_nodo->sig = cabecera;
    return nuevo_nodo;
}

void insertar_cabeza(NodoA*& cabecera, int dato){
    /*
        si no hay nada una insercion normal segun el esquema
    */
    if(cabecera == NULL){
        cabecera = crear_nodo(NULL, dato);
        cabecera->sig = cabecera;
    }
    else{
        /*
            al crear apuntamos al que le sigue a cabecera y 
            terminamos de enlazar, pero al final movemos 
            cabecera para que ocupe el que acabamos de poner
        */
        NodoA* nuevo_nodo = crear_nodo(cabecera->sig, dato);
        cabecera->sig = nuevo_nodo;
        cabecera = nuevo_nodo;
    }
}

void insertar_cola(NodoA*& cabecera, int dato){
    if(cabecera == NULL){
        cabecera = crear_nodo(NULL, dato);
        cabecera->sig = cabecera;
    }
    else{
        /*
            aca ponemos un auxiliar justo antes de cabecera
            el esquema usando do while es el siguiente:
            y la condicion es aux->sig != cabecera
            luego solo hacemos el enlace, no hay que mover
            la cabecera porque insertamos al final y ya
        */
        NodoA* aux = cabecera;
        do{
            aux = aux->sig;
        } while(aux->sig != cabecera);
        aux->sig = crear_nodo(cabecera, dato);
    }
}

NodoA* buscar(NodoA* cabecera, int dato){
    /*
        el esquema de recorrido completo usando do while
        es el sgte usando la siguiente evaluacion
        while(aux != cabecera)
        luego solo preguntamos y si encuentra devuelve
        de lo contrario al final retorna NULL
    */
    NodoA* aux = cabecera;
    if(cabecera != NULL){
        do{
            if(aux->dato == dato){
                return aux;
            }
            aux = aux->sig;
        } while(aux != cabecera);
    }
    return NULL;
}

void eliminar(NodoA*& cabecera, int dato){
    /*
        preguntamos por el elemento con la funcion buscar
    */
    NodoA* nodo_eliminar = buscar(cabecera, dato);
    if (nodo_eliminar != NULL){
        /*
            si solo hay un elemento simplemente eliminamos y ponemos
            cabecera == NULL, en esta condicion no importa el orden
            podemos eliminar y luego apuntar a NULL o viceversa
        */
        if(nodo_eliminar == cabecera && nodo_eliminar->sig == cabecera){
            cabecera = NULL;
            delete(nodo_eliminar);
        }
        else{
            /*
                en el panorama normal siempre pondremos un auxiliar
                justo detras del que queremos eliminar y para ello 
                usamos el esquema de do while:
                while(aux->sig != nodo_eliminar)
                con esto lo dejamos justo antes del que queremos eliminar
            */
            NodoA* aux = cabecera;
            do{
                aux = aux->sig;
            } while(aux->sig != nodo_eliminar);
            /*
                luego hacemos las conexiones y eliminamos el nodo
                al final preguntamos si el nodo era el primero para 
                mover la cabecera al siguiente, es decir:
                cabecera = cabecera->sig;
            */
            aux->sig = nodo_eliminar->sig;
            if(nodo_eliminar == cabecera){
                cabecera = cabecera->sig;
            }
            delete(nodo_eliminar);
        }
    }
    else{
        cout << "No encontrado!" << endl;
    }
}

void mostrar(NodoA* cabecera){
    /*
        lo más facil de todo, solo un recorrido completo e
        imprimir, ya sabemos que para el esquema de do
        while es: while(aux != cabecera)
    */
    NodoA* aux = cabecera;
    cout << "CAB->";
    if(cabecera != NULL){
        do{
            cout << "[" << aux->dato << "]->";
            aux = aux->sig;
        }while(aux != cabecera);
    }
    cout << "CAB" << endl;
}

// Ejercicios

void insertar_despues(NodoA*& cabecera, int despues_de, int dato_nuevo){
    /*
        buscamos nuestro nodo objetivo, es decir, el nodo despues
        del que vamos a insertar
    */
    NodoA* nodo_objetivo = buscar(cabecera, despues_de);
    if (nodo_objetivo != NULL){
        /*
            si el nodo es encontrado entonces creamos un nuevo nodo
            con el apuntador siguiente: nodo_objetivo->sig
            luego hacemos: nodo_objetivo->sig = nuevo_nodo;
            con eso tenemos los dos movimientos, ya que cabecera 
            nunca cambia
        */
        NodoA* nuevo_nodo = crear_nodo(nodo_objetivo->sig, dato_nuevo);
        nodo_objetivo->sig = nuevo_nodo;
    }
    else{
        cout << "No encontrado" << endl;
    }
}

void insertar_antes(NodoA*& cabecera, int antes_de, int dato_nuevo){
    /*
        buscamos nuestro nodo objetivo, es decir, el nodo despues
        del que vamos a insertar
    */
    NodoA* nodo_objetivo = buscar(cabecera, despues_de);
    if (nodo_objetivo != NULL){
        /*
            ponemos un auxiliar antes del nodo del cual vamos
            a ingresar y procedemos a hacer los movimientos
        */
        NodoA* aux = cabecera;
        do{
            aux = aux->sig;
        } while(aux->sig != nodo_objetivo);
        NodoA* nuevo_nodo = crear_nodo(nodo_objetivo, dato_nuevo);
        aux->sig = nuevo_nodo;
        /*
            si el nuevo nodo esta detras de cabecera, es decir
            insertamos el nodo justo detras de la cabecera
            entonces movemos la cabecera ya que ese nodo nuevo
            seria la cabecera
        */
        if (nuevo_nodo->sig == cabecera){
            cabecera = nuevo_nodo;
        }
    }
    else{
        cout << "No encontrado" << endl;
    }
}

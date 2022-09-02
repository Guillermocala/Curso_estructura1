#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct Nodo{
    int dato;
    struct Nodo* sig;
    struct Nodo* ant;
}NodoA;

NodoA* crear_nodo(NodoA* cabecera, int dato);
void insertar_cabeza(NodoA*& cabecera, int dato);
void insertar_cola(NodoA*& cabecera, int dato);
NodoA* buscar(NodoA* cabecera, int dato);
void mostrar(NodoA* cabecera);
void eliminar(NodoA*& cabecera, int dato);
void modificar(NodoA*& cabecera, int dato_buscar, int dato_nuevo);


int main() {

    NodoA* puntero_lista = NULL;
    insertar_cola(puntero_lista, 1);
    insertar_cola(puntero_lista, 2);
    insertar_cola(puntero_lista, 3);
    insertar_cola(puntero_lista, 4);
    insertar_cola(puntero_lista, 5);
    mostrar(puntero_lista);
    modificar(puntero_lista, 2, 6);
    mostrar(puntero_lista);

    return 0;
}

NodoA* crear_nodo(NodoA* nodo_trasero, NodoA* nodo_delantero, int dato){
    NodoA* nuevo_nodo = (NodoA*) malloc (sizeof(NodoA));
    nuevo_nodo->dato = dato;
    nuevo_nodo->sig = nodo_delantero;
    nuevo_nodo->ant = nodo_trasero;
    return nuevo_nodo;
}

void insertar_cabeza(NodoA*& cabecera, int dato){
    if(cabecera == NULL){
        cabecera = crear_nodo(NULL, NULL, dato);
    }
    else{
        NodoA* nuevo_nodo = crear_nodo(NULL, NULL, dato);
        nuevo_nodo->sig = cabecera;
        cabecera->ant = nuevo_nodo;
        cabecera = nuevo_nodo;
    }
}

void insertar_cola(NodoA*& cabecera, int dato){
    if(cabecera == NULL){
        cabecera = crear_nodo(NULL, NULL, dato);
    }
    else{
        NodoA* aux = cabecera;
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        aux->sig = crear_nodo(aux->ant, NULL, dato);
    }
}

NodoA* buscar(NodoA* cabecera, int dato){
    NodoA* aux = cabecera;
    while(aux != NULL){
        if(aux->dato == dato){
            return aux;
        }
        aux = aux->sig;
    }
    return NULL;
}

void eliminar(NodoA*& cabecera, NodoA* nodo_eliminar){
    if(nodo_eliminar->ant != NULL){
        nodo_eliminar->ant->sig = nodo_eliminar->sig; 
    }
    else{
        cabecera = cabecera->sig;
    }
    if(nodo_eliminar ->sig != NULL){
        nodo_eliminar->sig->ant = nodo_eliminar->ant;
    }
    delete(nodo_eliminar);
}

void mostrar(NodoA* cabecera){
    cout << "CAB->";
    NodoA* aux = cabecera;
    while(aux != NULL){
        cout << "[" << aux->dato << "]->";
        aux = aux->sig;
    }
    cout << "NULL" << endl;
}

void modificar(NodoA*& cabecera, int dato_buscar, int dato_nuevo){
    NodoA* nodo_objetivo = buscar(cabecera, dato_buscar);
    if(nodo_objetivo != NULL){
        nodo_objetivo->dato = dato_nuevo;
    }
    else{
        cout << "No encontrado para modificar!" << endl;
    }
}
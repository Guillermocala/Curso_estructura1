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
int buscar(NodoA* cabecera, int dato);
void mostrar(NodoA* cabecera);
void eliminar(NodoA*& cabecera, int dato);


int main() {

    NodoA* puntero_lista = NULL;
    insertar_cabeza(puntero_lista, 1);
    insertar_cabeza(puntero_lista, 2);
    insertar_cabeza(puntero_lista, 3);
    insertar_cabeza(puntero_lista, 4);
    insertar_cabeza(puntero_lista, 5);
    mostrar(puntero_lista);
    int pos = buscar(puntero_lista, 3);
    cout << "pos: " << pos << endl;
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
    cabecera = crear_nodo(cabecera, dato);
}

void insertar_cola(NodoA*& cabecera, int dato){
    if(cabecera == NULL){
        cabecera = crear_nodo(cabecera, dato);
    }
    else{
        NodoA* aux = cabecera;
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        aux->sig = crear_nodo(NULL, dato);
    }
}

int buscar(NodoA* cabecera, int dato){
    int posicion = 0, encontrado = 0;
    NodoA* aux = cabecera;
    while(aux != NULL){
        if(aux->dato == dato){
            encontrado = 1;
            break;
        }
        posicion++;
        aux = aux->sig;
    }
    if(encontrado == 1){
        return posicion;
    }
    else{
        return -1;
    }
}

void eliminar(NodoA*& cabecera, int dato){
    int posicion = buscar(cabecera, dato);
    if (posicion != -1){
        NodoA* aux = cabecera;
        if(posicion == 0){
            cabecera = cabecera->sig;
            free(aux);
        }
        else{
            for(int i = 0; i < (posicion - 1); i++){
                aux = aux->sig;
            }
            NodoA* nodo_eliminar = aux->sig;
            aux->sig = nodo_eliminar->sig;
            free(nodo_eliminar);
        }
    }
    else{
        cout << "No encontrado!" << endl;
    }
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
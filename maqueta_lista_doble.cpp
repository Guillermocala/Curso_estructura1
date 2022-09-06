#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct Nodo{
    int dato;
    struct Nodo* sig;
    struct Nodo* ant;
}NodoA;


NodoA* crear_nodo(NodoA* nodo_trasero, NodoA* nodo_delantero, int dato);
void insertar_cabeza(NodoA*& cabecera, int dato);
void insertar_cola(NodoA*& cabecera, int dato);
NodoA* buscar(NodoA* cabecera, int dato);
void mostrar(NodoA* cabecera);
void eliminar(NodoA*& cabecera, int dato);
void modificar(NodoA*& cabecera, int dato_buscar, int dato_nuevo);
// Ejercicios
void insertar_despues(NodoA*& cabecera, int despues_de, int dato_nuevo);
void insertar_antes(NodoA*& cabecera,int antes_de, int dato_nuevo);
void insertar_ordenado(NodoA*& cabecera, int dato);


int main() {

    NodoA* puntero_lista = NULL;
    insertar_cola(puntero_lista, 1);
    insertar_cola(puntero_lista, 2);
    insertar_cola(puntero_lista, 3);
    insertar_cola(puntero_lista, 4);
    insertar_cola(puntero_lista, 5);
    mostrar(puntero_lista);
    insertar_antes(puntero_lista, 4, 23);
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
        aux->sig = crear_nodo(aux, NULL, dato);
        
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

// Ejercicios

void insertar_despues(NodoA*& cabecera, int despues_de, int dato_nuevo){
	NodoA* aux = buscar(cabecera, despues_de);
	if(aux == NULL){
		cout << "No se encontro" << endl;
	}else{
		if(aux->sig == NULL){
			aux->sig = crear_nodo(aux, NULL, dato_nuevo);
		}else{
			NodoA* aux2 = aux->sig;
			aux->sig = crear_nodo(aux, aux2, dato_nuevo);
			aux2->ant = aux->sig;
		}
	}
}

void insertar_antes(NodoA*& cabecera,int antes_de, int dato_nuevo){
	NodoA* aux = buscar(cabecera, antes_de);
	if(aux == NULL){
		cout<<"No se encontro"<<endl;
	}else{
		if(aux->ant == NULL){
            /*
                si esta en el primer nodo entonces colocamos
                un auxiliar en la cabecera para hacer facil
                el ultimo movimiento: aux2->ant = cabecera;
                en la cabeza al crear el nodo recibe de primero
                null(primer nodo), luego la cabecera que luego
                va a reemplazar
            */
            NodoA* aux2 = cabecera;
			cabecera = crear_nodo(NULL, cabecera, dato_nuevo);
            aux2->ant = cabecera;
		}else{
            /*
                en cualquier otro caso colocamos un auxiliar antes
                y nos apoyamos del mismo para realizar los movimientos
            */
			NodoA* aux2 = aux->ant;
			aux2->sig = crear_nodo(aux2, aux, dato_nuevo);
			aux->ant = aux2->sig;
		}
	}
}

void insertar_ordenado(NodoA*& cabecera, int dato){
	if(cabecera == NULL){
		cabecera = crear_nodo(NULL, NULL, dato);
	}
	else{
		bool insertado = false;
		NodoA* aux = cabecera;
		if (aux->dato > dato){
			NodoA* aux2 = cabecera;
			cabecera = crear_nodo(NULL, cabecera, dato);
			aux2->ant = cabecera;
		}
		else{
			while(aux->sig != NULL){
				if(aux->sig->dato > dato){
					NodoA* aux2 = aux->sig;
					aux->sig = crear_nodo(aux, aux2, dato);
					aux2->ant = aux->sig;
					insertado = true;
					break;
				}
				aux = aux->sig;
			}
			if (insertado == false){
				aux->sig = crear_nodo(aux, NULL, dato);
			}
		}
	}
}
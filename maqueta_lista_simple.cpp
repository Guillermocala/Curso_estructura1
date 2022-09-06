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
// Ejercicios
float promedio(NodoA* cabecera);
void insertar_antes(NodoA*& cabecera, int posicion, int dato);
void insertar_despues(NodoA*& cabecera, int posicion, int dato);
void insertar_ordenado(NodoA*& cabecera, int dato);


int main() {
    NodoA* puntero_lista = NULL;
    insertar_cabeza(puntero_lista, 1);
    insertar_cabeza(puntero_lista, 2);
    insertar_cabeza(puntero_lista, 3);
    insertar_cabeza(puntero_lista, 4);
    insertar_cabeza(puntero_lista, 5);
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

// Ejercicios

float promedio(NodoA* cabecera){
	float suma = 0, cantidad = 0, promedio;
	NodoA* aux = cabecera;
	while (aux != NULL){
		suma = aux->dato + suma;
		cantidad++;
		aux = aux->sig;
	}
	promedio = suma / cantidad;
	return promedio;
}

void insertar_antes(NodoA*& cabecera, int posicion, int dato){
    NodoA* aux = cabecera;
    /* 
        Si esta en el primero insertamos, sino colocamos un auxiliar
        detras de el para proceder a insertar
    */
    if(posicion == 0){
        cabecera = crear_nodo(cabecera, dato);
    }
    else{
        /*
            Colocamos auxiliar detras de donde vamos a insertar 
            con (posicion - 1)
        */
        for(int i = 0; i < (posicion - 1); i++){
            aux = aux->sig;
        }
        aux->sig = crear_nodo(aux->sig, dato);	
    }
}

void insertar_despues(NodoA*& cabecera, int posicion, int dato){
    NodoA* aux = cabecera;
    /*
        Si la posicion es diferente del primer nodo movemos el auxiliar
        hasta la posicion y luego procedemos a insertar
    */
    if(posicion != 0){
    	for(int i = 0; i < posicion; i++){
            aux = aux->sig;
        }
    }
	aux->sig = crear_nodo(aux->sig, dato);
}

void insertar_ordenado(NodoA*& cabecera, int dato){
    /*
        Si la lista esta vacia hacemos una insercion normal
    */
	if(cabecera == NULL){
		cabecera = crear_nodo(NULL, dato);
	}
	else{
        /*
            si el dato a ingresar sera el primero, es decir, el 
            dato es menor que el primero, entonces insertamos 
            segun cabecera
        */
		bool insertado = false;
		Nodo* aux = cabecera;
		if (aux->dato > dato){
			cabecera = crear_nodo(cabecera, dato);
		}
		else{
            /*
                recorremos bajo esta condicion para no usar variables
                externas y el unico problema es que al llegar al ultimo
                toca verificar ese ultimo dato
            */
			while(aux->sig != NULL){
                /*
                    siempre vamos preguntando por el valor siguiente al
                    que estamos apuntando con aux, por eso se usa
                    aux->sig->dato
                */
				if(aux->sig->dato > dato){
					aux->sig = crear_nodo(aux->sig, dato);
					insertado = true;
					break;
				}
				aux = aux->sig;
			}
            /*
                una vez llegado al final y si no hemos insertado nada
                entonces solo insertamos al final
            */
			if (insertado == false){
				aux->sig = crear_nodo(aux->sig, dato);
			}
		}
	}
}
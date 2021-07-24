#include "cola.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Structs
typedef struct nodo{
	void* dato;
	struct nodo* prox;
}nodo_t;

struct cola{
	nodo_t* prim;
	nodo_t* ult;
};
//


cola_t* cola_crear(void){
	cola_t* cola = malloc(sizeof(cola_t));
	if(cola == NULL){
		return NULL;
	}
	cola->prim = NULL;
	cola->ult = NULL;
	return cola;
}

bool cola_esta_vacia(const cola_t *cola){
	return cola->prim == NULL;
}

void* cola_ver_primero(const cola_t *cola){
	if(cola_esta_vacia(cola)){
		return NULL;
	}
	return cola->prim->dato;
}

nodo_t* nodo_crear(void* valor){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if(nodo == NULL){
		return NULL;
	}
	nodo->dato = valor;
	nodo->prox = NULL;
	return nodo;
}

bool cola_encolar(cola_t *cola, void* valor){
	nodo_t* nodo = nodo_crear(valor);
	if(nodo == NULL){
		return false;
	}
	if(cola_esta_vacia(cola)){
		cola->prim = nodo;
	}
	else{
		cola->ult->prox = nodo;
	}
	cola->ult = nodo;
	return true;	
}

void* cola_desencolar(cola_t *cola){
	void* valor = cola_ver_primero(cola);
	if(!cola_esta_vacia(cola)){
		nodo_t* segundo = cola->prim->prox;
		free(cola->prim);
		cola->prim = segundo;
	}
	return valor;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)){
	while(!cola_esta_vacia(cola)){
		if(destruir_dato != NULL){
			destruir_dato(cola->prim->dato);
		}
		nodo_t* segundo = cola->prim->prox;
		free(cola->prim);
		cola->prim = segundo;
    }
	free(cola);
}

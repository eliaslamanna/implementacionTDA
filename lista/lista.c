#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Definicion de structs

typedef struct nodo{
	void* dato;
	struct nodo* prox;
}nodo_t;

struct lista{
	nodo_t* prim;
	nodo_t* ult;
	size_t largo;
};

struct lista_iter{
	nodo_t* ant;
	nodo_t* act;
	lista_t* lista;
};

//Primitivas de la lista

lista_t* lista_crear(void){
	lista_t* lista = malloc(sizeof(lista_t));
	if(lista == NULL){
		return NULL;
	}
	lista->prim = NULL;
	lista->ult = NULL;
	lista->largo = 0;
	return lista;
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

void lista_destruir(lista_t *lista, void destruir_dato(void*)){
	while(!lista_esta_vacia(lista)){
		if(destruir_dato != NULL){
			destruir_dato(lista->prim->dato);
		}
		nodo_t* segundo = lista->prim->prox;
		free(lista->prim);
		lista->prim = segundo;
		lista->largo -= 1;
    }
	free(lista);
}

bool lista_esta_vacia(const lista_t *lista){
	return lista->largo == 0;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_t* nodo = nodo_crear(dato);
	if(nodo == NULL){
		return false;
	}
	if(lista_esta_vacia(lista)){
		lista->prim = nodo;
	}
	else{
		lista->ult->prox = nodo;
	}
	lista->ult = nodo;
	lista->largo += 1;
	return true;	
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_t* nodo = nodo_crear(dato);
	if(nodo == NULL){
		return false;
	}
	if(lista_esta_vacia(lista)){
		lista->ult = nodo;
	}
	nodo_t* aux = lista->prim;
	lista->prim = nodo;
	lista->prim->prox = aux;
	lista->largo += 1;
	return true;
}	
	
void *lista_borrar_primero(lista_t *lista){	
	if(lista_esta_vacia(lista)){
		return NULL;
	}
	void* valor = lista_ver_primero(lista);
	nodo_t* segundo = lista->prim->prox;
	free(lista->prim);
	lista->prim = segundo;
	lista->largo -= 1;
	return valor;
}

void *lista_ver_primero(const lista_t *lista){
	if(lista_esta_vacia(lista)){
		return NULL;
	}
	return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
	if(lista_esta_vacia(lista)){
		return NULL;
	}
	return lista->ult->dato;
}

size_t lista_largo(const lista_t *lista){
	return lista->largo;
}

//Primitiva del iterador interno

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
	nodo_t* aux = lista->prim;
	while(aux != NULL){
		if(!(visitar(aux->dato,extra))){
			return;
		}
		aux = aux->prox;
	}
}

//Primitivas del iterador externo

lista_iter_t *lista_iter_crear(lista_t *lista){
	lista_iter_t* lista_iter = malloc(sizeof(lista_iter_t));
	if(lista_iter == NULL){
		return NULL;
	}
	lista_iter->act = lista->prim;
	lista_iter->ant = NULL;
	lista_iter->lista = lista;
	return lista_iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	if(lista_iter_al_final(iter)){
		return false;
	}
	iter->ant = iter->act;
	iter->act = iter->act->prox;
	return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
	if(lista_iter_al_final(iter)){
		return NULL;
	}
	return iter->act->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
	return iter->act == NULL;
}

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	if(lista_iter_al_final(iter)){
		nodo_t* aux = iter->lista->ult;
		lista_insertar_ultimo(iter->lista, dato);
		iter->act = iter->lista->ult;
		if(iter->lista->largo == 1){
			return true;
		}
		iter->ant = aux;
		iter->ant->prox = iter->act;
	}
	else if(iter->ant == NULL){
		nodo_t* aux = iter->act;
		lista_insertar_primero(iter->lista, dato);
		iter->act = iter->lista->prim;
		iter->act->prox = aux;
	}
	else{
		nodo_t* aux = nodo_crear(dato);
		if(aux == NULL){
		return false;
		}
		aux->prox = iter->act;
		iter->act = aux;
		iter->ant->prox = iter->act;
		iter->lista->largo += 1;
	}
	return true;
}
		
void *lista_iter_borrar(lista_iter_t *iter){
	if(lista_iter_al_final(iter)){
		return NULL;
	}
	void* valor = iter->act->dato;																																																				
	nodo_t* aux = iter->act;
	if(iter->lista->largo == 1){
		iter->lista->prim = NULL;
		iter->lista->ult = NULL;
		iter->act = NULL;
		iter->ant = NULL;
	}
	else if(iter->act == iter->lista->ult){
		iter->act = NULL;
		iter->ant->prox = iter->act;
		iter->lista->ult = iter->ant;
	}
	else if(iter->act == iter->lista->prim){
		nodo_t* segundo = iter->lista->prim->prox;
		iter->lista->prim = segundo;
		iter->act = iter->lista->prim;
	}
	else{
		iter->act = iter->act->prox;
		iter->ant->prox = iter->act;
	}
	iter->lista->largo -= 1;
	free(aux);
	return valor;
}

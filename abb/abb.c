#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "abb.h"
#include "pila.h"

typedef struct nodo_abb{
	struct nodo_abb* izq;
	struct nodo_abb* der;
	char* clave;
	void* dato;
}nodo_abb_t;

struct abb{
	nodo_abb_t* raiz;
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t destruir_dato;
	size_t cantidad;
};

struct abb_iter{
	nodo_abb_t* nodo_actual;
	pila_t* pila;
};

nodo_abb_t* abb_nodo_crear(void* valor, const char* clave){
	nodo_abb_t* nodo = malloc(sizeof(nodo_abb_t));
	if(nodo == NULL){
		return NULL;
	}
	char* aux = malloc(sizeof(char) * (strlen(clave) + 1));
	if(aux == NULL){
		free(nodo);
		return NULL;
	}
	strcpy(aux, clave);
	nodo->clave = aux;
	nodo->dato = valor;
	nodo->izq = NULL;
	nodo->der = NULL;
	return nodo;
}

void abb_nodo_destruir(const abb_t* arbol, nodo_abb_t* nodo){
	if(arbol->destruir_dato != NULL){
		arbol->destruir_dato(nodo->dato);
	}
	free(nodo->clave);
	free(nodo);
}

nodo_abb_t* abb_nodo_buscar(const abb_t* arbol, nodo_abb_t* nodo, const char* clave){
	if(nodo == NULL){
		return NULL;
	}
	int comparacion = arbol->cmp(nodo->clave, clave);
	if(comparacion == 0){
		return nodo;
	}
	else if(comparacion > 0){
		return abb_nodo_buscar(arbol, nodo->izq, clave);
	}
	else{
		return abb_nodo_buscar(arbol, nodo->der, clave);
	}
}

nodo_abb_t* abb_buscar_padre(const abb_t* arbol, nodo_abb_t* nodo_actual, nodo_abb_t* nodo_dado, pila_t* pila){
	if(arbol->cantidad == 1){
		return nodo_actual;
	}
	if(arbol->cmp(arbol->raiz->clave, nodo_dado->clave) == 0){
		return nodo_dado;
	}
	pila_apilar(pila,nodo_actual);
	if(arbol->cmp(nodo_actual->clave, nodo_dado->clave) == 0){
		pila_desapilar(pila);
		return pila_ver_tope(pila);
	}
	if(arbol->cmp(nodo_actual->clave, nodo_dado->clave) > 0){
		if(nodo_actual->izq == NULL){
			return nodo_actual;
		}
		return abb_buscar_padre(arbol, nodo_actual->izq, nodo_dado, pila);
	}
	else{
		if(nodo_actual->der == NULL){
			return nodo_actual;
		}
		return abb_buscar_padre(arbol, nodo_actual->der, nodo_dado, pila);
	}
}

void abb_swap_nodos(nodo_abb_t* nodo_1, nodo_abb_t* nodo_2){
	char* clave_aux = nodo_1->clave;
	void* dato_aux = nodo_1->dato;

	nodo_1->clave = nodo_2->clave;
	nodo_2->clave = clave_aux;
	nodo_1->dato = nodo_2->dato;
	nodo_2->dato = dato_aux;

	return;
}

size_t abb_cantidad_hijos(nodo_abb_t* nodo){
	size_t hijos = 0;
	if(nodo->der){
		hijos ++;
	}
	if(nodo->izq){
		hijos ++;
	}
	return hijos;
}

nodo_abb_t* abb_nodo_buscar_ultimo_izquierdo(nodo_abb_t* nodo){
	if(nodo->izq == NULL){
		return nodo;
	}
	return abb_nodo_buscar_ultimo_izquierdo(nodo->izq);
}

nodo_abb_t* abb_nodo_buscar_reemplazo(const abb_t* arbol, nodo_abb_t* nodo){
	if(nodo->der == NULL){
		return nodo;
	}
	return abb_nodo_buscar_ultimo_izquierdo(nodo->der);
}

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t* abb = malloc(sizeof(abb_t));
	if(abb == NULL){
		return NULL;
	}
	abb->cantidad = 0;
	abb->cmp = cmp;
	abb->destruir_dato = destruir_dato;
	abb->raiz = NULL;
	return abb;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	nodo_abb_t* nodo = abb_nodo_buscar(arbol, arbol->raiz, clave);
	return nodo != NULL;
}

void *abb_obtener(const abb_t *arbol, const char *clave){
	nodo_abb_t* nodo = abb_nodo_buscar(arbol, arbol->raiz, clave);
	if(nodo == NULL){
		return NULL;
	}
	return nodo->dato;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	nodo_abb_t* nodo = abb_nodo_buscar(arbol, arbol->raiz, clave);
	if(nodo != NULL){
		if(arbol->destruir_dato != NULL){
			arbol->destruir_dato(nodo->dato);
		}
		nodo->dato = dato;
		return true;
	}
	pila_t* pila = pila_crear();
	if(pila == NULL){
		return NULL;
	}
	nodo_abb_t* nodo_abb = abb_nodo_crear(dato, clave);
	if(nodo_abb == NULL){
		pila_destruir(pila);
		return false;
	}
	if(arbol->cantidad == 0){
		arbol->raiz = nodo_abb;
		arbol->cantidad ++;
	}
	else{
		nodo_abb_t* padre = abb_buscar_padre(arbol, arbol->raiz, nodo_abb, pila);
		if(arbol->cmp(padre->clave, nodo_abb->clave) > 0){
			padre->izq = nodo_abb;
			arbol->cantidad ++;
		}
		else{
			padre->der = nodo_abb;
			arbol->cantidad ++;
		}
	}
	pila_destruir(pila);
	return true;
}

size_t abb_cantidad(abb_t *arbol){
	return arbol->cantidad;
}

void *abb_borrar(abb_t *arbol, const char *clave){
	nodo_abb_t* nodo = abb_nodo_buscar(arbol, arbol->raiz, clave);
	if(nodo == NULL){
		return NULL;
	}
	
	if(arbol->cantidad == 1){
		void* valor = arbol->raiz->dato;
		abb_nodo_destruir(arbol, arbol->raiz);
		arbol->raiz = NULL;
		arbol->cantidad --;
		return valor;
	}
	void* valor;

	pila_t* pila = pila_crear();
	if(!pila) return NULL;
	if(abb_cantidad_hijos(nodo) == 0){
		nodo_abb_t* padre = abb_buscar_padre(arbol,arbol->raiz, nodo, pila);

		if(padre->izq == nodo){
			padre->izq = NULL;
		}
		else{
			padre->der = NULL;
		}
		valor = nodo->dato;
		abb_nodo_destruir(arbol, nodo);
		
	}
	else if(abb_cantidad_hijos(nodo) == 1){
		nodo_abb_t* hijo;
		if(nodo->der){
			hijo = nodo->der;
		}
		else{
			hijo = nodo->izq;
		}
		valor = nodo->dato;
		nodo_abb_t* padre_buscado = abb_buscar_padre(arbol, arbol->raiz, nodo, pila);
		//Ahora el hijo tiene la clave y el dato que hay que borrar
		if(arbol->raiz == nodo){
			arbol->raiz = hijo;
		}
		else if(arbol->cmp(padre_buscado->clave, nodo->clave) > 0){
			padre_buscado->izq = hijo;
		}
		else{
			padre_buscado->der = hijo;
		}
		
		abb_nodo_destruir(arbol, nodo);
	}
	else{
		nodo_abb_t* reemplazo = abb_nodo_buscar_reemplazo(arbol, nodo);
		nodo_abb_t* padre_reemplazo = abb_buscar_padre(arbol,arbol->raiz, reemplazo, pila);
		
		valor = nodo->dato;
		abb_swap_nodos(nodo, reemplazo);
		//Ahora el reemplazo tiene la clave y el dato que hay que borrar
		
		if(padre_reemplazo->izq == reemplazo){
			if(reemplazo->izq){
				padre_reemplazo->izq = reemplazo->izq;
			}
			else{
				padre_reemplazo->izq = reemplazo->der;
			}
		}
		else{
			if(reemplazo->izq){
				padre_reemplazo->der = reemplazo->izq;
			}
			else{
				padre_reemplazo->der = reemplazo->der;
			}
		}
		abb_nodo_destruir(arbol, reemplazo);
		
	}
	pila_destruir(pila);
	arbol->cantidad --;
	return valor;	
}

void _abb_destruir(abb_t* arbol, nodo_abb_t* nodo){
	if(nodo == NULL){
		return;
	}
	if(nodo->izq != NULL){
		_abb_destruir(arbol, nodo->izq);
	}
	if(nodo->der != NULL){
		_abb_destruir(arbol, nodo->der);
	}
	abb_nodo_destruir(arbol, nodo);
}

void abb_destruir(abb_t* arbol){
	if(arbol == NULL){
		return;
	}
	_abb_destruir(arbol, arbol->raiz);
	free(arbol);
}

//funciones iter

bool _abb_in_order(nodo_abb_t* nodo, bool visitar(const char*, void*, void*), void* extra){
	if(nodo == NULL) return true;
	
	if(!_abb_in_order(nodo->izq, visitar, extra)) return false;
	if(!visitar(nodo->clave,nodo->dato, extra)) return false;
	if(!_abb_in_order(nodo->der, visitar, extra)) return false;

	return true;
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
	_abb_in_order(arbol->raiz, visitar, extra);
}

void apilar_nodos(nodo_abb_t* nodo, pila_t* pila){
	if(nodo == NULL){
		return;
	}
	pila_apilar(pila, nodo);
	apilar_nodos(nodo->izq, pila);
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
	abb_iter_t* abb_iter = malloc(sizeof(abb_iter_t));
	if(abb_iter == NULL){
		return NULL;
	}
	pila_t* pila = pila_crear();
	if(pila == NULL){
		free(abb_iter);
		return NULL;
	}
	abb_iter->pila = pila;
	apilar_nodos(arbol->raiz, pila);
	return abb_iter;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
	return (pila_esta_vacia(iter->pila));
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
	if(abb_iter_in_al_final(iter)){
		return false;
	}
	nodo_abb_t* desapilado = pila_desapilar(iter->pila);
	apilar_nodos(desapilado->der, iter->pila);
	return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	if(abb_iter_in_al_final(iter)){
		return NULL;
	}
	nodo_abb_t* nodo = pila_ver_tope(iter->pila);
	return nodo->clave;
}

void abb_iter_in_destruir(abb_iter_t* iter){
	pila_destruir(iter->pila);
	free(iter);
}

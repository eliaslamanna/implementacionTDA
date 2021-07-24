#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
 
void pruebas_destruir_free(){
	lista_t* lista = lista_crear();
	void** vec = malloc(sizeof(void*) * 100);
	for(int i = 0; i < 100; i ++){
		vec[i] = malloc(sizeof(void*));
		lista_insertar_primero(lista, vec[i]);
	}
	lista_destruir(lista,free);
	free(vec);
}

void pruebas_destruir_null(){
	lista_t* lista = lista_crear();
	for(int i = 0; i < 5; i ++){
		lista_insertar_primero(lista, &i);
	}
	for(int i = 0; i < 5; i ++){
		lista_borrar_primero(lista);
	}
	lista_destruir(lista,NULL);
}

void chequear_invariante_insertar_ultimo(){
	lista_t* lista = lista_crear();
	int var_ult1 = 3;
    int var_ult2 = 4; 
	lista_insertar_ultimo(lista, &var_ult1);
	lista_insertar_ultimo(lista, &var_ult2);
	int *tope_ult = (int *)(lista_borrar_primero(lista));
	print_test("Se mantuvo la invariante al insertar ultimo", tope_ult == &var_ult1);
	lista_destruir(lista,NULL);
}

void chequear_invariante_insertar_primero(){
	lista_t* lista = lista_crear();
	int var1 = 5;
    int var2 = 9;
    lista_insertar_primero(lista, &var1);
    lista_insertar_primero(lista, &var2);
    int *tope1 = (int *)(lista_borrar_primero(lista));
    print_test("Se mantuvo la invariante al insertar primero", tope1 == &var2);
    lista_destruir(lista, NULL);
}

void desapilar_y_ver_tope_invalido(){
	lista_t* lista = lista_crear();
	int var = 8;
	lista_insertar_primero(lista, &var);
	lista_borrar_primero(lista);
	void* a = lista_borrar_primero(lista);
    print_test("Desapilar en una lista vacia es invalido", a == NULL);
    void* b = lista_ver_primero(lista);
    print_test("Ver el tope de una lista vacia es invalido", b == NULL);
    lista_destruir(lista, NULL);
}

void insertar_null(){
	lista_t* lista = lista_crear();
	void* nuevo = NULL;
    print_test("Se inserto un NULL", lista_insertar_primero(lista, nuevo));
    lista_borrar_primero(lista);
    print_test("Se borro el NULL", lista_esta_vacia(lista));
    lista_destruir(lista, NULL);
}

bool volumen(lista_t* lista){
	int vector[1000];
    for(int i = 0; i < 1000; i++){
		vector[i] = i;
        lista_insertar_ultimo(lista, &vector[i]);
    }
    for(int i = 0; i < 1000; i ++){
        int* nuevo_tope = (int*)(lista_borrar_primero(lista));
        if(*nuevo_tope != vector[i]){
			return false;
		}
    }
    return true;
}

bool prueba_lista_crear(){
	lista_t* lista = lista_crear();
	if(lista){
		lista_destruir(lista, NULL);
		return true;
	}
	lista_destruir(lista, NULL);
	return false;
}

bool prueba_lista_esta_vacia(){
    lista_t* lista = lista_crear();
    if(lista_esta_vacia(lista)){
    	lista_destruir(lista, NULL);
    	return true;
    }
    lista_destruir(lista, NULL);
    return false;
}

bool prueba_lista_desapilada_se_comporta_como_vacia(){
	lista_t* lista = lista_crear();
	int var1 = 6;
	int var2 = 7;
	lista_insertar_primero(lista, &var1);
	lista_insertar_primero(lista, &var2);
	lista_borrar_primero(lista);
	lista_borrar_primero(lista);
	if(lista_esta_vacia(lista)){
		lista_destruir(lista, NULL);
		return true;
	}
	lista_destruir(lista, NULL);
	return false;
}

bool prueba_volumen(){
	lista_t* lista = lista_crear();
	if(volumen(lista)){
		lista_destruir(lista, NULL);
		return true;
	}
	lista_destruir(lista, NULL);
	return false;
}

void prueba_lista_destruir(){
	lista_t*lista = lista_crear();
	lista_destruir(lista, NULL);
}

//Pruebas iteradores
bool suma(void* numero, void* sumatoria){
	*(int*)sumatoria += *(int*)numero;
	return true;
}
	
bool iter_interno(){
	lista_t* lis = lista_crear();
	int valor1 = 5;
    int valor2 = 9;
    int valor3 = 14;
    lista_insertar_primero(lis, &valor1);
    lista_insertar_primero(lis, &valor2);
	lista_insertar_primero(lis, &valor3);
	int resultado = 0;
	lista_iterar(lis, suma, &resultado);
	lista_destruir(lis,NULL);
	if(resultado == 28){
		return true;
	}
	return false;
}

bool iter_insertar_medio(){
	lista_t* lista = lista_crear();
	int elem = 10;
	int vector[3] = {3,5,7};
	for(int i = 0; i < 3; i ++){
		lista_insertar_ultimo(lista, &vector[i]);
	}
	lista_iter_t* iter = lista_iter_crear(lista);
	lista_iter_avanzar(iter);
	lista_iter_insertar(iter, &elem);
	lista_destruir(lista, NULL);
	free(iter);
	return true;
}

bool iter_insertar_al_final(){
	lista_t* lista = lista_crear();
	int elem1 = 4;
	int elem2 = 6;
	int elem3 = 10;
	lista_insertar_ultimo(lista, &elem1);
	lista_insertar_ultimo(lista, &elem2);
	lista_iter_t* iter = lista_iter_crear(lista);
	lista_iter_avanzar(iter);
	lista_iter_insertar(iter, &elem3);
	lista_destruir(lista, NULL);
	free(iter);
	return true;
}

bool iter_insertar_al_principio(){
	lista_t* lista = lista_crear();
	int elem1 = 2;
	int elem2 = 6;
	int elem3 = 9;
	lista_insertar_ultimo(lista, &elem1);
	lista_insertar_ultimo(lista, &elem2);
	lista_iter_t* iter = lista_iter_crear(lista);
	lista_iter_insertar(iter, &elem3);
	lista_destruir(lista, NULL);
	free(iter);
	return true;
}

void *borrar_vacio(){
	lista_t* lista = lista_crear();
	lista_iter_t* iter = lista_iter_crear(lista);
	void* valor = lista_iter_borrar(iter);
	lista_destruir(lista, NULL);
	free(iter);
	return valor;
}

bool borrar_en_el_medio(){
	lista_t* lista = lista_crear();
	int elem1 = 5;
	int elem2 = 8;
	int elem3 = 4;
	int elem4 = 6;
	lista_insertar_ultimo(lista, &elem1);
	lista_insertar_ultimo(lista, &elem2);
	lista_insertar_ultimo(lista, &elem3);
	lista_insertar_ultimo(lista, &elem4);
	lista_iter_t* iter = lista_iter_crear(lista);
	lista_iter_avanzar(iter);
	lista_iter_avanzar(iter);
	void* valor = lista_iter_borrar(iter);
	lista_destruir(lista, NULL);
	free(iter);
	return *(int*)valor == elem3;
}

bool borrar_ultimo(){
	lista_t* lista = lista_crear();
	int elem1 = 1;
	int elem2 = 7;
	lista_insertar_ultimo(lista, &elem1);
	lista_insertar_ultimo(lista, &elem2);
	lista_iter_t* iter = lista_iter_crear(lista);
	lista_iter_avanzar(iter);
	void* valor = lista_iter_borrar(iter);
	lista_destruir(lista, NULL);
	free(iter);
	return *(int*)valor == elem2;
}

bool borrar_primero(){
	lista_t* lista = lista_crear();
	int elem1 = 3;
	int elem2 = 8;
	lista_insertar_ultimo(lista, &elem1);
	lista_insertar_ultimo(lista, &elem2);
	lista_iter_t* iter = lista_iter_crear(lista);
	void* valor = lista_iter_borrar(iter);
	lista_destruir(lista, NULL);
	free(iter);
	return *(int*)valor == elem1;
}

bool borrar_uno_solo(){
	lista_t* lista = lista_crear();
	int elem1 = 4;
	lista_insertar_ultimo(lista, &elem1);
	lista_iter_t* iter = lista_iter_crear(lista);
	void* valor = lista_iter_borrar(iter);
	lista_destruir(lista, NULL);
	free(iter);
	return *(int*)valor == elem1;
}

bool borrar_segundo(){
	lista_t* lista = lista_crear();
	int elem1 = 4;
	int elem2 = 5;
	int elem3 = 6;
	int elem4 = 8;
	lista_insertar_primero(lista, &elem1);
	lista_insertar_primero(lista, &elem2);
	lista_insertar_primero(lista, &elem3);
	lista_insertar_primero(lista, &elem4);
	lista_iter_t* iter = lista_iter_crear(lista);
	lista_iter_avanzar(iter);
	void* valor = lista_iter_borrar(iter);
	lista_destruir(lista, NULL);
	free(iter);
	return *(int*)valor == elem3;
}

bool prueba_lista_iter_externo_crear(){
	lista_t* lista = lista_crear();
	lista_iter_t* iter = lista_iter_crear(lista);
	if(iter){
		lista_destruir(lista, NULL);
		free(iter);
		return true;
	}
	lista_destruir(lista, NULL);
	free(iter);
	return false;
}

bool prueba_iter_devuelve_correctamente(){
	lista_t* lista = lista_crear();
	int vec[3] = {1,2,3};
	for(int i = 0; i < 3; i ++){
		lista_insertar_primero(lista, &vec[i]);
	}
	lista_iter_t* iter = lista_iter_crear(lista);
	if(*(int*)lista_iter_ver_actual(iter) == vec[2]){
		lista_destruir(lista, NULL);
		free(iter);
		return true;
	}
	lista_destruir(lista, NULL);
	free(iter);
	return false;
}

bool prueba_lista_iter_avanzar(){
	lista_t* lista = lista_crear();
	int vec[3] = {1,2,3};
	for(int i = 0; i < 3; i ++){
		lista_insertar_primero(lista, &vec[i]);
	}
	lista_iter_t* iter = lista_iter_crear(lista);
	if(lista_iter_avanzar(iter)){
		lista_destruir(lista, NULL);
		free(iter);
		return true;
	}
	lista_destruir(lista, NULL);
	free(iter);
	return false;
}

void pruebas_lista_alumno(){

	print_test("La lista se creo", prueba_lista_crear());
	print_test("La lista esta vacia", prueba_lista_esta_vacia());

//Desapilar y ver tope en una lista vacia es invalido.
    desapilar_y_ver_tope_invalido();

//Me fijo que encolando y desencolando se mantiene la invariable.
    chequear_invariante_insertar_primero();
	chequear_invariante_insertar_ultimo();

//Me fijo que al desencolar hasta dejarla vacia la cola se comporta como recien creada.
    print_test("La lista desapilada se comporta como vacia", prueba_lista_desapilada_se_comporta_como_vacia());

//En una cola que quedo vacia desencolar son invalidos desencolar y ver primero.
    desapilar_y_ver_tope_invalido();

//Prueba de volumen.
    print_test("Pasa la prueba de volumen", prueba_volumen());

//Insertar NULL es valido.
    insertar_null();
    
//Iterador interno
	print_test("El iterador interno funciona", iter_interno());

//Iterador externo
	print_test("Se creo un iterador externo", prueba_lista_iter_externo_crear());
	print_test("El iterador devuelve correctamente", prueba_iter_devuelve_correctamente());
	print_test("El iterador avanza correctamente", prueba_lista_iter_avanzar());

	//Insertar en el medio
	print_test("Se inserto un elemento en el medio", iter_insertar_medio());

	//insertar cuando el proximo es NULL
	print_test("Se inserto un elemento cuando el proximo es NULL", iter_insertar_al_final());

	//Insertar cuando el anterior es NULL
	print_test("Se inserto un elemento cuando el anterior es NULL", iter_insertar_al_principio());

	print_test("Borrar en una lista vacia devuelve NULL", borrar_vacio() == NULL);

	//Borrar en el medio
	print_test("Borar en el medio funciona", borrar_en_el_medio());

	//Borrar el ultimo
	print_test("Borrar el ultimo funciona", borrar_ultimo());
	
	//Borrar el primero
	print_test("Borrar el primero funciona", borrar_primero());

	//Borrar uno solo
	print_test("Borrar el unico elemento de una lista funciona", borrar_uno_solo());

	//Borro el segundo
	print_test("Borrar el segundo funciona", borrar_segundo());
	
//Destruir lista.
	pruebas_destruir_free();
	pruebas_destruir_null();
    prueba_lista_destruir();
}

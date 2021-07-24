#include "cola.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void pruebas_destruir_free(){
	cola_t* cola = cola_crear();
	void** vec = malloc(sizeof(void*) * 100);
	for(int i = 0; i < 100; i ++){
		vec[i] = malloc(sizeof(void*));
		cola_encolar(cola, vec[i]);
	}
	cola_destruir(cola,free);
	free(vec);
}

void pruebas_destruir_null(){
	cola_t* cola = cola_crear();
	for(int i = 0; i < 5; i ++){
		cola_encolar(cola, &i);
	}
	for(int i = 0; i < 5; i ++){
		cola_desencolar(cola);
	}
	cola_destruir(cola,NULL);
} 

//La invariante del TDA seria que el primer elemento en entrar es el primero
//en desencolarse.
void chequear_invariante_cola(){
	cola_t* cola = cola_crear();
	int var1 = 5;
    int var2 = 9;
    cola_encolar(cola, &var1);
    cola_encolar(cola, &var2);
    int *tope1 = (int *)(cola_desencolar(cola));
    print_test("El tope es 5, se mantuvo la invariante", tope1 == &var1);
    cola_destruir(cola, NULL);
}

void desapilar_y_ver_tope_invalido(cola_t* cola,void* a, void* b){
	a = cola_desencolar(cola);
    print_test("Desapilar en una cola vacia es invalido", a == NULL);
    b = cola_ver_primero(cola);
    print_test("Ver el tope de una cola vacia es invalido", b == NULL);
}

void encolar_null(){
    cola_t* cola = cola_crear();
	void* nuevo = NULL;    
    print_test("Se encolo un NULL", cola_encolar(cola, nuevo));
    cola_destruir(cola, NULL);
}

bool volumen(cola_t* cola){
	int vector[1000];
    for(int i = 0; i < 1000; i++){
		vector[i] = i;
        cola_encolar(cola, &vector[i]);
    }
    for(int i = 0; i < 1000; i++){
        int* nuevo_tope = (int*)(cola_desencolar(cola));
        if(*nuevo_tope != vector[i]){
			return false;
		}
    }
    return true;
}

bool prueba_cola_crear(){
    cola_t* cola = cola_crear();
    if(cola){
    	cola_destruir(cola, NULL);
    	return true;
    }
    cola_destruir(cola, NULL);
    return false;
}

bool prueba_cola_esta_vacia(){
    cola_t* cola = cola_crear();
    if(cola_esta_vacia(cola)){
    	cola_destruir(cola, NULL);
    	return true;
    }
    cola_destruir(cola, NULL);
    return false;
}

void desencolar_y_ver_tope_invalido(){
    cola_t* cola = cola_crear();
	void* a = cola_desencolar(cola);
    print_test("Desencolar en una cola vacia es invalido", a == NULL);
    void* b = cola_ver_primero(cola);
    print_test("Ver el tope de una cola vacia es invalido", b == NULL);
    cola_destruir(cola, NULL);
}

void cola_se_comporta_como_recien_creda(){
    cola_t* cola = cola_crear();
    volumen(cola);
    print_test("La cola desapilada se comporta como vacia", cola_esta_vacia(cola));
    cola_destruir(cola, NULL);
}

void desencolar_y_ver_tope_invalido_cola_vaciada(){
    cola_t* cola = cola_crear();
    volumen(cola);
    void* a = cola_desencolar(cola);
    print_test("Desencolar en una cola que se vacio es invalido", a == NULL);
    void* b = cola_ver_primero(cola);
    print_test("Ver el primero de una cola que se vacio es invalido", b == NULL);
    cola_destruir(cola, NULL);
}

bool prueba_volumen(){
    cola_t* cola = cola_crear();
    if(volumen(cola)){
        cola_destruir(cola, NULL);
        return true;
    }
    cola_destruir(cola, NULL);
    return false;
}

void prueba_destruir_cola(){
    cola_t* cola = cola_crear();
    cola_destruir(cola, NULL);
}


void pruebas_cola_alumno(){

	print_test("La cola se creo", prueba_cola_crear());
	print_test("La cola esta vacia", prueba_cola_esta_vacia());

//Desapilar y ver tope en una cola vacia es invalido.
    desencolar_y_ver_tope_invalido();

//Me fijo que encolando y desencolando se mantiene la invariable.
    chequear_invariante_cola();

//Me fijo que al desencolar hasta dejarla vacia la cola se comporta como recien creada.
    cola_se_comporta_como_recien_creda();

//En una cola que quedo vacia desencolar son invalidos desencolar y ver primero.
    desencolar_y_ver_tope_invalido_cola_vaciada();

//Prueba de volumen.
    print_test("Pasa la prueba de volumen", prueba_volumen());

//Encolar NULL es valido.
    encolar_null();

//Destruir cola.
	pruebas_destruir_free();
	pruebas_destruir_null();
    prueba_destruir_cola();
}

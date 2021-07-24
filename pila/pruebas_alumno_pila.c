#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
 
 //Por invariante se refiere a que el TDA respete que el ultimo elemento
 //en entrar sea el primero en salir.
void chequear_invariante_pila(){
    pila_t* pila = pila_crear();
	int var1 = 5;
    int var2 = 9;
    pila_apilar(pila, &var1);
    pila_apilar(pila, &var2);
    int *tope1 = (int *)(pila_desapilar(pila));
    print_test("El tope es 5, se mantuvo la invariante", tope1 == &var2);
    pila_destruir(pila);
}

void desapilar_y_ver_tope_invalido(){
    pila_t* pila = pila_crear();
	void* a = pila_desapilar(pila);
    print_test("Desapilar en una pila vacia es invalido", a == NULL);
    void* b = pila_ver_tope(pila);
    print_test("Ver el tope de una pila vacia es invalido", b == NULL);
    pila_destruir(pila);
}

void apilar_null(){
    pila_t* pila = pila_crear();
	void* nuevo = NULL;    
    print_test("Se apilo un NULL", pila_apilar(pila, nuevo));
    pila_destruir(pila);
}

bool volumen(pila_t* pila){
	int vector[1000];		
    for(int i = 0; i < 1000; i++){
		vector[i] = i;
        pila_apilar(pila, &vector[i]);
        int* y = (int*)(pila_ver_tope(pila));
        if(*y != vector[i]){
			return false;
		}
    }
    for(int i = 999; i >= 0; i--){
        int* nuevo_tope = (int*)(pila_desapilar(pila));
        if(*nuevo_tope != vector[i]){
			return false;
		}
    }
    return true;
}

bool prueba_pila_crear(){
    pila_t* pila = pila_crear();
    if(pila){
    	pila_destruir(pila);
    	return true;
    }
    pila_destruir(pila);
    return false;
}

bool prueba_pila_esta_vacia(){
    pila_t* pila = pila_crear();
    if(pila_esta_vacia(pila)){
    	pila_destruir(pila);
    	return true;
    }
    pila_destruir(pila);
    return false;
}

void pila_se_comporta_como_recien_creda(){
    pila_t* pila = pila_crear();
    volumen(pila);
    print_test("La pila desapilada se comporta como vacia", pila_esta_vacia(pila));
    pila_destruir(pila);
}

void desapilar_y_ver_tope_invalido_pila_desapilada(){
    pila_t* pila = pila_crear();
    volumen(pila);
    void* a = pila_desapilar(pila);
    print_test("Desapilar en una pila que se vacio es invalido", a == NULL);
    void* b = pila_ver_tope(pila);
    print_test("Ver el tope de una pila que se vacio es invalido", b == NULL);
    pila_destruir(pila);
}

bool prueba_volumen(){
    pila_t* pila = pila_crear();
    if(volumen(pila)){
        pila_destruir(pila);
        return true;
    }
    pila_destruir(pila);
    return false;
}

void prueba_destruir_pila(){
    pila_t* pila = pila_crear();
    pila_destruir(pila);
}


void pruebas_pila_alumno(){
//Creo la pila.  
    print_test("La pila pudo crearse", prueba_pila_crear());

//Verifica que este vacia.
    print_test("La pila esta vacia.", prueba_pila_esta_vacia());

//Desapilar y ver tope en una pila vacia es invalido.
    desapilar_y_ver_tope_invalido();

//Me fijo que apilando y desapilando se mantiene la invariable.   
    chequear_invariante_pila();

//Me fijo que al desapilar hasta dejarla vacia la pila se comporta como recien creada.
    pila_se_comporta_como_recien_creda();

//En una pila que quedo vacia desapilandola son invalidos desapilar y ver tope.   
    desapilar_y_ver_tope_invalido_pila_desapilada();

//Prueba de volumen.
    print_test("Pasa la prueba de volumen", prueba_volumen());

//Apilar NULL es valido.
    apilar_null();

//Destruir pila.
    prueba_destruir_pila();   
}
